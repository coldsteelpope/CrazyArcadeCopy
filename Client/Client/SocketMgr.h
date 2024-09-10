#pragma once
class CSocketMgr
{
private:
	CSocketMgr();
	virtual ~CSocketMgr();

public:
	bool Initialize();
	void Release();

public:
	static DWORD WINAPI ThreadReceive(LPVOID pParam);
	static DWORD Send_Move_Message(
		int m_iClientID,
		INFO _tInfo,
		FRAME _tFrame, 
		OBJ_STATUS _eObjStatus
	);

	// Trap 상태는 상대편에 의해 죽을수도 있는 상태이니 지속적으로 보낼 것
	static DWORD Send_Trap_Message(
		int m_iClientID,
		INFO _tInfo,
		FRAME _tFrame
	);

	// 죽는건 딱 한번
	static DWORD Send_Dead_Message(
		int m_iClientID,
		INFO _tInfo,
		FRAME _tFrame
	);

	// wait 이벤트가 발생할 때마다 보내기
	static DWORD Send_Wait_Message(
		int m_iClientID,
		INFO _tInfo,
		FRAME _tFrame
	);

	static DWORD Send_Create_Water_Bomb_Message(int m_iClientID, int _iSpawnX, int _iSpawnY);

	static DWORD Send_Break_Tile_Message(int m_iTileID);
	
private:
	void Initialize_WinSock();
	bool Get_Tiles_From_Server();
public:
	static CSocketMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CSocketMgr;
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
	static CSocketMgr* m_pInstance;
	static SOCKET m_hSocket;
	bool m_bSuccessToGetTiles = false;
	
};

