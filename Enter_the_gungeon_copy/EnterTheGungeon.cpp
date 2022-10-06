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
	m_pMapObject = new JBaseObject;
	m_pMapObject->m_wstrTextureName = L"_RAINBOW.bmp";
	m_pMapObject->m_rtUV.Set({ 0, 0 }, { 1, 1 });
	m_pMapObject->m_rtArea.Set({ -(MAP_SIZE_X / 2), -(MAP_SIZE_Y / 2) }, { MAP_SIZE_X, MAP_SIZE_Y });
	m_pUser->init();
	m_pMapObject->init();

	for (int i = 0; i < 100;i++) {
		auto curEnemy = I_ObjectManager.GetRecycledEnemy<bullet_kin>();
		curEnemy->init();
		curEnemy->m_rtArea.m_vLeftTop[0] = rand() % MAP_SIZE_X - MAP_SIZE_X / 2;
		curEnemy->m_rtArea.m_vLeftTop[1] = rand() % MAP_SIZE_Y - MAP_SIZE_Y / 2;
	}

	m_vGunShots.resize(32);
	for (JSoundChannel*& curGunshot : m_vGunShots) {
		
		curGunshot = new JSoundChannel(L"Gun1.wav");
	}
	m_pBGM = new JSoundChannel(L"MyLove.mp3");

	return true;
}

bool EnterTheGungeon::frame()
{
	if (I_Input.GetKey(VK_HOME) == KEY_PUSH)
	{
		for (JSoundChannel*& curGunshot : m_vGunShots) {
			I_Sound.playEffect(curGunshot, false);
		}
	}
	if (I_Input.GetKey(VK_INSERT) == KEY_PUSH)
	{
		I_Sound.play(m_pBGM, true);
	}
	if (I_Input.GetKey(VK_END) == KEY_PUSH)
	{
		I_Sound.stop(m_pBGM);
	}
	if (I_Input.GetKey(VK_F1) == KEY_PUSH)
	{
		I_Sound.pause(m_pBGM);
	}
	if (I_Input.GetKey(VK_F2) == KEY_PUSH)
	{
		I_Sound.resume(m_pBGM);
	}
	m_pUser->frame();
	m_pMapObject->frame();

	for (int i = 0; i < I_ObjectManager.getNumOfEnemy(); i++) {
		if (I_ObjectManager.getEnemy(i))
			I_ObjectManager.getEnemy(i)->frame();
	}

	for (int i = 0; i < I_ObjectManager.getNumOfUserBullet(); i++) {
		if(I_ObjectManager.getUserBullet(i)) 
			I_ObjectManager.getUserBullet(i)->frame();
	}
	for (int i = 0; i < I_ObjectManager.getNumOfEnemyBullet(); i++) {
		if (I_ObjectManager.getEnemyBullet(i)) 
			I_ObjectManager.getEnemyBullet(i)->frame();
	}

	I_Camera.m_rtCamera.m_vLeftTop = m_pUser->m_rtArea.vCenter() - (JVector<2>{ I_Window.m_rtClient.right, I_Window.m_rtClient.bottom } / 2);
	return true;
}

bool EnterTheGungeon::render()
{
	m_pMapObject->render();
	m_pUser->render();

	for (int i = 0; i < I_ObjectManager.getNumOfEnemy(); i++) {
		if (I_ObjectManager.getEnemy(i))
			I_ObjectManager.getEnemy(i)->render();
	}

	for (int i = 0; i < I_ObjectManager.getNumOfUserBullet(); i++) {
		if (I_ObjectManager.getUserBullet(i))
			I_ObjectManager.getUserBullet(i)->render();
	}
	for (int i = 0; i < I_ObjectManager.getNumOfEnemyBullet(); i++) {
		if (I_ObjectManager.getEnemyBullet(i))
			I_ObjectManager.getEnemyBullet(i)->render();
	}
	return true;
}

bool EnterTheGungeon::release()
{
	m_pUser->release();
	for (int i = 0; i < I_ObjectManager.getNumOfEnemy(); i++) {
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