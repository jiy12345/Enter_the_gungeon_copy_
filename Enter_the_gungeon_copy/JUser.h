#pragma once
#include"JBaseObject.h"
#include"JSpriteManager.h"

enum SPRITE {
	IDLE_DOWN,
	IDLE_RIGHT,
	IDLE_LEFT,
	IDLE_UP,
	IDLE_RIGHT_UP,
	IDLE_LEFT_UP,
};

class JUser : public JBaseObject
{
public:
	bool init() override;
	bool frame() override;
public:
	void setCurSprite(float angle);
};

