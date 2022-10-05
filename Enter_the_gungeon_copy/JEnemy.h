#pragma once
#include "JBaseCharacter.h"
#include "gr_black_revolver.h"

#define MAX_ATTACK_TERM 3;
#define MIN_ATTACK_TERM 2;

enum SPRITE_ENEMY {
	IDLE_DOWN_ENEMY,
	IDLE_UP_ENEMY,
	WALKING_DOWN_ENEMY,
	WALKING_UP_ENEMY,
};

class JEnemy : public JBaseCharacter
{
	bool m_bIsMoving = false;
	float m_fCurLeftTime;
	int m_iCurLeftShots;
	float m_fAttackTime = 3;
public:
	bool init() override;
	bool frame() override;
	void setIdleSprite();
	void setWalkSprite();
};

