#pragma once
#include <windows.h>
#include <string>
#include "JSingleton.h"
#include "JWindow.h"

enum KeyState
{
	KEY_FREE = 0,
	KEY_UP,
	KEY_PUSH,
	KEY_HOLD,
};
class JInput : public JSingleton<JInput>
{
	friend class JSingleton<JInput>;
private:
	DWORD		m_dwKeyState[256];
public:
	POINT		m_ptPos;
public:
	virtual bool		init();
	virtual bool		frame();
	virtual bool		render();
	virtual bool		release();
public:
	DWORD  GetKey(DWORD dwKey);
private:
	JInput() {};
	~JInput() = default;
	JInput(const JInput&) = delete;
	JInput& operator=(const JInput&) = delete;
};
#define I_Input JInput::GetInstance()
