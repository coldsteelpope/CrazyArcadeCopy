#pragma once

class CSession;
class CSessionMgr
{
private:
	CSessionMgr();
	virtual ~CSessionMgr();

public:
	bool Initialize();
	bool Add_Session(SOCKET _hAcceptSocket, PROTOCOL_INFO _tINFO, PROTOCOL_FRAME _tFrame);
	void Release();

public:
	static DWORD WINAPI ThreadFunction(LPVOID pParam);
	static void Update_Status_With_Send_Message(PROTOCOL _tProtocol);
	static void Send_Create_Water_Bomb_Message(PROTOCOL _tProtocol);
	static void Update_Tile_Status_To_Broken(int m_iTileID);
public:
	static CSessionMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CSessionMgr;
		}
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSessionMgr* m_pInstance;
	static CRITICAL_SECTION m_cs;
	static list<CSession*> m_sessionList;

	int m_iSessionID = 1;
};

