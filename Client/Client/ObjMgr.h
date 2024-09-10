#pragma once

class CObj;
class CObjMgr
{
private:
	CObjMgr();
	virtual ~CObjMgr();

public:
	void Add_Object(OBJ_ID _eObjId, CObj* _pObj);
	void Delete_Enemy(int m_iClientID);

	void Update();
	void Late_Update();
	void Render(HDC _hDC);
	void Release();

public:
	void Clear_All_Object_List();
	list<CObj*>& Get_List_By_Id(OBJ_ID _eObjId);

public:
	static CObjMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CObjMgr;
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
	static CObjMgr* m_pInstance;
	list<CObj*> m_pObjList[OBJ_ID_END];
};

