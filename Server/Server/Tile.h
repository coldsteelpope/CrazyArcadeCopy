#pragma once
class CTile
{
public:
	CTile();
	~CTile();


public:
	inline void Set_Tile_ID(int _iTileID) { m_iTileID = _iTileID; }
	inline void Set_Pos(D3DXVECTOR3 _vPos) { m_tInfo.vPos = _vPos; }
	inline void Set_Scale(float _fCX, float _fCY) { m_tInfo.fCX = _fCX; m_tInfo.fCY = _fCY; }
	inline void Set_Tile_Type(TILE_TYPE _eTileType) { m_eTileType = _eTileType; }

public:
	inline const int Get_Tile_ID() { return m_iTileID; }
	inline const INFO Get_Info() { return m_tInfo; }
	inline const TILE_TYPE Get_Tile_Type() { return m_eTileType; }
public:

public:
	int m_iTileID;
	INFO m_tInfo;
	TILE_TYPE m_eTileType;
};

