#pragma once
#include "stdafx.h"
#include "JGameEngine.h"
#include "ObjectManager.h"
#include "bullet_kin.h"
#include "SpacePartition.h"
#include "Heart.h"
#include "Tile.h"

class EnterTheGungeon : public JGameEngine
{
	JUser* m_pUser;
	Tile* m_pMapObject;
	JSoundChannel* m_pBGM;
	std::vector<JSoundChannel*> m_vGunShots;
	std::vector<Heart> m_vHeart;
public:
	virtual bool init() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
public:
	bool		 checkCollision();
};