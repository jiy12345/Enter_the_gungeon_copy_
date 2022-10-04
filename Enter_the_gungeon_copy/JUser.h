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

class JUser : public JBaseCharacter
{
public:
	bool  m_bIsRoll;
	float m_fRollTime;
public:
	bool init() override;
	bool frame() override;
	bool render() override;
public:
	void setIdleSprite();
	void setWalkSprite();
	void setRollSprite();
};

