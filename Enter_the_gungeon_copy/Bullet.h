#pragma once
#include "stdafx.h"
#include "JBaseObject.h"
#include "IObejctPoolable.h"

class Bullet : public IObejctPoolable, JBaseObject
{
public :
	JVector<2> m_vVelocity;
	JVector<2> m_vFireLocation;
	float	   m_fRange;
	bool	   m_bIsUser;
public :
	bool init() override;
	bool update() override;
	bool frame() override;
	bool render_objectPool() override;
public:
	Bullet();
public:
	void shoot(JVector<2> vLocation, JVector<2> vVelocity, float fRange, bool isUser);

};

