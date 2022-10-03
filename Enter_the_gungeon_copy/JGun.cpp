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
