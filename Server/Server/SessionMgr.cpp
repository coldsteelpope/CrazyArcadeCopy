#include "pch.h"
#include "Session.h"
#include "SessionMgr.h"
#include "Tile.h"
#include "ListenSocketMgr.h"
#include "MapMgr.h"

CSessionMgr* CSessionMgr::m_pInstance = nullptr;
CRITICAL_SECTION CSessionMgr::m_cs = {};
list<CSession*> CSessionMgr::m_sessionList = {};

CSessionMgr::CSessionMgr()
{
}

CSessionMgr::~CSessionMgr()
{
	Release();
}

bool CSessionMgr::Initialize()
{
	::InitializeCriticalSection(&m_cs);
	return true;
}

bool CSessionMgr::Add_Session(SOCKET _hAcceptSocket, PROTOCOL_INFO _tInfo, PROTOCOL_FRAME _tFrame)
{
	vector<CTile*> vTiles = CMapMgr::Get_Instance()->Get_Tiles();
	for (CTile* vTile : vTiles)
	{
		TILE_PROTOCOL tTileProtocol = {
			vTile->Get_Tile_ID(),
			OBJ_ID::OBJ_ID_TILE,
			PROTOCOL_TYPE::PROTOCOL_TYPE_TILE,
			vTile->Get_Tile_Type(),
			vTile->Get_Info().vPos,
			vTile->Get_Info().fCX,
			vTile->Get_Info().fCY,
			false
		};
		::send(_hAcceptSocket, (char*)(&tTileProtocol), sizeof(TILE_PROTOCOL), 0);
	}
	
	TILE_PROTOCOL tTileProtocol = {
		-1,
		OBJ_ID::OBJ_ID_TILE,
		PROTOCOL_TYPE::PROTOCOL_TYPE_TILE,
		TILE_TYPE::TILE_TYPE_END,
		{ -1.f, -1.f, -1.f },
		-1.f, -1.f,
		true
	};
	::send(_hAcceptSocket, (char*)(&tTileProtocol), sizeof(TILE_PROTOCOL), 0);



	CSession* pNewSession = new CSession(
		m_iSessionID,
		_hAcceptSocket,
		OBJ_ID::OBJ_ID_PLAYER,
		_tInfo,
		_tFrame
	);

	// Session을 만들어, Player에게 정보를 제공한다.
	PROTOCOL tProtocol = {
		m_iSessionID,
		OBJ_ID::OBJ_ID_PLAYER,
		PROTOCOL_TYPE::PROTOCOL_TYPE_CREATE,
		_tInfo,
		_tFrame,
		OBJ_STATUS::OBJ_STATUS_READY
	};
	::send(_hAcceptSocket, (char*)&tProtocol, sizeof(PROTOCOL), 0);

	::EnterCriticalSection(&m_cs);
	m_sessionList.push_back(pNewSession);
	for (auto iter = m_sessionList.begin(); iter != m_sessionList.end(); ++iter)
	{
		if ((*iter)->Get_Session_ID() == tProtocol.m_iClientID)
		{
			continue;
		}

		// 게임에 있던 Client에게 방문한 Client의 정보를 제공한다.
		PROTOCOL tVisitedClientInfoProtocol = {
			tProtocol.m_iClientID,
			OBJ_ID::OBJ_ID_ENEMY,
			PROTOCOL_TYPE::PROTOCOL_TYPE_CREATE,
			_tInfo,
			_tFrame,
			OBJ_STATUS::OBJ_STATUS_READY
		};
		::send(
			(*iter)->Get_Client_Socket(), 
			(char*)(&tVisitedClientInfoProtocol), 
			sizeof(PROTOCOL), 
			0
		);

		// 방문한 Client에게 원래 게임에 있던 Client들의 정보들을 제공한다.
		PROTOCOL tLivedClientInfoProtocol = {
			(*iter)->Get_Session_ID(),
			OBJ_ID::OBJ_ID_ENEMY,
			PROTOCOL_TYPE::PROTOCOL_TYPE_CREATE,
			(*iter)->Get_Protocol_Info(),
			(*iter)->Get_Protocol_Frame(),
			(*iter)->Get_Obj_Status()
		};
		::send(
			_hAcceptSocket,
			(char*)(&tLivedClientInfoProtocol),
			sizeof(PROTOCOL),
			0
		);
	}
	::LeaveCriticalSection(&m_cs);


	DWORD dwThreadID = 0;
	HANDLE hThread = ::CreateThread(
		NULL, 0,
		ThreadFunction,
		(LPVOID)pNewSession, 0,
		&dwThreadID
	);
	::CloseHandle(hThread);

	++m_iSessionID;
	return true;
}

void CSessionMgr::Release()
{
	CListenSocketMgr::Get_Instance()->ShutDown_ListenSocket();
	::EnterCriticalSection(&m_cs);
	for (auto iter = m_sessionList.begin(); iter != m_sessionList.end(); ++iter)
	{
		::closesocket((*iter)->Get_Client_Socket());
		Safe_Delete<CSession*>((*iter));
	}
	m_sessionList.clear();
	::LeaveCriticalSection(&m_cs);

	::Sleep(100);
	::DeleteCriticalSection(&m_cs);
}

// session 정보를 업데이트하고, 다른 이들에게 메시지를 보내는 함수
void CSessionMgr::Update_Status_With_Send_Message(PROTOCOL _tProtocol)
{
	::EnterCriticalSection(&m_cs);

	// enemy들에게 보내는 player 정보
	PROTOCOL tEnemyProtocol = {
		_tProtocol.m_iClientID,
		OBJ_ID::OBJ_ID_ENEMY,
		PROTOCOL_TYPE::PROTOCOL_TYPE_UPDATE,
		_tProtocol.tProtocolInfo,
		_tProtocol.tProtocolFrame,
		_tProtocol.eObjStatus
	};

	for (auto iter = m_sessionList.begin(); iter != m_sessionList.end(); ++iter)
	{
		if (_tProtocol.m_iClientID == (*iter)->Get_Session_ID())
		{
			(*iter)->Set_Info(_tProtocol.tProtocolInfo);
			(*iter)->Set_Frame(_tProtocol.tProtocolFrame);
			(*iter)->Set_Obj_Status(_tProtocol.eObjStatus);
			continue;
		}
		::send(
			(*iter)->Get_Client_Socket(),
			(char*)(&tEnemyProtocol),
			sizeof(PROTOCOL),
			0
		);
	}

	::LeaveCriticalSection(&m_cs);
}

void CSessionMgr::Send_Create_Water_Bomb_Message(PROTOCOL _tProtocol)
{
	::EnterCriticalSection(&m_cs);
	PROTOCOL tCreatedWaterBombProtocol = {
		_tProtocol.m_iClientID,
		OBJ_ID::OBJ_ID_WATER_BOMB,
		PROTOCOL_TYPE::PROTOCOL_TYPE_CREATE,
		_tProtocol.tProtocolInfo,
		_tProtocol.tProtocolFrame,
		_tProtocol.eObjStatus
	};

	for (auto iter = m_sessionList.begin(); iter != m_sessionList.end(); ++iter)
	{
		if (_tProtocol.m_iClientID == (*iter)->Get_Session_ID())
		{
			continue;
		}
		::send(
			(*iter)->Get_Client_Socket(),
			(char*)(&tCreatedWaterBombProtocol),
			sizeof(PROTOCOL),
			0
		);
	}


	::LeaveCriticalSection(&m_cs);
}

void CSessionMgr::Update_Tile_Status_To_Broken(int m_iTileID)
{
	::EnterCriticalSection(&m_cs);
	CMapMgr::Get_Instance()->Get_Tiles()[m_iTileID]->Set_Tile_Type(TILE_TYPE::BROKEN_TILE);
	::LeaveCriticalSection(&m_cs);
}

DWORD __stdcall CSessionMgr::ThreadFunction(LPVOID pParam)
{
	PROTOCOL tProtocol = { 0 };
	CSession* pSession = (CSession*)pParam;

	int nReceiveDataSize = 0;
	puts("[+] 새 클라이언트가 연결되었습니다.");
	
	// 클라이언트가 데이터를 받으면
	while ((nReceiveDataSize = ::recv(
		pSession->Get_Client_Socket(),
		(char*)(&tProtocol),
		sizeof(PROTOCOL),
		0
	)) > 0)
	{
		switch (tProtocol.eObjID)
		{
		case OBJ_ID::OBJ_ID_PLAYER:
		{
			Update_Status_With_Send_Message(tProtocol);
			break;
		}
		case OBJ_ID::OBJ_ID_WATER_BOMB:
		{
			Send_Create_Water_Bomb_Message(tProtocol);
			break;
		}
		case OBJ_ID::OBJ_ID_TILE:
		{
			switch (tProtocol.eType)
			{
			case PROTOCOL_TYPE::PROTOCOL_TYPE_DELETE:
			{
				Update_Tile_Status_To_Broken(tProtocol.m_iClientID);
				break;
			}
			}
			break;
		}
		// 나머지는 그냥 보내는 방식
		}
		memset(&tProtocol, 0, sizeof(PROTOCOL));
	}

	// client 연결이 끊겼을 때
	puts("[+] 클라이언트가 연결을 끊었습니다.");
	::closesocket(pSession->Get_Client_Socket());
	
	PROTOCOL tDeleteProtocol = {
		pSession->Get_Session_ID(),
		OBJ_ID::OBJ_ID_ENEMY,
		PROTOCOL_TYPE::PROTOCOL_TYPE_DELETE,
		pSession->Get_Protocol_Info(),
		pSession->Get_Protocol_Frame(),
		pSession->Get_Obj_Status()
	};

	::EnterCriticalSection(&m_cs);
	for (auto iter = m_sessionList.begin(); iter != m_sessionList.end();)
	{
		if (tDeleteProtocol.m_iClientID == (*iter)->Get_Session_ID())
		{
			Safe_Delete<CSession*>((*iter));
			iter = m_sessionList.erase(iter);
		}
		else
		{
			::send(
				(*iter)->Get_Client_Socket(),
				(char*)(&tDeleteProtocol),
				sizeof(PROTOCOL),
				0
			);
			++iter;
		}
	}
	::LeaveCriticalSection(&m_cs);


	return 0;
}
