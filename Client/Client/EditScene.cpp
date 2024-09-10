#include "pch.h"
#include "EditScene.h"
#include "TileMgr.h"

CEditScene::CEditScene()
{
}

CEditScene::~CEditScene()
{
	Release();
}

void CEditScene::Initialize()
{
	CTileMgr::Get_Instance()->Initialize();
}

int CEditScene::Update()
{
	CTileMgr::Get_Instance()->Update();
	return 0;
}

void CEditScene::Late_Update()
{
	CTileMgr::Get_Instance()->Late_Update();
}

void CEditScene::Render(HDC _hDC)
{
	CTileMgr::Get_Instance()->Render(_hDC);
}

void CEditScene::Release()
{
	CTileMgr::Destroy_Instance();
}
