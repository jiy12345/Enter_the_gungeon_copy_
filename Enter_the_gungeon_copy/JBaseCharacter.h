#pragma once
#include "stdafx.h"
#include "JBaseObject.h"
#include "JGun.h"

class JBaseCharacter: public JBaseObject
{
public:
	float		m_fAngle;
	int			m_iDirection;
	JVector<2>	m_vDirection;
public:
	int		m_iHp;
	JGun*	m_pGun;
public:
	bool	render() override;
};

