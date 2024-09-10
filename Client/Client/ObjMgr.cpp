#include "pch.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{

}

CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Add_Object(OBJ_ID _eObjId, CObj* _pObj)
{
	m_pObjList[_eObjId].push_back(_pObj);
}

void CObjMgr::Delete_Enemy(int m_iClientID)
{
	for (auto iter = m_pObjList[OBJ_ID::OBJ_ID_ENEMY].begin(); iter != m_pObjList[OBJ_ID::OBJ_ID_ENEMY].end();)
	{
		if ((*iter)->Get_ClientID() == m_iClientID)
		{
			Safe_Delete<CObj*>((*iter));
			iter = m_pObjList[OBJ_ID::OBJ_ID_ENEMY].erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CObjMgr::Update()
{
	for (int i = 0; i < OBJ_ID_END; ++i)
	{
		for (auto iter = m_pObjList[i].begin(); iter != m_pObjList[i].end();)
		{
			int iResult = (*iter)->Update();
			if (iResult == OBJ_DEAD)
			{
				Safe_Delete<CObj*>((*iter));
				iter = m_pObjList[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}

void CObjMgr::Late_Update()
{
	for (int i = 0; i < OBJ_ID_END; ++i)
	{
		for (auto iter = m_pObjList[i].begin(); iter != m_pObjList[i].end(); ++iter)
		{
			(*iter)->Late_Update();
		}
	}

	CCollisionMgr::Get_Instance()->Collide_Player_Collider_With_Enemy_Collider_When_Trapped(m_pObjList[OBJ_ID::OBJ_ID_PLAYER], m_pObjList[OBJ_ID::OBJ_ID_ENEMY]);
	CCollisionMgr::Get_Instance()->Collide_Player_Collider_With_Tile(m_pObjList[OBJ_ID::OBJ_ID_PLAYER], m_pObjList[OBJ_ID::OBJ_ID_TILE]);
	CCollisionMgr::Get_Instance()->Collide_Player_Collider_With_Wave(m_pObjList[OBJ_ID::OBJ_ID_PLAYER], m_pObjList[OBJ_ID::OBJ_ID_WAVE]);
	CCollisionMgr::Get_Instance()->Collide_Player_Collider_With_Water_Bomb(m_pObjList[OBJ_ID::OBJ_ID_PLAYER], m_pObjList[OBJ_ID::OBJ_ID_WATER_BOMB]);
}

void CObjMgr::Render(HDC _hDC)
{
	for (int i = 0; i < OBJ_ID_END; ++i)
	{
		for (auto iter = m_pObjList[i].begin(); iter != m_pObjList[i].end(); ++iter)
		{
			(*iter)->Render(_hDC);
		}
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJ_ID_END; ++i)
	{
		if (i == OBJ_ID_TILE)
		{
			continue;
		}
		for_each(m_pObjList[i].begin(), m_pObjList[i].end(), Safe_Delete<CObj*>);
		m_pObjList[i].clear();
	}
}

list<CObj*>& CObjMgr::Get_List_By_Id(OBJ_ID _eObjId)
{
	return m_pObjList[_eObjId];
}

void CObjMgr::Clear_All_Object_List()
{
	for (size_t i = 0; i < OBJ_ID_END; ++i)
	{
		for_each(m_pObjList[i].begin(), m_pObjList[i].end(), Safe_Delete<CObj*>);
		m_pObjList[i].clear();
	}
}
