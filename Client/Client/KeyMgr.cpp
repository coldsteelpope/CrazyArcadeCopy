#include "pch.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr()
{
    ZeroMemory(m_bKeyStates, sizeof(m_bKeyStates));
}

CKeyMgr::~CKeyMgr()
{
}

bool CKeyMgr::Key_Press(int _iKey)
{
    if (GetAsyncKeyState(_iKey) & 0x8000)
    {
        return true;
    }
    return false;
}

bool CKeyMgr::Key_Up(int _iKey)
{
    if (m_bKeyStates[_iKey] == true && !(GetAsyncKeyState(_iKey) & 0x8000))
    {
        return true;
    }
    return false;
}

bool CKeyMgr::Key_Down(int _iKey)
{
    if (m_bKeyStates[_iKey] == false && (GetAsyncKeyState(_iKey) & 0x8000))
    {
        m_bKeyStates[_iKey] = !m_bKeyStates[_iKey];
        return true;
    }
    return false;
}

void CKeyMgr::Key_Late_Update()
{
    for (int _iKey = 0; _iKey < VK_MAX; ++_iKey)
    {
        if (m_bKeyStates[_iKey] == false && (GetAsyncKeyState(_iKey) & 0x8000))
        {
            m_bKeyStates[_iKey] = !m_bKeyStates[_iKey];
        }

        if (m_bKeyStates[_iKey] == true && !(GetAsyncKeyState(_iKey) & 0x8000))
        {
            m_bKeyStates[_iKey] = !m_bKeyStates[_iKey];
        }
    }
}
