#include "pch.h"
#include "ObjMgr.h"
#include "SocketMgr.h"
#include "CAbstractFactory.h"
#include "Player.h"
#include "WaterBomb.h"
#include "Enemy.h"

CSocketMgr* CSocketMgr::m_pInstance = nullptr;
SOCKET CSocketMgr::m_hSocket = {};

CSocketMgr::CSocketMgr()
{

}

CSocketMgr::~CSocketMgr()
{
    Release();
}

bool CSocketMgr::Initialize()
{
    Initialize_WinSock();
    
    m_hSocket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (m_hSocket == INVALID_SOCKET)
    {
        assert(false);
    }

    SOCKADDR_IN svraddr = { 0 };
    svraddr.sin_family = AF_INET;
    svraddr.sin_port = htons(25000);
    svraddr.sin_addr.S_un.S_addr = inet_addr("192.168.1.55");

    if (::connect(m_hSocket, (SOCKADDR*)&svraddr, sizeof(svraddr)) == SOCKET_ERROR)
    {
        assert(false);
        return false;
    }

    // Get Tiles

    if (Get_Tiles_From_Server())
    {
        DWORD dwThreadID = 0;
        HANDLE hThread = ::CreateThread(
            NULL,
            0,
            ThreadReceive,
            (LPVOID)m_hSocket,
            0, &dwThreadID
        );
        ::CloseHandle(hThread);
        return true;
    }
    else
    {
        assert(false);
        return false;
    }
}

DWORD __stdcall CSocketMgr::ThreadReceive(LPVOID pParam)
{
    SOCKET hSocket = (SOCKET)pParam;
    PROTOCOL tProtocol = { 0 };
    while (::recv(
        hSocket,
        (char*)&tProtocol,
        sizeof(PROTOCOL),
        0
    ) > 0)
    {
        switch (tProtocol.eObjID)
        {
        case OBJ_ID::OBJ_ID_PLAYER:
        {
            switch (tProtocol.eType)
            {
            case PROTOCOL_TYPE::PROTOCOL_TYPE_CREATE:
            {
                // OBJ_ID: PLAYER || PROTOCOL_TYPE: CREATE
                CObjMgr::Get_Instance()->Add_Object(
                    OBJ_ID_PLAYER,
                    CAbstractFactory<CPlayer>::Create_Player(
                        D3DXVECTOR3{ tProtocol.tProtocolInfo._fX, tProtocol.tProtocolInfo._fY, 0 },
                        D3DXVECTOR3{ 0.f, 1.0f, 0.f },
                        PLAYER_READY_FCX,
                        PLAYER_READY_FCY,
                        tProtocol.m_iClientID,
                        tProtocol.eObjStatus,
                        FRAME{
                            tProtocol.tProtocolFrame.iFrameStart,
                            tProtocol.tProtocolFrame.iFrameEnd,
                            0,
                            100,
                            GetTickCount(),
                            false
                        }
                    )
                );
                break;
            }
            }
            break;
        }
        case OBJ_ID::OBJ_ID_ENEMY:
        {
            switch (tProtocol.eType)
            {
            case PROTOCOL_TYPE::PROTOCOL_TYPE_CREATE:
            {
                // OBJ_ID: ENEMY || PROTOCOL_TYPE: CREATE
                CObjMgr::Get_Instance()->Add_Object(
                    OBJ_ID_ENEMY,
                    CAbstractFactory<CEnemy>::Create_Enemy(
                        D3DXVECTOR3{ tProtocol.tProtocolInfo._fX, tProtocol.tProtocolInfo._fY, 0 },
                        D3DXVECTOR3{ 0.f, 1.0f, 0.f },
                        PLAYER_READY_FCX,
                        PLAYER_READY_FCY,
                        tProtocol.m_iClientID,
                        tProtocol.eObjStatus,
                        FRAME{
                            tProtocol.tProtocolFrame.iFrameStart,
                            tProtocol.tProtocolFrame.iFrameEnd,
                            0,
                            100,
                            GetTickCount(),
                            false
                        }
                    )
                );
                break;
            }
            case PROTOCOL_TYPE::PROTOCOL_TYPE_UPDATE:
            {
                // OBJ_ID: ENEMY || PROTOCOL_TYPE: UPDATE
                list<CObj*> m_pTargetList = CObjMgr::Get_Instance()->Get_List_By_Id(OBJ_ID_ENEMY);
                for (CObj* pObj : m_pTargetList)
                {
                    if (pObj->Get_ClientID() == tProtocol.m_iClientID)
                    {
                        pObj->Set_Pos(D3DXVECTOR3{ tProtocol.tProtocolInfo._fX, tProtocol.tProtocolInfo._fY, 0.f });
                        pObj->Set_Scale(tProtocol.tProtocolInfo._fCX, tProtocol.tProtocolInfo._fCY);
                        pObj->Set_Frame_Start(tProtocol.tProtocolFrame.iFrameStart);
                        pObj->Set_Frame_End(tProtocol.tProtocolFrame.iFrameEnd);
                        pObj->Set_Obj_Cur_Status(tProtocol.eObjStatus);
                    }
                }
                break;
            }
            case PROTOCOL_TYPE::PROTOCOL_TYPE_DELETE:
            {
                CObjMgr::Get_Instance()->Delete_Enemy(tProtocol.m_iClientID);
                break;
            }
            }
            break;
        }
        case OBJ_ID::OBJ_ID_WATER_BOMB:
        {
            switch (tProtocol.eType)
            {
            case PROTOCOL_TYPE::PROTOCOL_TYPE_CREATE:
            {
                CObjMgr::Get_Instance()->Add_Object(
                    OBJ_ID_WATER_BOMB,
                    CAbstractFactory<CWaterBomb>::Create(
                        D3DXVECTOR3{ (float)tProtocol.tProtocolInfo._fX, (float)tProtocol.tProtocolInfo._fY, 0.f },
                        D3DXVECTOR3{ 0.f, 0.f, 0.f },
                        WATER_BOMB_IDLE_FCX,
                        WATER_BOMB_IDLE_FCY
                    )
                );
                break;
            }
            }
            break;
        }
        }
    }
    
    return 0;
}


void CSocketMgr::Release()
{
    ::shutdown(m_hSocket, SD_BOTH);
    ::closesocket(m_hSocket);
    ::WSACleanup();
}


DWORD CSocketMgr::Send_Move_Message(int m_iClientID, INFO _tInfo, FRAME _tFrame, OBJ_STATUS _eObjStatus)
{
    /*
    typedef struct tagProtocol
    {
	    int m_iClientID;
	    OBJ_ID eObjID;
	    PROTOCOL_TYPE eType;
	    PROTOCOL_INFO tProtocolInfo;
	    PROTOCOL_FRAME tProtocolFrame;
        OBJ_STATUS eObjStatus
    } PROTOCOL;
    */
    PROTOCOL tMoveProtocol = {
        m_iClientID,
        OBJ_ID::OBJ_ID_PLAYER,
        PROTOCOL_TYPE::PROTOCOL_TYPE_UPDATE,
        PROTOCOL_INFO { _tInfo.vPos.x, _tInfo.vPos.y, _tInfo.fCX, _tInfo.fCY },
        PROTOCOL_FRAME { _tFrame.iFrameStart, _tFrame.iFrameEnd },
        _eObjStatus
    };
    ::send(m_hSocket, (char*)&tMoveProtocol, sizeof(PROTOCOL), 0);
    return 0;
}

DWORD CSocketMgr::Send_Trap_Message(int m_iClientID, INFO _tInfo, FRAME _tFrame)
{
    PROTOCOL tTrapProtocol = {
        m_iClientID,
        OBJ_ID::OBJ_ID_PLAYER,
        PROTOCOL_TYPE::PROTOCOL_TYPE_UPDATE,
        PROTOCOL_INFO { _tInfo.vPos.x, _tInfo.vPos.y, _tInfo.fCX, _tInfo.fCY },
        PROTOCOL_FRAME { _tFrame.iFrameStart, _tFrame.iFrameEnd },
        OBJ_STATUS::OBJ_STATUS_TRAP
    };
    ::send(m_hSocket, (char*)&tTrapProtocol, sizeof(PROTOCOL), 0);
    return 0;
}

DWORD CSocketMgr::Send_Dead_Message(int m_iClientID, INFO _tInfo, FRAME _tFrame)
{
    PROTOCOL tDeadProtocol = {
        m_iClientID,
        OBJ_ID::OBJ_ID_PLAYER,
        PROTOCOL_TYPE::PROTOCOL_TYPE_UPDATE,
        PROTOCOL_INFO { _tInfo.vPos.x, _tInfo.vPos.y, _tInfo.fCX, _tInfo.fCY },
        PROTOCOL_FRAME { _tFrame.iFrameStart, _tFrame.iFrameEnd },
        OBJ_STATUS::OBJ_STATUS_DIE
    };
    ::send(m_hSocket, (char*)&tDeadProtocol, sizeof(PROTOCOL), 0);
    return 0;
}

DWORD CSocketMgr::Send_Wait_Message(int m_iClientID, INFO _tInfo, FRAME _tFrame)
{
    PROTOCOL tWaitProtocol = {
        m_iClientID,
        OBJ_ID::OBJ_ID_PLAYER,
        PROTOCOL_TYPE::PROTOCOL_TYPE_UPDATE,
        PROTOCOL_INFO { _tInfo.vPos.x, _tInfo.vPos.y, _tInfo.fCX, _tInfo.fCY },
        PROTOCOL_FRAME { _tFrame.iFrameStart, _tFrame.iFrameEnd },
        OBJ_STATUS::OBJ_STATUS_WAIT
    };
    ::send(m_hSocket, (char*)(&tWaitProtocol), sizeof(PROTOCOL), 0);
    return 0;
}

DWORD CSocketMgr::Send_Create_Water_Bomb_Message(int m_iClientID, int _iSpawnX, int _iSpawnY)
{
    PROTOCOL tCreateWaterBombProtocol = {
        m_iClientID,
        OBJ_ID::OBJ_ID_WATER_BOMB,
        PROTOCOL_TYPE::PROTOCOL_TYPE_CREATE,
        PROTOCOL_INFO { (float)_iSpawnX, (float)_iSpawnY, 0, 0 },
        PROTOCOL_FRAME { 0, 0 }
    };
    ::send(m_hSocket, (char*)(&tCreateWaterBombProtocol), sizeof(PROTOCOL), 0);
    return 0;
}

DWORD CSocketMgr::Send_Break_Tile_Message(int m_iTileID)
{
    //typedef struct tagProtocol
    //{
    //    int m_iClientID;
    //    OBJ_ID eObjID;
    //    PROTOCOL_TYPE eType;
    //    PROTOCOL_INFO tProtocolInfo;
    //    PROTOCOL_FRAME tProtocolFrame;
    //    OBJ_STATUS eObjStatus;
    //} PROTOCOL;

    PROTOCOL tBreakTileProtocol = {
        m_iTileID,
        OBJ_ID::OBJ_ID_TILE,
        PROTOCOL_TYPE::PROTOCOL_TYPE_DELETE,
        PROTOCOL_INFO { 0, 0, 0, 0 },
        PROTOCOL_FRAME { 0, 0 }
    };
    ::send(m_hSocket, (char*)(&tBreakTileProtocol), sizeof(PROTOCOL), 0);
    return 0;
}


void CSocketMgr::Initialize_WinSock()
{
    WSADATA wsa = { 0 };
    if (::WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        assert(false);
    }
}

bool CSocketMgr::Get_Tiles_From_Server()
{
    TILE_PROTOCOL tTileProtocol = {};
    while (::recv(m_hSocket, (char*)(&tTileProtocol), sizeof(TILE_PROTOCOL), 0) > 0)
    {
        if (tTileProtocol.done)
        {
            m_bSuccessToGetTiles = true;
            break;
        }
        else
        {
            switch (tTileProtocol.eTileType)
            {
            case TILE_TYPE::BROKEN_TILE:
            {
                CObj* pTile = CAbstractFactory<CTile>::Create_Tile(
                    tTileProtocol.m_iTileID,
                    tTileProtocol.vPos,
                    tTileProtocol.fCX,
                    tTileProtocol.fCY,
                    TILE_TYPE::FLOOR_TILE
                );
                CObjMgr::Get_Instance()->Add_Object(
                    OBJ_ID_TILE,
                    pTile
                );
                break;
            }
            default:
            {
                CObj* pTile = CAbstractFactory<CTile>::Create_Tile(
                    tTileProtocol.m_iTileID,
                    tTileProtocol.vPos,
                    tTileProtocol.fCX,
                    tTileProtocol.fCY,
                    tTileProtocol.eTileType
                );
                CObjMgr::Get_Instance()->Add_Object(
                    OBJ_ID_TILE,
                    pTile
                );
                break;
            }
            }
        }
    }

    m_bSuccessToGetTiles = true;
    return true;
}
