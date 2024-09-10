#pragma once

class CTile;
class CMapMgr
{
private:
	CMapMgr();
	~CMapMgr();

public:
	void Release();
	bool Load_Tiles();
	vector<CTile*>& Get_Tiles() { return m_vecTile; }

public:
	static CMapMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CMapMgr;
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
	static CMapMgr* m_pInstance;
	vector<CTile*> m_vecTile;
	int m_iTileID = 0;
};

