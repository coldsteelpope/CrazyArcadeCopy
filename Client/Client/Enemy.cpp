#include "pch.h"
#include "Enemy.h"
#include "BmpMgr.h"

CEnemy::CEnemy()
{
}

CEnemy::~CEnemy()
{
    Release();
}

void CEnemy::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/ready.bmp", L"Enemy_Ready");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/wait.bmp", L"Enemy_Wait");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/up.bmp", L"Enemy_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/down.bmp", L"Enemy_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/left.bmp", L"Enemy_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/right.bmp", L"Enemy_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/trap.bmp", L"Enemy_Trap");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/die.bmp", L"Enemy_Die");


	m_vOriginPos = m_tInfo.vPos;
	m_vPrePos = m_tInfo.vPos;
	m_fSpeed = 2.0f;
}

int CEnemy::Update()
{
	if (m_bDead == false)
	{
		CObj::Update_Rect();
		CObj::Update_Collider_Rect();
		return OBJ_NO_EVENT;
	}
	else
	{
		return OBJ_NO_EVENT;
	}
}

void CEnemy::Late_Update()
{
	if (m_bDead == false)
	{
		CEnemy::Motion_Change();
		CEnemy::Manage_Status();
		CEnemy::Move_Frame();
	}
}

void CEnemy::Render(HDC _hDC)
{
	CObj::Update_Rect();
	CObj::Update_Collider_Rect();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
	GdiTransparentBlt(
		_hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255)
	);
}

void CEnemy::Release()
{
}



void CEnemy::Motion_Change()
{
	if (m_eObjPreStatus != m_eObjCurStatus)
	{
		switch (m_eObjCurStatus)
		{
		case OBJ_STATUS::OBJ_STATUS_READY:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 17;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 75;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIter = false;
			break;
		}
		case OBJ_STATUS::OBJ_STATUS_DIE:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIter = false;
			break;
		}
		case OBJ_STATUS::OBJ_STATUS_WAIT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIter = false;
			break;
		}
		}
		m_eObjPreStatus = m_eObjCurStatus;
	}
}

void CEnemy::Manage_Status()
{
	switch (m_eObjCurStatus)
	{
	case OBJ_STATUS::OBJ_STATUS_READY:
	{
		m_pFrameKey = L"Enemy_Ready";
		m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
		m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_READY;
		

		if (m_tFrame.bIter)
		{
			m_pFrameKey = L"Enemy_Wait";
			m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
			m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_WAIT;
			m_tInfo.fCX = PLAYER_WAIT_FCX;
			m_tInfo.fCY = PLAYER_WAIT_FCY;
			CObj::Update_Rect();
		}
		break;
	}
	case OBJ_STATUS::OBJ_STATUS_WAIT:
	{
		m_pFrameKey = L"Enemy_Wait";
		m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
		m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_WAIT;
		break;
	}
	case OBJ_STATUS::OBJ_STATUS_WALK_UP:
	{
		m_pFrameKey = L"Enemy_Up";
		m_eObjDir = OBJ_DIR::OBJ_DIR_TOP;
		m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_WALK_UP;
		break;
	}
	case OBJ_STATUS::OBJ_STATUS_WALK_DOWN:
	{
		m_pFrameKey = L"Enemy_Down";
		m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
		m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_WALK_DOWN;
		break;
	}
	case OBJ_STATUS::OBJ_STATUS_WALK_LEFT:
	{
		m_pFrameKey = L"Enemy_Left";
		m_eObjDir = OBJ_DIR::OBJ_DIR_LEFT;
		m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_WALK_LEFT;
		
		break;
	}
	case OBJ_STATUS::OBJ_STATUS_WALK_RIGHT:
	{
		m_pFrameKey = L"Enemy_Right";
		m_eObjDir = OBJ_DIR::OBJ_DIR_RIGHT;
		m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_WALK_RIGHT;

		break;
	}
	case OBJ_STATUS::OBJ_STATUS_TRAP:
	{
		m_pFrameKey = L"Enemy_Trap";
		m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
		m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_TRAP;

		break;
	}
	case OBJ_STATUS::OBJ_STATUS_DIE:
	{
		m_pFrameKey = L"Enemy_Die";
		m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
		m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_DIE;

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			m_bDead = true;
			// 서버에게 나 죽었다고 알리기
			int a = 3;
		}
		break;
	}
	}
}

void CEnemy::Set_Frame_Key()
{
	switch (m_eObjCurStatus)
	{
	case OBJ_STATUS::OBJ_STATUS_READY:
	{
		m_pFrameKey = L"Enemy_Ready";
		break;
	}
	case OBJ_STATUS::OBJ_STATUS_WAIT:
	{
		m_pFrameKey = L"Enemy_Wait";
		break;
	}
	case OBJ_STATUS::OBJ_STATUS_WALK_UP:
	{
		m_pFrameKey = L"Enemy_Up";
		break;
	}
	case OBJ_STATUS::OBJ_STATUS_WALK_DOWN:
	{
		m_pFrameKey = L"Enemy_Down";
		break;
	}
	case OBJ_STATUS::OBJ_STATUS_WALK_LEFT:
	{
		m_pFrameKey = L"Enemy_Left";
		break;
	}
	case OBJ_STATUS::OBJ_STATUS_WALK_RIGHT:
	{
		m_pFrameKey = L"Enemy_Right";
		break;
	}
	case OBJ_STATUS::OBJ_STATUS_TRAP:
	{
		m_pFrameKey = L"Enemy_Trap";
		break;
	}
	case OBJ_STATUS::OBJ_STATUS_DIE:
	{
		m_pFrameKey = L"Enemy_Die";
		break;
	}
	}
}
