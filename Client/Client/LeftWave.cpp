#include "pch.h"
#include "LeftWave.h"
#include "BmpMgr.h"

CLeftWave::CLeftWave()
{
}

CLeftWave::~CLeftWave()
{
    Release();
}

void CLeftWave::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/wave/left1.bmp", L"LEFT_WAVE_END_POINT");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/wave/left2.bmp", L"LEFT_WAVE_MIDDLE_POINT");

    m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_BOMB;
    m_eObjDir = OBJ_DIR::OBJ_DIR_LEFT;
    switch (m_eWaveType)
    {
    case WAVE_TYPE::MIDDLE_POINT_TYPE:
    {
        m_pFrameKey = L"LEFT_WAVE_MIDDLE_POINT";
        break;
    }
    case WAVE_TYPE::END_POINT_TYPE:
    {
        m_pFrameKey = L"LEFT_WAVE_END_POINT";
        break;
    }
    }
}

int CLeftWave::Update()
{
    if (m_bDead)
    {
        return OBJ_DEAD;
    }
    CObj::Update_Rect();
    return OBJ_NO_EVENT;
}

void CLeftWave::Late_Update()
{
    CLeftWave::Motion_Change();
    CLeftWave::Manage_Status();
    CLeftWave::Move_Frame();
}

void CLeftWave::Render(HDC _hDC)
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

void CLeftWave::Release()
{
}

void CLeftWave::Manage_Status()
{
    switch (m_eObjCurStatus)
    {
    case OBJ_STATUS::OBJ_STATUS_BOMB:
    {
        switch (m_eWaveType)
        {
        case WAVE_TYPE::END_POINT_TYPE:
        {
            m_pFrameKey = L"LEFT_WAVE_END_POINT";
            m_tInfo.fCX = WATER_SIDE_POP_FCX;
            m_tInfo.fCY = WATER_SIDE_POP_FCY;
            m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_BOMB;
            m_eObjDir = OBJ_DIR::OBJ_DIR_LEFT;
            CObj::Update_Rect();

            if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
            {
                m_bDead = true;
            }

            break;
        }
        case WAVE_TYPE::MIDDLE_POINT_TYPE:
        {
            m_pFrameKey = L"LEFT_WAVE_MIDDLE_POINT";
            m_tInfo.fCX = WATER_SIDE_POP_FCX;
            m_tInfo.fCY = WATER_SIDE_POP_FCY;
            m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_BOMB;
            m_eObjDir = OBJ_DIR::OBJ_DIR_LEFT;
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

void CLeftWave::Motion_Change()
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
