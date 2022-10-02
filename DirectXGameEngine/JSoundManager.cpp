#include "JSoundManager.h"

bool JSoundManager::init()
{
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, 0);
	return true;
}

bool JSoundManager::release()
{
	for (auto data : m_List)
	{
		FMOD::Sound* pData = data.second;
		if (pData) pData->release();
		pData = nullptr;
	}
	m_pSystem->close();
	m_pSystem->release();
	m_List.clear();
	return true;
}

bool JSoundManager::frame()
{
	m_pSystem->update();
	return true;
}

void JSoundManager::pause(const JSoundChannel* pChannel)
{
	if (pChannel->m_pChannel == nullptr) return;
	bool isPaused;
	pChannel->m_pChannel->getPaused(&isPaused);
	if (isPaused == false) pChannel->m_pChannel->setPaused(true);
}

void JSoundManager::resume(const JSoundChannel* pChannel)
{
	if (pChannel->m_pChannel == nullptr) return;
	bool isPaused;
	pChannel->m_pChannel->getPaused(&isPaused);
	if (isPaused == true) pChannel->m_pChannel->setPaused(false);
}

void JSoundManager::volumeUp(const JSoundChannel* pChannel, float fVolume)
{
	float fCurVolume = 0.0f;
	pChannel->m_pChannel->getVolume(&fCurVolume);
	fCurVolume += fVolume;
	fCurVolume = min(1.0f, fCurVolume);
	pChannel->m_pChannel->setVolume(fCurVolume);
}

void JSoundManager::volumeDown(const JSoundChannel* pChannel, float fVolume)
{
	float fCurVolume = 0.0f;
	pChannel->m_pChannel->getVolume(&fCurVolume);
	fCurVolume -= fVolume;
	fCurVolume = min(1.0f, fCurVolume);
	pChannel->m_pChannel->setVolume(fCurVolume);
}

bool JSoundManager::play(JSoundChannel* pChannel, bool bIsLoop)
{
	if (isPlay(pChannel->m_pChannel) == false)
	{
		FMOD::Sound* pSound = nullptr;
		load(pSound, pChannel->m_fileName);
		FMOD_RESULT hr =
			m_pSystem->playSound(pSound, nullptr, false,
				&pChannel->m_pChannel);
		if (hr == FMOD_OK)
		{
			pChannel->m_pChannel->setVolume(0.5f);
			setLoop(pSound, bIsLoop);
		}
	}
	return true;
}

bool JSoundManager::playEffect(JSoundChannel* pChannel, bool bIsLoop)
{
	FMOD::Sound* pSound = nullptr;
	load(pSound, pChannel->m_fileName);
	FMOD_RESULT hr =
		m_pSystem->playSound(pSound, nullptr, false,
			&pChannel->m_pChannel);
	if (hr == FMOD_OK)
	{
		pChannel->m_pChannel->setVolume(0.5f);
		setLoop(pSound, bIsLoop);
	}
	return true;
}

void JSoundManager::stop(const JSoundChannel* pChannel)
{
	if (pChannel->m_pChannel == nullptr) return;
	pChannel->m_pChannel->stop();
}

void JSoundManager::setLoop(FMOD::Sound* pSound, bool bIsLoop)
{
	if (bIsLoop)
		pSound->setMode(FMOD_LOOP_NORMAL);
	else
		pSound->setMode(FMOD_LOOP_OFF);
}

bool JSoundManager::load(FMOD::Sound*& m_pSound, std::wstring fileName)
{
	auto iter = m_List.find(fileName);
	if (iter != m_List.end())
	{
		m_pSound = iter->second;
		return true;
	}
	FMOD_RESULT hr = m_pSystem->createSound(
		to_wm(fileName).c_str(),
		FMOD_DEFAULT, nullptr,
		&m_pSound);

	m_List.insert({ fileName, m_pSound });

	return (hr == FMOD_OK) ? true : false;
}

bool JSoundManager::isPlay(FMOD::Channel*& m_pChannel)
{
	bool playing = false;
	if (m_pChannel != nullptr)
	{
		m_pChannel->isPlaying(&playing);
	}
	return playing;
}
