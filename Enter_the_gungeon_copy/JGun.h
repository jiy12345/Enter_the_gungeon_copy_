#pragma once
#include "JBaseObject.h"

enum GUN_SPRITE {
	GUN_RIGHT_IDLE,
	GUN_LEFT_IDLE,
	GUN_RIGHT_SHOOT,
	GUN_LEFT_SHOOT,
	GUN_RIGHT_RELOAD,
	GUN_LEFT_RELOAD,
};

class JGun : public JBaseObject
{
	int m_iDamage;
	int m_iMaxNumShots;
	int m_iCurNumShots;
public:
	bool init() override;
};

