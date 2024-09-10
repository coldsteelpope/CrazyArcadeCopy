#include "pch.h"
#include "Player.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "WaterBomb.h"
#include "ObjMgr.h"
#include "SocketMgr.h"
#include "CAbstractFactory.h"


CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/ready.bmp", L"Player_Ready");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/wait.bmp", L"Player_Wait");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/up.bmp", L"Player_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/down.bmp", L"Player_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/left.bmp", L"Player_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/right.bmp", L"Player_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/trap.bmp", L"Player_Trap");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/die.bmp", L"Player_Die");
	
	m_vOriginPos = m_tInfo.vPos;
	m_vPrePos = m_tInfo.vPos;
	m_eObjCurStatus = OBJ_STATUS_READY;
	m_pFrameKey = L"Player_Ready";
	m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
	m_fSpeed = 4.5f;
}

int CPlayer::Update()
{
	if (m_bDead == false)
	{
		switch (m_eObjCurStatus)
		{
		case OBJ_STATUS::OBJ_STATUS_READY:
		{
			break;
		}
		case OBJ_STATUS::OBJ_STATUS_DIE:
		{
			break;
		}
		default:
		{
			Key_Input();
		}
		}

		CObj::Update_Rect();
		CObj::Update_Collider_Rect();
		return OBJ_NO_EVENT;
	}
	else
	{
		return OBJ_DEAD;
	}
}

void CPlayer::Late_Update()
{
	if (m_bDead == false)
	{
		CPlayer::Motion_Change();
		CPlayer::Manage_Status();
		CPlayer::Move_Frame();

		if (m_vPrePos != m_tInfo.vPos)
		{
			CSocketMgr::Get_Instance()->Send_Move_Message(m_iClientID, m_tInfo, m_tFrame, m_eObjCurStatus);
			m_vPrePos = m_tInfo.vPos;
		}
	}
}

void CPlayer::Render(HDC _hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
	GdiTransparentBlt(
		_hDC,
		m_tRect.left,
		m_tRect.top,
		m_tInfo.fCX,
		m_tInfo.fCY,
		hMemDC,
		m_tInfo.fCX * m_tFrame.iFrameStart,
		m_tInfo.fCY * m_tFrame.iMotion,
		m_tInfo.fCX,
		m_tInfo.fCY,
		RGB(255, 0, 255)
	);

	// Print Collider
	//::Rectangle(_hDC, m_tColliderRect.left, m_tColliderRect.top, m_tColliderRect.right, m_tColliderRect.bottom);
}

void CPlayer::Release()
{
	
}

void CPlayer::Motion_Change()
{
	if (m_eObjPreStatus != m_eObjCurStatus)
	{
		switch (m_eObjCurStatus)
		{
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
		case OBJ_STATUS::OBJ_STATUS_WALK_UP:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIter = false;

			break;
		}
		case OBJ_STATUS::OBJ_STATUS_WALK_DOWN:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIter = false;

			break;
		}
		case OBJ_STATUS::OBJ_STATUS_WALK_LEFT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIter = false;

			break;
		}
		case OBJ_STATUS::OBJ_STATUS_WALK_RIGHT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIter = false;

			break;
		}
		case OBJ_STATUS::OBJ_STATUS_TRAP:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 250;
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
		case OBJ_STATUS::OBJ_STATUS_READY:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 17;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 75;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIter = false;

			if (m_bDead)
			{
				m_bDead = true;
			}
			break;
		}
		}
		m_eObjPreStatus = m_eObjCurStatus;
	}
}

void CPlayer::Manage_Status()
{
	switch (m_eObjCurStatus)
	{
	case OBJ_STATUS::OBJ_STATUS_READY:
	{
		m_pFrameKey = L"Player_Ready";
		m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
		m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_READY;

		if (m_tFrame.bIter)
		{
			m_pFrameKey = L"Player_Wait";
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
		m_pFrameKey = L"Player_Wait";
		m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
		m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_WAIT;

		CSocketMgr::Get_Instance()->Send_Wait_Message(m_iClientID, m_tInfo, m_tFrame);
		break;
	}
	case OBJ_STATUS::OBJ_STATUS_WALK_UP:
	{
		m_pFrameKey = L"Player_Up";
		m_eObjDir = OBJ_DIR::OBJ_DIR_TOP;
		m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_WALK_UP;
		m_tInfo.fCX = PLAYER_WAIT_FCX;
		m_tInfo.fCY = PLAYER_WAIT_FCY;
		CObj::Update_Rect();
		break;
	}
	case OBJ_STATUS::OBJ_STATUS_WALK_LEFT:
	{
		m_pFrameKey = L"Player_Left";
		m_eObjDir = OBJ_DIR::OBJ_DIR_LEFT;
		m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_WALK_LEFT;

		m_tInfo.fCX = PLAYER_WAIT_FCX;
		m_tInfo.fCY = PLAYER_WAIT_FCY;
		CObj::Update_Rect();
		break;
	}
	case OBJ_STATUS::OBJ_STATUS_WALK_RIGHT:
	{
		m_pFrameKey = L"Player_Right";
		m_eObjDir = OBJ_DIR::OBJ_DIR_RIGHT;
		m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_WALK_RIGHT;
		m_tInfo.fCX = PLAYER_WAIT_FCX;
		m_tInfo.fCY = PLAYER_WAIT_FCY;
		CObj::Update_Rect();
		break;
	}
	case OBJ_STATUS::OBJ_STATUS_WALK_DOWN:
	{
		m_pFrameKey = L"Player_Down";
		m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
		m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_WALK_DOWN;
		m_tInfo.fCX = PLAYER_WAIT_FCX;
		m_tInfo.fCY = PLAYER_WAIT_FCY;
		CObj::Update_Rect();
		break;
	}
	case OBJ_STATUS::OBJ_STATUS_TRAP:
	{
		m_pFrameKey = L"Player_Trap";
		m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
		m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_TRAP;
		m_tInfo.fCX = PLAYER_TRAP_FCX;
		m_tInfo.fCY = PLAYER_TRAP_FCY;
		CObj::Update_Rect();
		CSocketMgr::Get_Instance()->Send_Trap_Message(m_iClientID, m_tInfo, m_tFrame);

		if (m_tFrame.bIter)
		{
			m_pFrameKey = L"Player_Die";
			m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
			m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_DIE;
			m_tInfo.fCX = PLAYER_DIE_FCX;
			m_tInfo.fCY = PLAYER_DIE_FCY;
			CSocketMgr::Get_Instance()->Send_Dead_Message(m_iClientID, m_tInfo, m_tFrame);
			CObj::Update_Rect();
		}

		break;
	}
	case OBJ_STATUS::OBJ_STATUS_DIE:
	{
		m_pFrameKey = L"Player_Die";
		m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
		m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_DIE;
		m_tInfo.fCX = PLAYER_DIE_FCX;
		m_tInfo.fCY = PLAYER_DIE_FCY;
		CObj::Update_Rect();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			// 이떄 서버에게 삭제해달라는 메시지 보내기
			m_bDead = true;
		}
		break;
	}
	}
}

void CPlayer::Key_Input()
{
	switch (m_eObjCurStatus)
	{
	case OBJ_STATUS::OBJ_STATUS_TRAP:
	{
		if (CKeyMgr::Get_Instance()->Key_Press('W'))
		{
			m_tInfo.vLook = { 0.f, -1.f, 0.f };
			D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
			m_vPrePos = m_tInfo.vPos;
			m_tInfo.vPos += m_tInfo.vDir * 0.5;
		}
		else if (CKeyMgr::Get_Instance()->Key_Press('S'))
		{
			m_tInfo.vLook = { 0.f, 1.f, 0.f };
			D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld); // 아무것도 안하면 걍 항등행렬
			m_vPrePos = m_tInfo.vPos;
			m_tInfo.vPos += m_tInfo.vDir * 0.5;
		}
		else if (CKeyMgr::Get_Instance()->Key_Press('A'))
		{
			m_tInfo.vLook = { -1.f, 0.f, 0.f };
			D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
			m_vPrePos = m_tInfo.vPos;
			m_tInfo.vPos += m_tInfo.vDir * 0.5;
		}
		else if (CKeyMgr::Get_Instance()->Key_Press('D'))
		{
			m_tInfo.vLook = { 1.f, 0.f, 0.f };
			D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
			m_vPrePos = m_tInfo.vPos;
			m_tInfo.vPos += m_tInfo.vDir * 0.5;
		}

		break;
	}
	default:
	{
		if (CKeyMgr::Get_Instance()->Key_Press('W'))
		{
			m_tInfo.vLook = { 0.f, -1.0f, 0.f };
			D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
			m_eObjCurStatus = OBJ_STATUS_WALK_UP;
			m_vPrePos = m_tInfo.vPos;
			m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;


		}
		else if (CKeyMgr::Get_Instance()->Key_Press('S'))
		{
			m_tInfo.vLook = { 0.f, 1.0f, 0.f };
			D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
			m_eObjCurStatus = OBJ_STATUS_WALK_DOWN;
			m_vPrePos = m_tInfo.vPos;
			m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		}

		else if (CKeyMgr::Get_Instance()->Key_Press('A'))
		{
			m_tInfo.vLook = { -1.f, 0.f, 0.f };
			D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
			m_eObjCurStatus = OBJ_STATUS_WALK_LEFT;

			m_vPrePos = m_tInfo.vPos;
			m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		}

		else if (CKeyMgr::Get_Instance()->Key_Press('D'))
		{
			m_tInfo.vLook = { 1.f, 0.f, 0.f };
			D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
			m_eObjCurStatus = OBJ_STATUS_WALK_RIGHT;

			m_vPrePos = m_tInfo.vPos;
			m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		}
		else if (CKeyMgr::Get_Instance()->Key_Up('W'))
		{
			m_eObjCurStatus = OBJ_STATUS_WAIT;
		}
		else if (CKeyMgr::Get_Instance()->Key_Up('S'))
		{
			m_eObjCurStatus = OBJ_STATUS_WAIT;
			
		}
		else if (CKeyMgr::Get_Instance()->Key_Up('A'))
		{
			m_eObjCurStatus = OBJ_STATUS_WAIT;
		}
		else if (CKeyMgr::Get_Instance()->Key_Up('D'))
		{
			m_eObjCurStatus = OBJ_STATUS_WAIT;
		}

		if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		{
			int iSpawnX = (TILE_FCX >> 1) + TILE_FCX * ((int)m_tInfo.vPos.x / 52) + TILE_OFFSET_FCX;
			int iSpawnY = (TILE_FCY >> 1) + TILE_FCY * ((int)m_tInfo.vPos.y / 52) + TILE_OFFSET_FCY;


			CObjMgr::Get_Instance()->Add_Object(
				OBJ_ID_WATER_BOMB,
				CAbstractFactory<CWaterBomb>::Create(
					D3DXVECTOR3{ (float)iSpawnX, (float)iSpawnY, 0.f },
					D3DXVECTOR3{ 0.f, 0.f, 0.f },
					WATER_BOMB_IDLE_FCX,
					WATER_BOMB_IDLE_FCY
				)
			);
			CSocketMgr::Get_Instance()->Send_Create_Water_Bomb_Message(m_iClientID, iSpawnX, iSpawnY);
		}
		break;
	}
	}


}
