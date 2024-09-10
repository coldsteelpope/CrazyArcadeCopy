#include "pch.h"
#include "DownWave.h"
#include "BmpMgr.h"

CDownWave::CDownWave()
{
}

CDownWave::~CDownWave()
{
    Release();
}

void CDownWave::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/wave/down1.bmp", L"DOWN_WAVE_END_POINT");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/wave/down2.bmp", L"DOWN_WAVE_MIDDLE_POINT");
    
    m_eObjCurStatus = OBJ_STATUS::OBJ_STATUS_BOMB;
    m_eObjDir = OBJ_DIR::OBJ_DIR_BOTTOM;
    switch (m_eWaveType)
    {
    case WAVE_TYPE::MIDDLE_POINT_TYPE:
    {
        m_pFrameKey = L"DOWN_WAVE_MIDDLE_POINT";
        break;
    }
    case WAVE_TYPE::END_POINT_TYPE:
    {
        m_pFrameKey = L"DOWN_WAVE_END_POINT";
        break;
    }
    }
}

int CDownWave::Update()
{
    if (m_bDead)
    {
        return OBJ_DEAD;
    }
    CObj::Update_Rect();
    return OBJ_NO_EVENT;
}

void CDownWave::Late_Update()
{
    CDownWave::Motion_Change();
    CDownWave::Manage_Status();
    CDownWave::Move_Frame();
}

void CDownWave::Render(HDC _hDC)
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

void CDownWave::Release()
{
}

void CDownWave::Manage_Status()
{
    switch (m_eObjCurStatus)
    {
    case OBJ_STATUS::OBJ_STATUS_BOMB:
    {
        switch (m_eWaveType)
        {
        case WAVE_TYPE::END_POINT_TYPE:
        {
            m_pFrameKey = L"DOWN_WAVE_END_POINT";
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
            m_pFrameKey = L"DOWN_WAVE_MIDDLE_POINT";
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

void CDownWave::Motion_Change()
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
