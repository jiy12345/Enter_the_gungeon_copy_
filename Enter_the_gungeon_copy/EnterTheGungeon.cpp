#define _CRT_SECURE_NO_WARNINGS
#include "EnterTheGungeon.h"

#define WINDOW_NAME L"DirectXGameEngine"



int APIENTRY wWinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPWSTR		lpCmdLine,
	int			nCmdShow) {

	srand(time(NULL));

#ifdef _DEBUG
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
#endif
	I_Window.setWindow(hInstance, WINDOW_NAME, WINDOW_SIZE_X, WINDOW_SIZE_Y);
	EnterTheGungeon test;
	test.run();
#ifdef _DEBUG
	FreeConsole();
#endif
	return 0;
}

bool EnterTheGungeon::init()
{
	I_SP2D.Init();
	I_SP2D.Buildtree(1, 0);

	m_pUser = new JUser;
	m_pUser->init();
	m_pMapObject = new Tile();

	for (int i = MIN_ENEMY_SERIAL_NUM; i < MIN_ENEMY_SERIAL_NUM + 10;i++) {
		auto curEnemy = I_ObjectManager.GetRecycledEnemy<bullet_kin>();
		curEnemy->init();
		curEnemy->m_rtArea.m_vLeftTop[0] = rand() % MAP_SIZE_X - MAP_SIZE_X / 2;
		curEnemy->m_rtArea.m_vLeftTop[1] = rand() % MAP_SIZE_Y - MAP_SIZE_Y / 2;
	}

	m_vGunShots.resize(32);
	for (JSoundChannel*& curGunshot : m_vGunShots) {
		
		curGunshot = new JSoundChannel(L"../data/sound/Gun1.wav");
	}
	m_pBGM = new JSoundChannel(L"../data/sound/TowerDefenseMusic01_Loop_Stereo.WAV");

	m_vHeart.resize(m_pUser->m_fMaxHp);

	I_Sound.play(m_pBGM, true);

	return true;
}

bool EnterTheGungeon::frame()
{
	if (I_Input.GetKey(VK_LBUTTON) == KEY_PUSH)
	{

		I_Sound.playEffect(m_vGunShots[0]);
	}

	m_pUser->frame();

	for (int i = MIN_ENEMY_SERIAL_NUM; i < MIN_ENEMY_SERIAL_NUM + I_ObjectManager.getNumOfEnemy(); i++) {
		if (I_ObjectManager.getEnemy(i))
			I_ObjectManager.getEnemy(i)->frame();
	}

	for (int i = MIN_USER_BULLET_SERIAL_NUM; i < MIN_USER_BULLET_SERIAL_NUM + I_ObjectManager.getNumOfUserBullet(); i++) {
		if(I_ObjectManager.getUserBullet(i)) 
			I_ObjectManager.getUserBullet(i)->frame();
	}

	for (int i = MIN_ENEMY_BULLET_SERIAL_NUM; i < MIN_ENEMY_BULLET_SERIAL_NUM + I_ObjectManager.getNumOfEnemyBullet(); i++) {
		if (I_ObjectManager.getEnemyBullet(i)) 
			I_ObjectManager.getEnemyBullet(i)->frame();
	}

	checkCollision();

	I_Camera.m_rtCamera.m_vLeftTop = m_pUser->m_rtArea.vCenter() - (JVector<2>{ I_Window.m_rtClient.right, I_Window.m_rtClient.bottom } / 2);
	return true;
}

bool EnterTheGungeon::render()
{
	JVector<2> vMapStartLoc{ -2500, -2500 };

	for (int i = 0; i < 25;i++) {
		for (int j = 0; j < 25; j++) {
			m_pMapObject->m_rtArea.m_vLeftTop[0] = vMapStartLoc[0] + i * m_pMapObject->m_rtArea.m_vSize[0];
			m_pMapObject->m_rtArea.m_vLeftTop[1] = vMapStartLoc[1] + j * m_pMapObject->m_rtArea.m_vSize[1];
			m_pMapObject->render();
		}
	}

	m_pUser->render();

	for (int i = MIN_ENEMY_SERIAL_NUM; i < MIN_ENEMY_SERIAL_NUM + I_ObjectManager.getNumOfEnemy(); i++) {
		if (I_ObjectManager.getEnemy(i))
			I_ObjectManager.getEnemy(i)->render();
	}

	for (int i = MIN_USER_BULLET_SERIAL_NUM; i < MIN_USER_BULLET_SERIAL_NUM + I_ObjectManager.getNumOfUserBullet(); i++) {
		if (I_ObjectManager.getUserBullet(i))
			I_ObjectManager.getUserBullet(i)->render();
	}
	for (int i = MIN_ENEMY_BULLET_SERIAL_NUM; i < MIN_ENEMY_BULLET_SERIAL_NUM + I_ObjectManager.getNumOfEnemyBullet(); i++) {
		if (I_ObjectManager.getEnemyBullet(i))
			I_ObjectManager.getEnemyBullet(i)->render();
	}

	JVector<2> vHPLocation = I_Camera.m_rtCamera.m_vLeftTop;
	vHPLocation[0] += 10;
	vHPLocation[1] += 10;
	
	for (int i = 0; i < m_pUser->m_fMaxHp; i++) {
		if (i < m_pUser->m_fHp) m_vHeart[i].setHeart(FULL);
		else					m_vHeart[i].setHeart(EMPTY);
		m_vHeart[i].m_rtArea.m_vLeftTop = vHPLocation;
		m_vHeart[i].m_rtArea.m_vLeftTop[0] += i * (m_vHeart[i].m_rtArea.m_vSize[0] + 10);
		m_vHeart[i].render();
	}

	return true;
}

bool EnterTheGungeon::release()
{
	m_pUser->release();
	for (int i = MIN_ENEMY_SERIAL_NUM; i < MIN_ENEMY_SERIAL_NUM + I_ObjectManager.getNumOfEnemy(); i++) {
		if (I_ObjectManager.getEnemy(i))
			I_ObjectManager.getEnemy(i)->render();
	}

	m_pMapObject->release();

	I_Sound.stop(m_pBGM);
	for (JSoundChannel*& curGunshot : m_vGunShots) {
		I_Sound.stop(curGunshot);
	}

	return true;
}

bool EnterTheGungeon::checkCollision()
{
	m_pUser->checkCollision();

	for (int i = MIN_ENEMY_SERIAL_NUM; i < MIN_ENEMY_SERIAL_NUM + I_ObjectManager.getNumOfEnemy(); i++) {
		if (I_ObjectManager.getEnemy(i))
			I_ObjectManager.getEnemy(i)->checkCollision();
	}

	return true;
}
