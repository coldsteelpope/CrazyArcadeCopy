#pragma once

#include "pch.h"
#include "Tile.h"
class CAbstractFactory
{
public:
	static CTile* Create_Tile(
		int _iTileID,
		D3DXVECTOR3 _vPos,
		float _fCX,
		float _fCY,
		TILE_TYPE _eTileType
	)
	{
		CTile* temp = new CTile;
		temp->Set_Tile_ID(_iTileID);
		temp->Set_Pos(_vPos);
		temp->Set_Scale(_fCX, _fCY);
		temp->Set_Tile_Type(_eTileType);
		return temp;
	}
};