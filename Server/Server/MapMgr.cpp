#include "pch.h"
#include "MapMgr.h"
#include "CAbstractFactory.h"


CMapMgr* CMapMgr::m_pInstance = nullptr;

CMapMgr::CMapMgr()
{
}

CMapMgr::~CMapMgr()
{
	Release();
}

void CMapMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CTile*>);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

bool CMapMgr::Load_Tiles()
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
		assert(false);
		return false;
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

		CTile* pTile = CAbstractFactory::Create_Tile(
			m_iTileID,
			tInfo.vPos,
			tInfo.fCX,
			tInfo.fCY,
			eTileType
		);
		m_vecTile.push_back(pTile);
		++m_iTileID;
	}
	::CloseHandle(hFile);
	return m_vecTile.size() != 0;
}
