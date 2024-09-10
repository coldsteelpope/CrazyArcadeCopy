#include "pch.h"
#include "PlayScene.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "Player.h"
#include "SocketMgr.h"
#include "CAbstractFactory.h"


CPlayScene::CPlayScene()
{
	
}

CPlayScene::~CPlayScene()
{
	Release();
}

void CPlayScene::Initialize()
{
	CSocketMgr::Get_Instance()->Initialize();
}

int CPlayScene::Update()
{
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CPlayScene::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CPlayScene::Render(HDC _hDC)
{
	CObjMgr::Get_Instance()->Render(_hDC);	
}

void CPlayScene::Release()
{
	CObjMgr::Destroy_Instance();
	CSocketMgr::Destroy_Instance();
}
