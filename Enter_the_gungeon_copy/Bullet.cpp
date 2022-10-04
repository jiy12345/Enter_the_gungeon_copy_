#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	JBaseObject::init();
	init();
}

bool Bullet::init() {
	m_wstrTextureName = L"../data/sprites/bullet.png";
	if (m_bIsUser) m_rtUV.Set({ 365, 293 }, { 46, 47 });
	else		  m_rtUV.Set({ 18, 294 }, { 46, 46 });

	m_rtArea.Set({ 0, 0 }, { 10, 10 });

	return true;
}

bool Bullet::update()
{
	return frame();
}

bool Bullet::frame() {
	m_rtArea.m_vLeftTop += m_vVelocity.normalize() * 1000 * I_Timer.m_fElapseTimer;

	JVector<2> vDistance = m_vFireLocation - m_rtArea.vCenter();
	if (vDistance.length() > m_fRange)
		setRecycle();

	JBaseObject::render();

	return true;
}

bool Bullet::render_objectPool()
{
	if(CanRecylcable == false) render();
	return true;
}

void Bullet::shoot(JVector<2> vLocation, JVector<2> vVelocity, float fRange, bool isUser)
{
	m_rtArea.m_vLeftTop = m_vFireLocation = vLocation;
	m_vVelocity = vVelocity;
	m_fRange = fRange;
}
