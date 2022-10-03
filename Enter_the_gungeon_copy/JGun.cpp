#include "JGun.h"

bool JGun::init()
{
	JBaseObject::init();
	m_rtArea.Set({ 0, 0 }, { 10, 10 });
	m_curSprite = GUN_RIGHT_IDLE;
	return true;
}
