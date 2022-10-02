#pragma once
#include"JBaseCharacter.h"
#include"JSpriteManager.h"

enum SPRITE {
	IDLE_DOWN,
	IDLE_RIGHT,
	IDLE_LEFT,
	IDLE_UP,
	IDLE_RIGHT_UP,
	IDLE_LEFT_UP,
	IDLE_WITH_WEAPON_DOWN_RIGHT,
	IDLE_WITH_WEAPON_DOWN_LEFT,
	IDLE_WITH_WEAPON_RIGHT,
	IDLE_WITH_WEAPON_LEFT,
	IDLE_WITH_WEAPON_UP_RIGHT,
	IDLE_WITH_WEAPON_UP_LEFT,
	IDLE_WITH_WEAPON_RIGHT_UP,
	IDLE_WITH_WEAPON_LEFT_UP,
};

class JUser : public JBaseCharacter
{
public:
	bool init() override;
	bool frame() override;
public:
	void setCurSprite(float angle);
};

