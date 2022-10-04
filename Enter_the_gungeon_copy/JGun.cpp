#include "JGun.h"

bool JGun::init()
{
	JBaseObject::init();
	m_rtArea.Set({ 0, 0 }, { 30, 30 });
	m_curSprite = GUN_RIGHT_IDLE;
	return true;
}

bool JGun::frame()
{
	m_fStep = m_vSpriteInfo->at(m_curSprite).m_fTotalTime / m_vSpriteInfo->at(m_curSprite).m_iNumFrame;
	return true;
}

void JGun::rotate(nCube<2> rtNDC)
{
	JVector<3> vCenter;
	if(m_curSprite %2 == 0) vCenter[0] = rtNDC.vCenter()[0] - rtNDC.m_vSize[0] / 2;
	else					vCenter[0] = rtNDC.vCenter()[0] + rtNDC.m_vSize[0] / 2;
	vCenter[1] = rtNDC.vCenter()[1] - rtNDC.m_vSize[1] / 2;

	float fRadian = DegreeToRadian(m_fRotateAngle);
	JVector<3> vRot;
	for (int vertex = 0; vertex < 4; vertex++)
	{
		JVector<3> vCenterMove = m_VertexList[vertex].p - vCenter;
		vRot[0] = vCenterMove[0] * cos(fRadian) - vCenterMove[1] * sin(fRadian);
		vRot[1] = vCenterMove[0] * sin(fRadian) + vCenterMove[1] * cos(fRadian);
		m_VertexList[vertex].p = vRot + vCenter;
	}
}

bool JGun::shot(JVector<2> curDirection)
{
	auto bullet = I_ObjectPool.GetRecycledObject<Bullet>();
	
	JVector<2> shootLocation;
	if (m_curSprite % 2 == 0) shootLocation = { m_rtArea.vMax()[0], m_rtArea.m_vLeftTop[1] };
	else					  shootLocation = { m_rtArea.m_vLeftTop[0], m_rtArea.m_vLeftTop[1] };
	
	bullet->shoot(shootLocation, curDirection * m_fSpeed, m_fRange, m_bIsUser);

	return true;
}
