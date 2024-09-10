#include "pch.h"
#include "Obj.h"
#include "Tile.h"
#include "CollisionMgr.h"
#include "WaterBomb.h"
#include "SocketMgr.h"

CCollisionMgr* CCollisionMgr::m_pInstance = nullptr;

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collide_Player_Collider_With_Enemy_Collider_When_Trapped(list<CObj*> m_pPlayerList, list<CObj*> m_pEnemyList)
{
	for (auto pPlayer : m_pPlayerList)
	{
		for (auto pEnemy : m_pEnemyList)
		{
			if (pPlayer->Get_Obj_Cur_Status() == OBJ_STATUS::OBJ_STATUS_TRAP)
			{
				if (Check_Sphere(pPlayer, pEnemy))
				{
					pPlayer->Set_Obj_Cur_Status(OBJ_STATUS::OBJ_STATUS_DIE);
					CSocketMgr::Get_Instance()->Send_Dead_Message(pPlayer->Get_ClientID(), pPlayer->Get_INFO(), pPlayer->Get_Frame());
				}
			}
		}
	}
}

void CCollisionMgr::Collide_Player_Collider_With_Water_Bomb(list<CObj*> m_pPlayerList, list<CObj*> m_pWaterBombList)
{
	for (auto pPlayer : m_pPlayerList)
	{
		for (auto pWaterBomb : m_pWaterBombList)
		{
			float pX(0.f), pY(0.f);			
			if (Check_Rect(pPlayer, pWaterBomb, &pX, &pY) && static_cast<CWaterBomb*>(pWaterBomb)->Get_Can_Not_Step())
			{
				if (pX > pY)
				{
					// 상하충돌
					if (pPlayer->Get_Collider_INFO().vPos.y < pWaterBomb->Get_INFO().vPos.y)
					{
						// 상 충돌
						pPlayer->Push_Top(pY);
					}
					else
					{
						// 하 충돌
						pPlayer->Push_Bottom(pY);
					}
				}
				else
				{
					// 좌우충돌
					if (pPlayer->Get_Collider_INFO().vPos.x < pWaterBomb->Get_INFO().vPos.x)
					{
						// 좌 충돌
						pPlayer->Push_Left(pX);
					}
					else
					{
						// 우 충돌
						pPlayer->Push_Right(pX);
					}
				}
			}
		}
	}
}

void CCollisionMgr::Collide_Player_Collider_With_Wave(list<CObj*> m_pPlayerList, list<CObj*> m_pWaveList)
{
	for (auto pPlayer : m_pPlayerList)
	{
		for (auto pWave : m_pWaveList)
		{
			RECT temp;
			RECT tPlayerCollider = pPlayer->Get_Collider();
			RECT tWaveRect = pWave->Get_Rect();
			if (IntersectRect(&temp, &tPlayerCollider, &tWaveRect))
			{
				pPlayer->Set_Obj_Cur_Status(OBJ_STATUS::OBJ_STATUS_TRAP);
			}
		}
	}
}

void CCollisionMgr::Collide_Player_Collider_With_Tile(list<CObj*> m_pPlayerList, list<CObj*> m_pTileList)
{
	for (auto pPlayer : m_pPlayerList)
	{
		for (auto pTile : m_pTileList)
		{
			float pX(0.f), pY(0.f);
			switch (static_cast<CTile*>(pTile)->Get_Tile_Type())
			{
			case TILE_TYPE::WALL_TILE:
			{
				if (Check_Rect(pPlayer, pTile, &pX, &pY))
				{
					if (pX > pY)
					{
						// 상하충돌
						if (pPlayer->Get_Collider_INFO().vPos.y < pTile->Get_Collider_INFO().vPos.y)
						{
							// 상 충돌
							pPlayer->Push_Top(pY);
						}
						else
						{
							// 하 충돌
							pPlayer->Push_Bottom(pY);
						}
					}
					else
					{
						// 좌우충돌
						if (pPlayer->Get_Collider_INFO().vPos.x < pTile->Get_Collider_INFO().vPos.x)
						{
							// 좌 충돌
							pPlayer->Push_Left(pX);
						}
						else
						{
							// 우 충돌
							pPlayer->Push_Right(pX);
						}
					}
				}
				break;
			}
			case TILE_TYPE::BLOCK_TILE:
			{
				if (Check_Rect(pPlayer, pTile, &pX, &pY))
				{
					if (pX > pY)
					{
						// 상하충돌
						if (pPlayer->Get_Collider_INFO().vPos.y < pTile->Get_Collider_INFO().vPos.y)
						{
							// 상 충돌
							pPlayer->Push_Top(pY);
						}
						else
						{
							// 하 충돌
							pPlayer->Push_Bottom(pY);
						}
					}
					else
					{
						// 좌우충돌
						if (pPlayer->Get_Collider_INFO().vPos.x < pTile->Get_Collider_INFO().vPos.x)
						{
							// 좌 충돌
							pPlayer->Push_Left(pX);
							
						}
						else
						{
							// 우 충돌
							pPlayer->Push_Right(pX);
						}
					}
				}
				break;
			}
			}
		}
	}
}


bool CCollisionMgr::Check_Sphere(CObj* _pDest, CObj* _pSrc)
{
	float fWidth = abs(_pDest->Get_Collider_INFO().vPos.x - _pSrc->Get_Collider_INFO().vPos.x);
	float fHeight = abs(_pDest->Get_Collider_INFO().vPos.y - _pSrc->Get_Collider_INFO().vPos.y);
	float fDiagonal = sqrt((fWidth * fWidth) + (fHeight * fHeight));

	float fRadius = (_pDest->Get_Collider_INFO().fCX + _pSrc->Get_Collider_INFO().fCX) * 0.5f;
	return fRadius >= fDiagonal;
}

bool CCollisionMgr::Check_Rect(CObj* _pDest, CObj* _pSrc, float* pX, float* pY)
{
	float fWidth = abs(_pDest->Get_Collider_INFO().vPos.x - _pSrc->Get_Collider_INFO().vPos.x);
	float fHeight = abs(_pDest->Get_Collider_INFO().vPos.y - _pSrc->Get_Collider_INFO().vPos.y);
 
	float fRadiusX = (_pDest->Get_Collider_INFO().fCX + _pSrc->Get_Collider_INFO().fCX) * 0.5f;
	float fRadiusY = (_pDest->Get_Collider_INFO().fCY + _pSrc->Get_Collider_INFO().fCY) * 0.5f;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;
		return true;
	}
	return false;
}


