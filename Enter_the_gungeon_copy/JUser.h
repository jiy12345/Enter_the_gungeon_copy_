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
	WALKING_DOWN,
	WALKING_RIGHT,
	WALKING_LEFT,
	WALKING_UP,
	WALKING_RIGHT_UP,
	WALKING_LEFT_UP,
	ROLLING_DOWN,
	ROLLING_RIGHT,
	ROLLING_LEFT,
	ROLLING_UP,
	ROLLING_RIGHT_UP,
	ROLLING_LEFT_UP,
};

enum MOVE_DIRECTION {
	NO_DIRECTION = 0b0000,
	UP = 0b0001,
	DOWN = 0b0010,
	LEFT = 0b0100,
	RIGHT = 0b1000,
	DOWN_RIGHT = DOWN | RIGHT,
	DOWN_LEFT = DOWN | LEFT,
	RIGHT_UP = RIGHT | UP,
	LEFT_UP = LEFT | UP,
};

class JUser : public JBaseCharacter
{
public:
	bool  m_bIsRoll;
	float m_fRollTime;
public:
	bool init() override;
	bool frame() override;
public:
	void setIdleSprite();
	void setWalkSprite();
	void setRollSprite();
};

