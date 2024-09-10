#include "pch.h"
#include "UpWave.h"
#include "ObjMgr.h"
#include "CAbstractFactory.h"
#include "WaterWave.h"
#include "BmpMgr.h"
#include "SocketMgr.h"

CWaterWave::CWaterWave()
	: m_iBombRadius(0)
	, m_iValidLeftNumber(0)
	, m_iValidRightNumber(0)
	, m_iValidUpNumber(0)
	, m_iValidDownNumber(0)
	, m_iPivotIdx(0)
{
}

CWaterWave::~CWaterWave()
{
	Release();
}

void CWaterWave::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/bomb/pop.bmp", L"Water_Wave_Center");

	CWaterWave::Set_vTiles();
	CWaterWave::Add_Water_Up_Waves();
	CWaterWave::Add_Water_Down_Waves();
	CWaterWave::Add_Water_Right_Waves();
	CWaterWave::Add_Water_Left_Waves();

	m_pFrameKey = L"Water_Wave_Center";
	m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_BOMB;
	
}

int CWaterWave::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	CObj::Update_Rect();
	return OBJ_NO_EVENT;
}

void CWaterWave::Late_Update()
{
	CWaterWave::Motion_Change();
	CWaterWave::Manage_Status();
	CWaterWave::Move_Frame();
}

void CWaterWave::Render(HDC _hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
	GdiTransparentBlt(
		_hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tInfo.fCX * m_tFrame.iFrameStart,
		m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255)
	);
}

void CWaterWave::Release()
{
}

void CWaterWave::Set_vTiles()
{
	int idx = 0;
	list<CObj*> m_pObjList = CObjMgr::Get_Instance()->Get_List_By_Id(OBJ_ID::OBJ_ID_TILE);
	for (auto iter = m_pObjList.begin(); iter != m_pObjList.end(); ++iter)
	{
		vTiles.push_back((*iter));
		if ((*iter)->Get_INFO().vPos == m_tInfo.vPos)
		{
			m_iPivotIdx = idx;
		}
		++idx;
	}
}

void CWaterWave::Add_Water_Up_Waves()
{
	for (int i = 1; i <= m_iBombRadius; ++i)
	{
		int iCurrentIdx = m_iPivotIdx - (17 * i);
		if (iCurrentIdx < 0)
		{
			break;
		}

		CObj* pCurrentTile = vTiles[iCurrentIdx];
		if (static_cast<CTile*>(pCurrentTile)->Get_Tile_Type() == TILE_TYPE::WALL_TILE)
		{
			break;
		}

		if (i == m_iBombRadius)
		{
			CObjMgr::Get_Instance()->Add_Object(
				OBJ_ID_WAVE,
				CAbstractFactory<CUpWave>::Create_Up_Wave(
					pCurrentTile->Get_INFO().vPos,
					TILE_FCX, TILE_FCY,
					WAVE_TYPE::END_POINT_TYPE
				)
			);

			if (static_cast<CTile*>(pCurrentTile)->Get_Tile_Type() == TILE_TYPE::BLOCK_TILE)
			{
				static_cast<CTile*>(pCurrentTile)->Set_Tile_Type(TILE_TYPE::FLOOR_TILE);
				CSocketMgr::Get_Instance()->Send_Break_Tile_Message(
					static_cast<CTile*>(pCurrentTile)->Get_Tile_ID()
				);
				break;
			}
		}
		else
		{
			CObjMgr::Get_Instance()->Add_Object(
				OBJ_ID_WAVE,
				CAbstractFactory<CUpWave>::Create_Up_Wave(
					pCurrentTile->Get_INFO().vPos,
					TILE_FCX, TILE_FCY,
					WAVE_TYPE::MIDDLE_POINT_TYPE
				)
			);

			if (static_cast<CTile*>(pCurrentTile)->Get_Tile_Type() == TILE_TYPE::BLOCK_TILE)
			{
				static_cast<CTile*>(pCurrentTile)->Set_Tile_Type(TILE_TYPE::FLOOR_TILE);
				CSocketMgr::Get_Instance()->Send_Break_Tile_Message(
					static_cast<CTile*>(pCurrentTile)->Get_Tile_ID()
				);
				break;
			}
		}
	}
}

void CWaterWave::Add_Water_Down_Waves()
{
	for (int i = 1; i <= m_iBombRadius; ++i)
	{
		int iCurrentIdx = m_iPivotIdx + (17 * i);
		if (iCurrentIdx > 220)
		{
			break;
		}

		CObj* pCurrentTile = vTiles[iCurrentIdx];
		if (static_cast<CTile*>(pCurrentTile)->Get_Tile_Type() == TILE_TYPE::WALL_TILE)
		{
			break;
		}

		if (i == m_iBombRadius)
		{
			CObjMgr::Get_Instance()->Add_Object(
				OBJ_ID_WAVE,
				CAbstractFactory<CDownWave>::Create_Up_Wave(
					pCurrentTile->Get_INFO().vPos,
					TILE_FCX, TILE_FCY,
					WAVE_TYPE::END_POINT_TYPE
				)
			);

			if (static_cast<CTile*>(pCurrentTile)->Get_Tile_Type() == TILE_TYPE::BLOCK_TILE)
			{
				static_cast<CTile*>(pCurrentTile)->Set_Tile_Type(TILE_TYPE::FLOOR_TILE);
				CSocketMgr::Get_Instance()->Send_Break_Tile_Message(
					static_cast<CTile*>(pCurrentTile)->Get_Tile_ID()
				);
				break;
			}
		}
		else
		{
			CObjMgr::Get_Instance()->Add_Object(
				OBJ_ID_WAVE,
				CAbstractFactory<CDownWave>::Create_Up_Wave(
					pCurrentTile->Get_INFO().vPos,
					TILE_FCX, TILE_FCY,
					WAVE_TYPE::MIDDLE_POINT_TYPE
				)
			);

			if (static_cast<CTile*>(pCurrentTile)->Get_Tile_Type() == TILE_TYPE::BLOCK_TILE)
			{
				static_cast<CTile*>(pCurrentTile)->Set_Tile_Type(TILE_TYPE::FLOOR_TILE);
				CSocketMgr::Get_Instance()->Send_Break_Tile_Message(
					static_cast<CTile*>(pCurrentTile)->Get_Tile_ID()
				);
				break;
			}
		}
	}

}

void CWaterWave::Add_Water_Left_Waves()
{
	for (int i = 1; i <= m_iBombRadius; ++i)
	{
		int iCurrentIdx = m_iPivotIdx - i;		
		int iRowFirstIdx = 17 * (m_iPivotIdx / 17);
		if (iCurrentIdx < iRowFirstIdx)
		{
			break;
		}

		CObj* pCurrentTile = vTiles[iCurrentIdx];
		if (static_cast<CTile*>(pCurrentTile)->Get_Tile_Type() == TILE_TYPE::WALL_TILE)
		{
			break;
		}

		if (i == m_iBombRadius)
		{
			CObjMgr::Get_Instance()->Add_Object(
				OBJ_ID_WAVE,
				CAbstractFactory<CLeftWave>::Create_Left_Wave(
					pCurrentTile->Get_INFO().vPos,
					TILE_FCX, TILE_FCY,
					WAVE_TYPE::END_POINT_TYPE
				)
			);

			if (static_cast<CTile*>(pCurrentTile)->Get_Tile_Type() == TILE_TYPE::BLOCK_TILE)
			{
				static_cast<CTile*>(pCurrentTile)->Set_Tile_Type(TILE_TYPE::FLOOR_TILE);
				CSocketMgr::Get_Instance()->Send_Break_Tile_Message(
					static_cast<CTile*>(pCurrentTile)->Get_Tile_ID()
				);
				break;
			}
		}
		else
		{
			CObjMgr::Get_Instance()->Add_Object(
				OBJ_ID_WAVE,
				CAbstractFactory<CLeftWave>::Create_Left_Wave(
					pCurrentTile->Get_INFO().vPos,
					TILE_FCX, TILE_FCY,
					WAVE_TYPE::MIDDLE_POINT_TYPE
				)
			);

			if (static_cast<CTile*>(pCurrentTile)->Get_Tile_Type() == TILE_TYPE::BLOCK_TILE)
			{
				static_cast<CTile*>(pCurrentTile)->Set_Tile_Type(TILE_TYPE::FLOOR_TILE);
				CSocketMgr::Get_Instance()->Send_Break_Tile_Message(
					static_cast<CTile*>(pCurrentTile)->Get_Tile_ID()
				);
				break;
			}
		}
	}
}

void CWaterWave::Add_Water_Right_Waves()
{
	for (int i = 1; i <= m_iBombRadius; ++i)
	{
		int iCurrentIdx = m_iPivotIdx + i;
		int iRowLastIdx = (17 * (m_iPivotIdx / 17)) + 16;
		if (iCurrentIdx > iRowLastIdx)
		{
			break;
		}

		CObj* pCurrentTile = vTiles[iCurrentIdx];
		if (static_cast<CTile*>(pCurrentTile)->Get_Tile_Type() == TILE_TYPE::WALL_TILE)
		{
			break;
		}

		if (i == m_iBombRadius)
		{
			CObjMgr::Get_Instance()->Add_Object(
				OBJ_ID_WAVE,
				CAbstractFactory<CRightWave>::Create_Right_Wave(
					pCurrentTile->Get_INFO().vPos,
					TILE_FCX, TILE_FCY,
					WAVE_TYPE::END_POINT_TYPE
				)
			);

			if (static_cast<CTile*>(pCurrentTile)->Get_Tile_Type() == TILE_TYPE::BLOCK_TILE)
			{
				static_cast<CTile*>(pCurrentTile)->Set_Tile_Type(TILE_TYPE::FLOOR_TILE);
				CSocketMgr::Get_Instance()->Send_Break_Tile_Message(
					static_cast<CTile*>(pCurrentTile)->Get_Tile_ID()
				);
				break;
			}
		}
		else
		{
			CObjMgr::Get_Instance()->Add_Object(
				OBJ_ID_WAVE,
				CAbstractFactory<CRightWave>::Create_Right_Wave(
					pCurrentTile->Get_INFO().vPos,
					TILE_FCX, TILE_FCY,
					WAVE_TYPE::MIDDLE_POINT_TYPE
				)
			);

			if (static_cast<CTile*>(pCurrentTile)->Get_Tile_Type() == TILE_TYPE::BLOCK_TILE)
			{
				static_cast<CTile*>(pCurrentTile)->Set_Tile_Type(TILE_TYPE::FLOOR_TILE);
				CSocketMgr::Get_Instance()->Send_Break_Tile_Message(
					static_cast<CTile*>(pCurrentTile)->Get_Tile_ID()
				);
				break;
			}
		}
	}
}

void CWaterWave::Motion_Change()
{
	if (m_eObjPreStatus != m_eObjCurStatus)
	{
		switch (m_eObjCurStatus)
		{
		case OBJ_STATUS::OBJ_STATUS_BOMB:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 150;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIter = false;
			break;
		}
		}
		m_eObjPreStatus = m_eObjCurStatus;
	}
}

void CWaterWave::Manage_Status()
{
	switch (m_eObjCurStatus)
	{
	case OBJ_STATUS::OBJ_STATUS_BOMB:
	{
		m_pFrameKey = L"Water_Wave_Center";
		m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
		m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_BOMB;
		m_tInfo.fCX = WATER_CENTER_POP_FCX;
		m_tInfo.fCY = WATER_CENTER_POP_FCY;
		CObj::Update_Rect();
		
		if (m_tFrame.bIter)
		{
			m_bDead = true;
		}
		break;
	}
	}
}
