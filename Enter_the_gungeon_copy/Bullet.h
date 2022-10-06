#pragma once
#include "stdafx.h"
#include "JBaseObject.h"
#include "IObejctPoolable.h"

class Bullet : public JBaseObject
{
public :
	JVector<2> m_vVelocity;
	JVector<2> m_vFireLocation;
	float	   m_fRange;
public :
	bool init() override;
	bool frame() override;
public:
	Bullet();
public:
	void shoot(JVector<2> vLocation, JVector<2> vVelocity, float fRange);

};

