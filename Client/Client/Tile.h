#pragma once

#include "Obj.h"
class CTile : public CObj
{
public:
	CTile();
	virtual ~CTile();
public:

	inline void Set_Tile_ID(int _iTileID) { m_iTileID = _iTileID; }
	inline int Get_Tile_ID() { return m_iTileID; }
	inline void Set_Tile_Type(TILE_TYPE _eTileType) { m_eTileType = _eTileType; }
	inline TILE_TYPE Get_Tile_Type() { return m_eTileType; }

public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;


public:
	int m_iTileID;
	TILE_TYPE m_eTileType;
	
};

