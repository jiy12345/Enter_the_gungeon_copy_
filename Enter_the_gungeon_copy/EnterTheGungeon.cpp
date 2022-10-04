#define _CRT_SECURE_NO_WARNINGS
#include "EnterTheGungeon.h"

#define WINDOW_SIZE_X 1024
#define WINDOW_SIZE_Y 768
#define WINDOW_NAME L"DirectXGameEngine"

int APIENTRY wWinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPWSTR		lpCmdLine,
	int			nCmdShow) {
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
	m_pUser = new JUser;
	m_pMapObject = new JBaseObject;
	m_pMapObject->m_wstrTextureName = L"_RAINBOW.bmp";
	m_pMapObject->m_rtUV.Set({ 0, 0 }, { 1, 1 });
	m_pMapObject->m_rtArea.Set({ -1024, -768 }, { 1024 * 2, 768 * 2 });
	m_pUser->init();
	m_pMapObject->init();

	m_vEnemy.resize(5);
	for (auto& curEnemy : m_vEnemy) {
		curEnemy = new bullet_kin();
		curEnemy->init();
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

	for (auto curEnemy : m_vEnemy) {
		curEnemy->frame();
	}

	for (auto bullet : I_ObjectPool.PoolObjects) {
		bullet->update();
	}

	I_Camera.m_rtCamera.m_vLeftTop = m_pUser->m_rtArea.vCenter() - (JVector<2>{ I_Window.m_rtClient.right, I_Window.m_rtClient.bottom } / 2);
	return true;
}

bool EnterTheGungeon::render()
{
	m_pMapObject->render();
	m_pUser->render();

	for (auto curEnemy : m_vEnemy) {
		curEnemy->render();
	}

	for (auto bullet : I_ObjectPool.PoolObjects) {
		bullet->render_objectPool();
	}
	return true;
}

bool EnterTheGungeon::release()
{
	m_pUser->release();
	for (auto curEnemy : m_vEnemy) {
		curEnemy->release();
	}

	m_pMapObject->release();
	I_Sound.stop(m_pBGM);
	for (JSoundChannel*& curGunshot : m_vGunShots) {
		I_Sound.stop(curGunshot);
	}
	m_vEnemy.clear();
	return true;
}