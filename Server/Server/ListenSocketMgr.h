#pragma once
class CListenSocketMgr
{
private:
	CListenSocketMgr();
	~CListenSocketMgr();
public:
	bool Initialize(int _portNumber);
	bool Listen();
	void ShutDown_ListenSocket();
	void Release();

public:
	const SOCKET& Get_Listen_Socket() const { return m_hListenSocket; }

public:
	static CListenSocketMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{

			m_pInstance = new CListenSocketMgr;
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
	static CListenSocketMgr* m_pInstance;
	SOCKET m_hListenSocket;
};

