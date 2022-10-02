#pragma once
#include "stdafx.h"
#include "JGameEngine.h"
#include "JUser.h"

class Test : public JGameEngine
{
	JUser* m_pUser;
	JBaseObject* m_pMapObject;
	JSoundChannel* m_pBGM;
	std::vector<JSoundChannel*> m_pGunShots;

public:
	virtual bool init() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};


