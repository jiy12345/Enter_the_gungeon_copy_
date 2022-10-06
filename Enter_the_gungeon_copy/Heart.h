#pragma once
#include "stdafx.h"
#include "JBaseObject.h"

enum SPRITE_HEART {
	EMPTY,
	HALF,
	FULL,
};

class Heart : public JBaseObject
{
public:
	bool init() override;
	void setHeart(SPRITE_HEART iSpriteHeart);
	Heart();
};

