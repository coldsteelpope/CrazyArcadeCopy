#include "pch.h"
#include "Tile.h"
#include "SceneMgr.h"
#include "BmpMgr.h"

CTile::CTile()
{
}

CTile::~CTile()
{
}

void CTile::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/tile/tile_9.bmp", L"FLOOR_TILE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/tile/block_2.bmp", L"BLOCK_TILE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/tile/object_2.bmp", L"WALL_TILE");
}

int CTile::Update()
{
	CObj::Update_Rect();
	CObj::Update_Block_Collider_Rect();
	return OBJ_NO_EVENT;
}

void CTile::Late_Update()
{
	
}

void CTile::Render(HDC _hDC)
{
	// Print Collider

	switch (CSceneMgr::Get_Instance()->Get_Cur_Scene())
	{
	case SCENE_ID::SCENE_ID_EDIT_SCENE:
	{
		switch (m_eTileType)
		{
		case TILE_TYPE::FLOOR_TILE:
		{
			HBRUSH GreenBrush = ::CreateSolidBrush(RGB(0, 255, 0));
			HBRUSH oldBrush = (HBRUSH)::SelectObject(_hDC, GreenBrush);
			::Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
			::SelectObject(_hDC, oldBrush);
			::DeleteObject(GreenBrush);

			break;
		}
		case TILE_TYPE::BLOCK_TILE:
		{
			HBRUSH blueBrush = ::CreateSolidBrush(RGB(0, 0, 255));
			HBRUSH oldBrush = (HBRUSH)::SelectObject(_hDC, blueBrush);
			::Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
			::SelectObject(_hDC, oldBrush);
			::DeleteObject(blueBrush);

			break;
		}
		case TILE_TYPE::WALL_TILE:
		{
			HBRUSH redBrush = ::CreateSolidBrush(RGB(255, 0, 0));
			HBRUSH oldBrush = (HBRUSH)::SelectObject(_hDC, redBrush);
			::Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
			::SelectObject(_hDC, oldBrush);
			::DeleteObject(redBrush);

			break;
		}
		}
		break;
	}
	default:
	{
		// sprite 출력하기
		switch (m_eTileType)
		{
		case TILE_TYPE::FLOOR_TILE:
		{
			HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"FLOOR_TILE");
			BitBlt(_hDC, m_tRect.left, m_tRect.top, TILE_FCX, TILE_FCY, hMemDC, 0, 0, SRCCOPY);
			break;
		}
		case TILE_TYPE::BLOCK_TILE:
		{

			HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BLOCK_TILE");
			GdiTransparentBlt(
				_hDC,
				m_tRect.left - 8,
				m_tRect.top - 15,
				BLOCK_TILE_FCX,
				BLOCK_TILE_FCY,
				hMemDC,
				0, 0,
				BLOCK_TILE_FCX,
				BLOCK_TILE_FCY,
				RGB(255, 0, 255)
			);
			//::Rectangle(_hDC, m_tColliderRect.left, m_tColliderRect.top, m_tColliderRect.right, m_tColliderRect.bottom);

			
			break;
		}
		case TILE_TYPE::WALL_TILE:
		{


			HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"WALL_TILE");
			GdiTransparentBlt(
				_hDC,
				m_tRect.left - 2,
				m_tRect.top - 10,
				WALL_TILE_FCX,
				WALL_TILE_FCY,
				hMemDC,
				0, 0,
				WALL_TILE_FCX,
				WALL_TILE_FCY,
				RGB(255, 0, 255)
			);

			
			break;
		}
		}
	}
	}


}

void CTile::Release()
{
}
