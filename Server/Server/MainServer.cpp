#include "pch.h"
#include "MainServer.h"
#include "SessionMgr.h"
#include "ListenSocketMgr.h"
#include "MapMgr.h"

CMainServer::CMainServer()
{
	
}

CMainServer::~CMainServer()
{
	Release();
}

bool CMainServer::Initialize()
{
	if (Initialize_WinSocket() == false)
	{
		return false;
	}

	if (CMapMgr::Get_Instance()->Load_Tiles() == false)
	{
		return false;
	}

	if (CSessionMgr::Get_Instance()->Initialize() == false)
	{
		return false;
	}

	if (CListenSocketMgr::Get_Instance()->Initialize(25000) == false)
	{
		return false;
	}

	if (CListenSocketMgr::Get_Instance()->Listen() == false)
	{
		return false;
	}

	puts("[+]간단한 크레이지 아케이드 게임 서버를 시작합니다.");
	return true;
}

void CMainServer::Update()
{
	SOCKADDR_IN clientAddr = { 0 };
	int nAddrLen = sizeof(clientAddr);
	SOCKET hClient = 0;


	hClient = ::accept(
		CListenSocketMgr::Get_Instance()->Get_Listen_Socket(),
		(SOCKADDR*)&clientAddr,
		&nAddrLen
	);

	if (hClient != INVALID_SOCKET)
	{
		PROTOCOL_INFO tPlayerInitInfo = { 400, 300, 0, 0 };
		PROTOCOL_FRAME tPlayerInitFrame = { 0, 17 };

		CSessionMgr::Get_Instance()->Add_Session(hClient, tPlayerInitInfo, tPlayerInitFrame);
	}
}

void CMainServer::Late_Update()
{
}

void CMainServer::Release()
{
	CSessionMgr::Destroy_Instance();
	CListenSocketMgr::Destroy_Instance();
	CMapMgr::Destroy_Instance();
	::WSACleanup();
}

bool CMainServer::Initialize_WinSocket()
{
	WSADATA wsa = { 0 };
	if (::WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		puts("ERROR: 윈속을 초기화 할 수 없습니다.");
		return false;
	}
	return true;
}
