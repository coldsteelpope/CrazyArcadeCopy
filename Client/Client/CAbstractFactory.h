#pragma once

#include "Tile.h"
#include "pch.h"
#include "WaterWave.h"
#include "UpWave.h"
#include "DownWave.h"
#include "LeftWave.h"
#include "Enemy.h"
#include "RightWave.h"

#include "Obj.h"
template<typename T>
class CAbstractFactory
{
public:
	static CObj* Create(
		D3DXVECTOR3 _vPos,
		D3DXVECTOR3	_vLook,
		float _fCX,
		float _fCY
	)
	{
		CObj* temp = new T;
		temp->Set_Pos(_vPos);
		temp->Set_Look(_vLook);
		temp->Set_Scale(_fCX, _fCY);
		temp->Initialize();
		return temp;
	}

	static CObj* Create_Player(
		D3DXVECTOR3 _vPos,
		D3DXVECTOR3 _vLook,
		float _fCX,
		float _fCY,
		int _iClientID,
		OBJ_STATUS _eObjStatus,
		FRAME _tFrame
	)
	{
		CObj* temp = new T;
		temp->Set_Pos(_vPos);
		temp->Set_Look(_vLook);
		temp->Set_Scale(_fCX, _fCY);
		temp->Set_ClinetID(_iClientID);
		temp->Set_Obj_Cur_Status(_eObjStatus);
		temp->Set_Frame(_tFrame);

		temp->Initialize();
		return temp;
	}

	static CObj* Create_Enemy(
		D3DXVECTOR3 _vPos,
		D3DXVECTOR3 _vLook,
		float _fCX,
		float _fCY,
		int _iClientID,
		OBJ_STATUS _eObjStatus,
		FRAME _tFrame
	)
	{
		CObj* temp = new T;
		temp->Set_Pos(_vPos);
		temp->Set_Look(_vLook);
		temp->Set_Scale(_fCX, _fCY);
		temp->Set_ClinetID(_iClientID);
		temp->Set_Obj_Cur_Status(_eObjStatus);
		temp->Set_Frame(_tFrame);
		static_cast<CEnemy*>(temp)->Set_Frame_Key();
		temp->Initialize();
		return temp;
	}

	static CObj* Create_Tile(
		D3DXVECTOR3 _vPos,
		float _fCX,
		float _fCY,
		TILE_TYPE _eTileType
	)
	{
		CObj* temp = new T;
		temp->Set_Pos(_vPos);
		temp->Set_Scale(_fCX, _fCY);
		static_cast<CTile*>(temp)->Set_Tile_Type(_eTileType);
		temp->Initialize();

		return temp;
	}

	static CObj* Create_Tile(
		int _iTileID,
		D3DXVECTOR3 _vPos,
		float _fCX,
		float _fCY,
		TILE_TYPE _eTileType
	)
	{
		CObj* temp = new T;
		temp->Set_Pos(_vPos);
		temp->Set_Scale(_fCX, _fCY);
		static_cast<CTile*>(temp)->Set_Tile_Type(_eTileType);
		static_cast<CTile*>(temp)->Set_Tile_ID(_iTileID);
		temp->Initialize();
		return temp;
	}

	static CObj* Create_Water_Wave(
		D3DXVECTOR3 _vPos,
		float _fCX,
		float _fCY,
		int m_iBombRadius
	)
	{
		CObj* pTemp = new T;
		pTemp->Set_Pos(_vPos);
		pTemp->Set_Scale(_fCX, _fCY);
		static_cast<CWaterWave*>(pTemp)->Set_Bomb_Radius(m_iBombRadius);
		pTemp->Initialize();
		return pTemp;
	}

	static CObj* Create_Up_Wave(
		D3DXVECTOR3 _vPos,
		float _fCX,
		float _fCY,
		WAVE_TYPE _eWaveType
	)
	{
		CObj* pTemp = new T;
		pTemp->Set_Pos(_vPos);
		pTemp->Set_Scale(_fCX, _fCY);
		static_cast<CUpWave*>(pTemp)->Set_Wave_Type(_eWaveType);
		pTemp->Initialize();
		pTemp->Update_Rect();

		return pTemp;
	}

	static CObj* Create_Down_Wave(
		D3DXVECTOR3 _vPos,
		float _fCX,
		float _fCY,
		WAVE_TYPE _eWaveType
	)
	{
		CObj* pTemp = new T;
		pTemp->Set_Pos(_vPos);
		pTemp->Set_Scale(_fCX, _fCY);
		static_cast<CDownWave*>(pTemp)->Set_Wave_Type(_eWaveType);
		pTemp->Initialize();
		pTemp->Update_Rect();

		return pTemp;
	}

	static CObj* Create_Left_Wave(
		D3DXVECTOR3 _vPos,
		float _fCX,
		float _fCY,
		WAVE_TYPE _eWaveType
	)
	{
		CObj* pTemp = new T;
		pTemp->Set_Pos(_vPos);
		pTemp->Set_Scale(_fCX, _fCY);
		static_cast<CLeftWave*>(pTemp)->Set_Wave_Type(_eWaveType);
		pTemp->Initialize();
		pTemp->Update_Rect();

		return pTemp;
	}

	static CObj* Create_Right_Wave(
		D3DXVECTOR3 _vPos,
		float _fCX,
		float _fCY,
		WAVE_TYPE _eWaveType
	)
	{
		CObj* pTemp = new T;
		pTemp->Set_Pos(_vPos);
		pTemp->Set_Scale(_fCX, _fCY);
		static_cast<CRightWave*>(pTemp)->Set_Wave_Type(_eWaveType);
		pTemp->Initialize();
		pTemp->Update_Rect();

		return pTemp;
	}
};