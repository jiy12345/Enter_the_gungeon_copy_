#pragma once
#include "stdafx.h"
#include "JBaseObject.h"
#include "JGun.h"

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

class JBaseCharacter: public JBaseObject
{
public:
	float		m_fAngle;
	int			m_iDirection;
	JVector<2>	m_vDirection;
public:
	float	m_fHp;
	float	m_fMaxHp;
	JGun*	m_pGun;
public:
	bool	init() override;
	bool	frame() override;
	bool	render() override;
	void	gunFrame();
public:
	virtual bool	checkCollision() = 0;
};

