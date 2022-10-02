#pragma once
#include "JSingleton.h"
#include <windows.h>

class JWindow : public JSingleton<JWindow>
{
	friend class JSingleton<JWindow>;
public:
	HINSTANCE			m_hInstance;
	HWND				m_hWnd;
	RECT				m_rtWindow;
	RECT				m_rtClient;
	DWORD				m_csStyle;
public:
	bool				setWindow(HINSTANCE hInst, const WCHAR* szTitle, UINT iWidth = 1024, UINT iHeight = 768);
	ATOM				registerWNDClass();
	BOOL				initInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight);
	bool				run();
	void				centerWindow();
public:
	virtual bool		init();
	virtual bool		frame();
	virtual bool		render();
	virtual bool		release();
	virtual LRESULT		msgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	JWindow() {};
	~JWindow() = default;
	JWindow(const JWindow&) = delete;
	JWindow& operator=(const JWindow&) = delete;
};
#define I_Window JWindow::GetInstance()

