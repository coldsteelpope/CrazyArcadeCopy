#include "pch.h"
#include "ListenSocketMgr.h"

CListenSocketMgr* CListenSocketMgr::m_pInstance = nullptr;

CListenSocketMgr::CListenSocketMgr() : m_hListenSocket(0)
{

}

CListenSocketMgr::~CListenSocketMgr()
{
	Release();
}

bool CListenSocketMgr::Initialize(int _portNumber)
{
	m_hListenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (m_hListenSocket == INVALID_SOCKET)
	{
		puts("ERROR: ���� ��� ������ ������ �� �����ϴ�.");
		return false;
	}

	SOCKADDR_IN svraddr = { 0 };
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(_portNumber);
	svraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if (::bind(m_hListenSocket, (SOCKADDR*)&svraddr, sizeof(svraddr)))
	{
		puts("ERROR: ���ε� ����");
		return false;
	}

	return true;
}

bool CListenSocketMgr::Listen()
{
	if (::listen(m_hListenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		puts("ERROR: ���� ���·� ��ȯ�� �� �����ϴ�.");
		return false;
	}
	return true;
}

void CListenSocketMgr::ShutDown_ListenSocket()
{
	::shutdown(m_hListenSocket, SD_BOTH);
}

void CListenSocketMgr::Release()
{
	::closesocket(m_hListenSocket);
}
