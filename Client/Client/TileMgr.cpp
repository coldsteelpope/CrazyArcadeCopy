#include "pch.h"
#include "TileMgr.h"
#include "CAbstractFactory.h"
#include "Tile.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"

CTileMgr* CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
}

CTileMgr::~CTileMgr()
{

}

void CTileMgr::Initialize()
{
	int iTheNumberOfHeightTiles = (WINCY / TILE_FCY) + 2;
	int iThenumberOfWidthTiles = (WINCX / TILE_FCX) + 2;
	m_vecTile.reserve(iTheNumberOfHeightTiles * iThenumberOfWidthTiles);
	for (int i = -1; i < iTheNumberOfHeightTiles - 1; ++i)
	{
		for (int j = -1; j < iThenumberOfWidthTiles - 1; ++j)
		{
			float fX = float((TILE_FCX >> 1) + TILE_OFFSET_FCX + (TILE_FCX * j));
			float fY = float((TILE_FCY >> 1) + TILE_OFFSET_FCY + (TILE_FCY * i));
			CObj* pTile = CAbstractFactory<CTile>::Create_Tile(
				D3DXVECTOR3{ fX, fY, 0.f},
				TILE_FCX,
				TILE_FCY,
				TILE_TYPE::FLOOR_TILE
			);
			m_vecTile.push_back(pTile);
		}
	}
}

void CTileMgr::Update()
{
	Key_Input();
	for (auto& pTile : m_vecTile)
	{
		pTile->Update();
	}
}

void CTileMgr::Late_Update()
{
	
	for (auto& pTile : m_vecTile)
	{
		pTile->Late_Update();
	}
}

void CTileMgr::Render(HDC _hDC)
{
	switch (CSceneMgr::Get_Instance()->Get_Cur_Scene())
	{
	case SCENE_ID::SCENE_ID_EDIT_SCENE:
	{
		for (int i = TILE_OFFSET_FCY - TILE_FCY; i <= WINCY - TILE_OFFSET_FCY; i += TILE_FCY)
		{
			for (int j = TILE_OFFSET_FCX - TILE_FCX; j <= WINCX - TILE_OFFSET_FCX; j += TILE_FCX)
			{
				HPEN redPen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				HPEN oldPen = (HPEN)::SelectObject(_hDC, redPen);
				::MoveToEx(_hDC, j, i, nullptr);
				::LineTo(_hDC, j + 52, i);
				::LineTo(_hDC, j + 52, i + 52);
				::LineTo(_hDC, j, i + 52);
				::LineTo(_hDC, j, i);
				::SelectObject(_hDC, oldPen);
				::DeleteObject(redPen);
			}
		}
		break;
	}
	}
	


	
	for (CObj* pTile : m_vecTile)
	{
		pTile->Render(_hDC);
	}
}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

void CTileMgr::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		m_eCurrentTileType = TILE_TYPE::BLOCK_TILE;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('W'))
	{
		m_eCurrentTileType = TILE_TYPE::WALL_TILE;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('E'))
	{
		m_eCurrentTileType = TILE_TYPE::FLOOR_TILE;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		Save_Tile();
	}

	if (CKeyMgr::Get_Instance()->Key_Down('L'))
	{
		Load_Tile();
	}

	if (CKeyMgr::Get_Instance()->Key_Press(VK_LBUTTON))
	{
		POINT ps;
		GetCursorPos(&ps);
		ScreenToClient(g_hWnd, &ps);
		Picking_Tile(ps);
	}
}

void CTileMgr::Picking_Tile(POINT _tPt)
{
	for (int i = 0; i < m_vecTile.size(); ++i)
	{
		bool m_bValidX = _tPt.x >= m_vecTile[i]->Get_Rect().left && _tPt.x <= m_vecTile[i]->Get_Rect().right;
		bool m_bValidY = _tPt.y >= m_vecTile[i]->Get_Rect().top && _tPt.y <= m_vecTile[i]->Get_Rect().bottom;
		if (m_bValidX && m_bValidY)
		{
			static_cast<CTile*>(m_vecTile[i])->Set_Tile_Type(m_eCurrentTileType);
			return;
		}
	}
}

void CTileMgr::Save_Tile()
{
	HANDLE hFile = CreateFile(
		L"../Data/Map.dat",
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"save failed", _T("error"), MB_OK);
		return;
	}

	DWORD dwByte(0);
	TILE_TYPE eTileType(TILE_TYPE_END);

	for (auto& pTile : m_vecTile)
	{
		eTileType = static_cast<CTile*>(pTile)->Get_Tile_Type();
		WriteFile(hFile, &(pTile->Get_INFO()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &(eTileType), sizeof(int), &dwByte, nullptr);
	}

	::CloseHandle(hFile);
	MessageBox(g_hWnd, L"TILE SAVE COMPLETE", L"SUCCESS", MB_OKCANCEL);
}



void CTileMgr::Load_Tile()
{
	HANDLE hFile = CreateFile(L"../Data/Map.dat",
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"LoadFailed", _T("error"), MB_OK);
		return;
	}
	
	DWORD dwByte(0);
	TILE_TYPE eTileType(TILE_TYPE_END);
	INFO tInfo{};

	Release();
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &eTileType, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
		{
			break;
		}

		CObj* pTile = CAbstractFactory<CTile>::Create_Tile(
			tInfo.vPos,
			tInfo.fCX,
			tInfo.fCY,
			eTileType
		);
		m_vecTile.push_back(pTile);
	}
	::CloseHandle(hFile);
	//MessageBox(g_hWnd, L"TILE LOAD COMPLETE", L"SUCCESS", MB_OKCANCEL);
}

void CTileMgr::Load_Tile_To_ObjMgr()
{
	Load_Tile();
	for (int i = 0; i < m_vecTile.size(); ++i)
	{
		m_vecTile[i]->Initialize();
		m_vecTile[i]->Update();

		CObjMgr::Get_Instance()->Add_Object(
			OBJ_ID_TILE, m_vecTile[i]
		);
	}
}

