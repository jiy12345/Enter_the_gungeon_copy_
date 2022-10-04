#pragma once
#include "stdafx.h"
#include "JBaseObject.h"
#include "Bullet.h"
#include "ObjectPool.h"

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
public:
	float m_fRange;
	bool m_bIsUser;
	int m_iDamage;
	int m_iMaxNumShots;
	int m_iCurNumShots;
public:
	bool init() override;
	bool frame() override;
	void rotate(nCube<2> rtNDC) override;
public:
	bool shot(JVector<2> curDirection);
};

