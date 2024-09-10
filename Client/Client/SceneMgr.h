#pragma once

class CScene;
class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();
public:
	int Update();
	void Late_Update();
	void Render(HDC _hDC);
	void Release();

public:
	void Change_Scene(SCENE_ID _eSceneID);
	SCENE_ID Get_Cur_Scene() { return m_eCurScene; }

public:
	static CSceneMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CSceneMgr;
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
	static CSceneMgr* m_pInstance;
	CScene* m_pActiveScene;

	SCENE_ID m_ePreScene;
	SCENE_ID m_eCurScene;
};

