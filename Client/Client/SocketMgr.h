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

	// Trap ���´� ����� ���� �������� �ִ� �����̴� ���������� ���� ��
	static DWORD Send_Trap_Message(
		int m_iClientID,
		INFO _tInfo,
		FRAME _tFrame
	);

	// �״°� �� �ѹ�
	static DWORD Send_Dead_Message(
		int m_iClientID,
		INFO _tInfo,
		FRAME _tFrame
	);

	// wait �̺�Ʈ�� �߻��� ������ ������
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

