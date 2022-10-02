#include "JWindow.h"
LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	return I_Window.msgProc(hWnd, message, wParam, lParam);
}

bool JWindow::setWindow(HINSTANCE hInst, const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{
	m_hInstance = hInst;
	WORD ret = registerWNDClass();

	return (!initInstance(szTitle, iWidth, iHeight)) ? false : true;
}

ATOM JWindow::registerWNDClass()
{
	WNDCLASSEXW wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance = m_hInstance;
	wcex.hbrBackground = CreateSolidBrush(RGB(7, 77, 7));
	wcex.lpszClassName = L"â";
	wcex.lpfnWndProc = WndProc;
	wcex.hCursor = LoadCursor(nullptr, IDC_UPARROW);
	return RegisterClassEx(&wcex);
}

BOOL JWindow::initInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{
	m_csStyle = WS_OVERLAPPEDWINDOW;

	RECT rc = { 0,0,iWidth , iHeight };
	AdjustWindowRect(&rc, m_csStyle, FALSE);

	m_hWnd = CreateWindowW(
		L"â",
		szTitle,
		m_csStyle,
		0, 0,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr, nullptr,
		m_hInstance, nullptr);

	if (!m_hWnd) return FALSE;
	ShowWindow(m_hWnd, SW_SHOW);

	GetWindowRect(m_hWnd, &m_rtWindow);
	GetClientRect(m_hWnd, &m_rtClient);

	return TRUE;
}

bool JWindow::run()
{
	MSG msg = { 0, };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			return true;
		}
	}
	return false;
}

void JWindow::centerWindow()
{
	UINT iScreenWidht = GetSystemMetrics(SM_CXFULLSCREEN);
	UINT iScreenHieght = GetSystemMetrics(SM_CYFULLSCREEN);
	UINT cx, cy;
	cx = (iScreenWidht - (m_rtWindow.right - m_rtWindow.left)) * 0.5f;
	cy = (iScreenHieght - (m_rtWindow.bottom - m_rtWindow.top)) * 0.5f;
	MoveWindow(m_hWnd, cx, cy,
		m_rtWindow.right - m_rtWindow.left,
		m_rtWindow.bottom - m_rtWindow.top,
		true);
}

bool JWindow::init()
{
	return true;
}

bool JWindow::frame()
{
	return true;
}

bool JWindow::render()
{
	return true;
}

bool JWindow::release()
{
	return true;
}

LRESULT JWindow::msgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return  DefWindowProc(hWnd, message, wParam, lParam);
}