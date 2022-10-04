#pragma once
#include "stdafx.h"
#include "JEnemy.h"
#include "gr_black_revolver.h"

enum SPRITE_ENEMY {
	IDLE_DOWN_ENEMY,
	IDLE_UP_ENEMY,
	WALKING_DOWN_ENEMY,
	WALKING_UP_ENEMY,
};


class bullet_kin : public JEnemy
{
	bool init();
};

