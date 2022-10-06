#include "bullet_kin.h"

bool bullet_kin::init() {
	JEnemy::init();
	m_rtArea.Set({ 0, 0 }, { 20, 40 });
	m_wstrTextureName = L"../data/sprites/bullet kin.png";
	I_Sprite.load(m_vSpriteInfo, L"../data/sprites/bullet kin.txt");
	m_fSpeed = 100.0f;

	m_fHp = 3.0f;
	m_fMaxHp = 3.0f;

	m_pGun = new gr_black_revolver;
	m_pGun->init();

	m_curSprite = IDLE_DOWN_ENEMY;

	return true;
}
