#include "JCamera.h"

void JCamera::getCameraCoord(nCube<2>& rtArea)
{
	rtArea.m_vLeftTop -= m_rtCamera.m_vLeftTop;
}
