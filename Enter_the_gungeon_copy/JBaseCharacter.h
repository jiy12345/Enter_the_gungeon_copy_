#pragma once
#include "stdafx.h"
#include "JBaseObject.h"
#include "JGun.h"

class JBaseCharacter: public JBaseObject
{
	int m_iHp;
	JGun m_gun;
};

