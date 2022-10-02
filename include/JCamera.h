#pragma once
#include "stdafx.h"

class JCamera: public JSingleton<JCamera>
{
	friend class JSingleton<JCamera>;
public:
	nCube<2> m_rtCamera;
	void getCameraCoord(nCube<2>& rtArea);
private:
	JCamera() {};
	~JCamera() = default;
	JCamera(const JCamera&) = delete;
	JCamera& operator=(const JCamera&) = delete;
};
#define I_Camera JCamera::GetInstance()