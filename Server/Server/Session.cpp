#include "pch.h"
#include "Session.h"

CSession::CSession()
{
}

CSession::CSession(int _iSessionID, SOCKET _hClientSocket, OBJ_ID _eObjId, PROTOCOL_INFO _tInfo, PROTOCOL_FRAME _tFrame)
{
	m_iSessionID = _iSessionID;
	m_hClientSocket = _hClientSocket;
	m_eObjId = _eObjId;
	m_tInfo = _tInfo;
	m_tFrame = _tFrame;
}

CSession::~CSession()
{
}

void CSession::Release()
{
}
