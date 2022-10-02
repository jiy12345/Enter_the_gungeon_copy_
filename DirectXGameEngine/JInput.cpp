#include "JInput.h"
bool		JInput::init()
{
    ZeroMemory(m_dwKeyState, sizeof(DWORD) * 256);
    return true;
}
DWORD  JInput::GetKey(DWORD dwKey)
{
    return m_dwKeyState[dwKey];
}
bool		JInput::frame()
{
    ::GetCursorPos(&m_ptPos);
    ::ScreenToClient(I_Window.m_hWnd, &m_ptPos);

    for (int iKey = 0; iKey < 256; iKey++)
    {
        SHORT sKey = ::GetAsyncKeyState(iKey);
        if (sKey & 0x8000)
        {
            if (m_dwKeyState[iKey] == KEY_FREE ||
                m_dwKeyState[iKey] == KEY_UP)
                m_dwKeyState[iKey] = KEY_PUSH;
            else
                m_dwKeyState[iKey] = KEY_HOLD;
        }
        else
        {
            if (m_dwKeyState[iKey] == KEY_PUSH ||
                m_dwKeyState[iKey] == KEY_HOLD)
                m_dwKeyState[iKey] = KEY_UP;
            else
                m_dwKeyState[iKey] = KEY_FREE;
        }
    }

    return true;
}
bool		JInput::render()
{
    std::wstring curPos =   L"x: ";
    curPos              +=  std::to_wstring(m_ptPos.x);
    curPos              +=  L", y: ";
    curPos              +=  std::to_wstring(m_ptPos.y);
    curPos              +=  L'\n';
    OutputDebugString(curPos.c_str());
    return true;
}
bool		JInput::release()
{
    return true;
}