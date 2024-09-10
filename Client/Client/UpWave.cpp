#include "pch.h"
#include "UpWave.h"
#include "BmpMgr.h"

CUpWave::CUpWave()
{
}

CUpWave::~CUpWave()
{
    Release();
}

void CUpWave::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/wave/up1.bmp", L"UP_WAVE_END_POINT");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/wave/up2.bmp", L"UP_WAVE_MIDDLE_POINT");
    
    m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_BOMB;
    m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
    switch (m_eWaveType)
    {
    case WAVE_TYPE::MIDDLE_POINT_TYPE:
    {
        m_pFrameKey = L"UP_WAVE_MIDDLE_POINT";
        break;
    }
    case WAVE_TYPE::END_POINT_TYPE:
    {
        m_pFrameKey = L"UP_WAVE_END_POINT";
        break;
    }
    }
}

int CUpWave::Update()
{
    if (m_bDead)
    {
        return OBJ_DEAD;
    }
    CObj::Update_Rect();
    return OBJ_NO_EVENT;
}

void CUpWave::Late_Update()
{
    CUpWave::Motion_Change();
    CUpWave::Manage_Status();
    CUpWave::Move_Frame();
}

void CUpWave::Render(HDC _hDC)
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
}

void CUpWave::Release()
{
}

void CUpWave::Manage_Status()
{
    switch (m_eObjCurStatus)
    {
    case OBJ_STATUS::OBJ_STATUS_BOMB:
    {
        switch (m_eWaveType)
        {
        case WAVE_TYPE::END_POINT_TYPE:
        {
            m_pFrameKey = L"UP_WAVE_END_POINT";
            m_tInfo.fCX = WATER_SIDE_POP_FCX;
            m_tInfo.fCY = WATER_SIDE_POP_FCY;
            m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_BOMB;
            m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
            CObj::Update_Rect();
            
            if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
            {
                m_bDead = true;
            }

            break;
        }
        case WAVE_TYPE::MIDDLE_POINT_TYPE:
        {
            m_pFrameKey = L"UP_WAVE_MIDDLE_POINT";
            m_tInfo.fCX = WATER_SIDE_POP_FCX;
            m_tInfo.fCY = WATER_SIDE_POP_FCY;
            m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_BOMB;
            m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
            CObj::Update_Rect();

            if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
            {
                m_bDead = true;
            }
            break;
        }
        }
        break;
    }
    }
}

void CUpWave::Motion_Change()
{
    if (m_eObjPreStatus != m_eObjCurStatus)
    {
        switch (m_eObjCurStatus)
        {
        case OBJ_STATUS::OBJ_STATUS_BOMB:
        {
            m_tFrame.iFrameStart = 0;
            m_tFrame.iFrameEnd = 10;
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


