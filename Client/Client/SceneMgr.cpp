#include "pch.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "PlayScene.h"
#include "EditScene.h"
#include "ObjMgr.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pActiveScene(nullptr)
	, m_ePreScene(SCENE_ID::SCENE_ID_END)
	, m_eCurScene(SCENE_ID::SCENE_ID_END)
{

}

CSceneMgr::~CSceneMgr()
{
	Release();
}

int CSceneMgr::Update()
{
	m_pActiveScene->Update();
	return 0;
}

void CSceneMgr::Late_Update()
{
	m_pActiveScene->Late_Update();
}

void CSceneMgr::Render(HDC _hDC)
{
	m_pActiveScene->Render(_hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete<CScene*>(m_pActiveScene);
}

void CSceneMgr::Change_Scene(SCENE_ID _eSceneID)
{
	m_eCurScene = _eSceneID;
	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete<CScene*>(m_pActiveScene);
		switch (m_eCurScene)
		{
		case SCENE_ID::SCENE_ID_PLAY_SCENE:
		{
			m_pActiveScene = new CPlayScene;
			break;
		}
		case SCENE_ID::SCENE_ID_EDIT_SCENE:
		{
			m_pActiveScene = new CEditScene;
			break;
		}
		}
		CObjMgr::Get_Instance()->Clear_All_Object_List();
		m_pActiveScene->Initialize();
		m_ePreScene = m_eCurScene;
	}
}
