#pragma once
#include "JSingleton.h"
#include <string>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
class JTimer : public JSingleton<JTimer>
{
	friend class JSingleton<JTimer>;
public:
	float			m_fGameTimer = 0.0f;
	float			m_fElapseTimer = 10.0f;
	UINT			m_iFPS = 0;
	std::wstring	m_szTimer;
private:
	DWORD m_dwBeforeTime;
	UINT  m_iFPSCounter = 0;
	float m_fFPSTimer = 0.0f;
public:
	virtual bool init();
	virtual bool frame();
	virtual bool render();
	virtual bool release();
private:
	JTimer() {};
	~JTimer() = default;
	JTimer(const JTimer&) = delete;
	JTimer& operator=(const JTimer&) = delete;
};

#define I_Timer JTimer::GetInstance()


