#pragma once
#include "stdafx.h"
#include "JGameEngine.h"
#include "ObjectPool.h"
#include "JUser.h"
#include "bullet_kin.h"

class EnterTheGungeon : public JGameEngine
{
	JUser* m_pUser;
	JBaseObject* m_pMapObject;
	JSoundChannel* m_pBGM;
	std::vector<JSoundChannel*> m_vGunShots;
	std::vector<JEnemy*> m_vEnemy;
public:
	virtual bool init() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};


