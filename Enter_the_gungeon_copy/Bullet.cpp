#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	JBaseObject::init();
	init();
}

bool Bullet::init() {
	m_wstrTextureName = L"../data/sprites/bullet.png";

	m_rtArea.Set({ 0, 0 }, { 10, 10 });

	return true;
}

bool Bullet::update()
{
	return frame();
}

bool Bullet::frame() {
	m_rtArea.m_vLeftTop += m_vVelocity * I_Timer.m_fElapseTimer;

	JVector<2> vDistance = m_vFireLocation - m_rtArea.vCenter();
	if (vDistance.length() > m_fRange)
		setRecycle();

	JBaseObject::render();

	return true;
}

bool Bullet::render_objectPool()
{
	if (m_bIsUser) m_rtUV.Set({ 365 / 667.0f, 293 / 374.0f }, { 46 / 667.0f, 47 / 374.0f });
	else		   m_rtUV.Set({ 18 / 667.0f, 294 / 374.0f }, { 46 / 667.0f, 46 / 374.0f });
	if(CanRecylcable == false) render();
	return true;
}

void Bullet::shoot(JVector<2> vLocation, JVector<2> vVelocity, float fRange, bool isUser)
{
	m_rtArea.m_vLeftTop = m_vFireLocation = vLocation;
	m_vVelocity = vVelocity;
	m_fRange = fRange;
	m_bIsUser = isUser;
}
