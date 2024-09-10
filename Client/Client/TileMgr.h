#pragma once

class CObj;
class CTileMgr
{
private:
	CTileMgr();
	virtual ~CTileMgr();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC _hDC);
	void Release();


private:
	void Key_Input();
	void Picking_Tile(POINT _tPt);
	void Save_Tile();
public:
	void Load_Tile();
	void Load_Tile_To_ObjMgr();

public:
	static CTileMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CTileMgr;
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
	static CTileMgr* m_pInstance;
	vector<CObj*> m_vecTile;

	TILE_TYPE m_eCurrentTileType = TILE_TYPE::FLOOR_TILE;

	
};

