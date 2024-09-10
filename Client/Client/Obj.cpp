#include "pch.h"
#include "Obj.h"

CObj::CObj() : m_fSpeed(0.f)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	D3DXMatrixIdentity(&m_tInfo.matWorld);
}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left		= (long)(m_tInfo.vPos.x - m_tInfo.fCX / 2.0f);
	m_tRect.top			= (long)(m_tInfo.vPos.y - m_tInfo.fCY / 2.0f);
	m_tRect.right		= (long)(m_tInfo.vPos.x + m_tInfo.fCX / 2.0f);
	m_tRect.bottom		= (long)(m_tInfo.vPos.y + m_tInfo.fCY / 2.0f);
}

void CObj::Update_Collider_Rect()
{
	m_tColliderInfo.fCX = PLAYER_COLLIDER_FCX;
	m_tColliderInfo.fCY = PLAYER_COLLIDER_FCY;
	m_tColliderInfo.vPos = m_tInfo.vPos;
	m_tColliderInfo.vLook = m_tInfo.vLook;
	m_tColliderInfo.vPos.y += 12;

	m_tColliderRect.left	= (long)(m_tColliderInfo.vPos.x - m_tColliderInfo.fCX / 2.0f);
	m_tColliderRect.top		= (long)(m_tColliderInfo.vPos.y - m_tColliderInfo.fCY / 2.0f);
	m_tColliderRect.right	= (long)(m_tColliderInfo.vPos.x + m_tColliderInfo.fCX / 2.0f);
	m_tColliderRect.bottom	= (long)(m_tColliderInfo.vPos.y + m_tColliderInfo.fCY / 2.0f);

}

void CObj::Update_Block_Collider_Rect()
{
	m_tColliderInfo.fCX = TILE_FCX - 4;
	m_tColliderInfo.fCY = TILE_FCY - 4;
	m_tColliderInfo.vPos = m_tInfo.vPos;
	m_tColliderInfo.vLook = m_tInfo.vLook;
	m_tColliderInfo.vPos.y -= 4;

	m_tColliderRect.left	= (long)(m_tColliderInfo.vPos.x - m_tColliderInfo.fCX / 2.0f);
	m_tColliderRect.top		= (long)(m_tColliderInfo.vPos.y - m_tColliderInfo.fCY / 2.0f);
	m_tColliderRect.right	= (long)(m_tColliderInfo.vPos.x + m_tColliderInfo.fCX / 2.0f);
	m_tColliderRect.bottom	= (long)(m_tColliderInfo.vPos.y + m_tColliderInfo.fCY / 2.0f);

}

void CObj::Update_Water_Bomb_Collider()
{
	m_tColliderInfo.fCX = TILE_FCX - 4;
	m_tColliderInfo.fCY = TILE_FCY - 4;
	m_tColliderInfo.vPos = m_tInfo.vPos;
	m_tColliderInfo.vLook = m_tInfo.vLook;
	m_tColliderInfo.vPos.y -= 4;

	m_tColliderRect.left = (long)(m_tColliderInfo.vPos.x - m_tColliderInfo.fCX / 2.0f);
	m_tColliderRect.top = (long)(m_tColliderInfo.vPos.y - m_tColliderInfo.fCY / 2.0f);
	m_tColliderRect.right = (long)(m_tColliderInfo.vPos.x + m_tColliderInfo.fCX / 2.0f);
	m_tColliderRect.bottom = (long)(m_tColliderInfo.vPos.y + m_tColliderInfo.fCY / 2.0f);
}

void CObj::Update_Player_Tile_Collider_Rect()
{
	m_tPlayerTileColliderInfo.vPos = m_tInfo.vPos;
	m_tPlayerTileColliderInfo.vLook = m_tInfo.vLook;
	m_tPlayerTileColliderInfo.fCX = PLAYER_TILE_COLLIDER_FCX;
	m_tPlayerTileColliderInfo.fCY = PLAYER_TILE_COLLIDER_FCY;
	m_tPlayerTileColliderInfo.vPos.y += 10.0f;

	m_tPlayerTileColliderRect.left = (long)(m_tPlayerTileColliderInfo.vPos.x - m_tPlayerTileColliderInfo.fCX / 2.0f);
	m_tPlayerTileColliderRect.top = (long)(m_tPlayerTileColliderInfo.vPos.y - m_tPlayerTileColliderInfo.fCY / 2.0f);
	m_tPlayerTileColliderRect.right = (long)(m_tPlayerTileColliderInfo.vPos.x + m_tPlayerTileColliderInfo.fCX / 2.0f);
	m_tPlayerTileColliderRect.bottom = (long)(m_tPlayerTileColliderInfo.vPos.y + m_tPlayerTileColliderInfo.fCY / 2.0f);
}

void CObj::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.bIter = true;
		}
		m_tFrame.dwTime = GetTickCount();
	}
}
