#include "pch.h"
#include "WaterBomb.h"
#include "WaterWave.h"
#include "ObjMgr.h"
#include "CAbstractFactory.h"
#include "BmpMgr.h"

CWaterBomb::CWaterBomb()
{
}

CWaterBomb::~CWaterBomb()
{
	Release();
}

void CWaterBomb::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/bomb/idle.bmp", L"BOMB_IDLE");

	m_pFrameKey = L"BOMB_IDLE";
	m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_BOMB_IDLE;

	m_dwCanNotStepTime = GetTickCount();
	m_dwSurviveTime = GetTickCount();
	m_dwLimitTime = 3000;
}

int CWaterBomb::Update()
{
	if (m_bDead)
	{
		// socket 메시지 보낸 후에 죽임 처리하기
		CObjMgr::Get_Instance()->Add_Object(
			OBJ_ID_WAVE,
			CAbstractFactory<CWaterWave>::Create_Water_Wave(
				m_tInfo.vPos,
				m_tInfo.fCX,
				m_tInfo.fCY,
				2
			)
		);
		return OBJ_DEAD;
	}

	CObj::Update_Rect();
	CObj::Update_Water_Bomb_Collider();
	return OBJ_NO_EVENT;
}

void CWaterBomb::Late_Update()
{
	CWaterBomb::Motion_Change();
	CWaterBomb::Manage_Status();
	CWaterBomb::Move_Frame();

	DWORD dwCurrentTickCount = GetTickCount();
	if (m_dwSurviveTime + m_dwLimitTime < dwCurrentTickCount)
	{
		m_bDead = true;
	}

	if (m_dwCanNotStepTime + 1000 < dwCurrentTickCount)
	{
		m_bCanNotStep = true;
	}
}

void CWaterBomb::Render(HDC _hDC)
{
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
	//::Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CWaterBomb::Release()
{
}

void CWaterBomb::Motion_Change()
{
	if (m_eObjPreStatus != m_eObjCurStatus)
	{
		switch (m_eObjCurStatus)
		{
		case OBJ_STATUS::OBJ_STATUS_BOMB_IDLE:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
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

void CWaterBomb::Manage_Status()
{
	switch (m_eObjCurStatus)
	{
	case OBJ_STATUS::OBJ_STATUS_BOMB_IDLE:
	{
		m_pFrameKey = L"BOMB_IDLE";
		m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
		m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_BOMB_IDLE;

		m_tInfo.fCX = WATER_BOMB_IDLE_FCX;
		m_tInfo.fCY = WATER_BOMB_IDLE_FCY;
		CObj::Update_Rect();
		break;
	}
	}
}
