#pragma once
class CObj;
class CCollisionMgr
{
private:
	CCollisionMgr();
	virtual ~CCollisionMgr();
public:
	void Collide_Player_Collider_With_Enemy_Collider_When_Trapped(list<CObj*> m_pPlayerList, list<CObj*> m_pEnemyList);
	void Collide_Player_Collider_With_Water_Bomb(list<CObj*> m_pPlayerList, list<CObj*> m_pWaterBombList);
	void Collide_Player_Collider_With_Wave(list<CObj*> m_pPlayerList, list<CObj*> m_pWaveList);
	void Collide_Player_Collider_With_Tile(list<CObj*> m_pPlayerList, list<CObj*> m_pTileList);

	bool Check_Sphere(CObj* _pDest, CObj* _pSrc);
	bool Check_Rect(CObj* _pDest, CObj* _pDown, float* _fCX, float* _fCY);
	

public:
	static CCollisionMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CCollisionMgr;
		}
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CCollisionMgr* m_pInstance;
};

