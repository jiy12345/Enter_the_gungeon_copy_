#pragma once
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#include "stdafx.h"

#pragma comment (lib, "fmod_vc.lib")

class JSoundChannel {
	friend class JSoundManager;
private:
	std::wstring m_fileName;
	FMOD::Channel* m_pChannel;
public:
	JSoundChannel(std::wstring fileName) {
		m_fileName = fileName;
		m_pChannel = nullptr;
	}
	bool release() {
		m_pChannel->stop();
	}
};

class JSoundManager : public JSingleton<JSoundManager> {
	friend class JSingleton<JSoundManager>;
private:
	FMOD::System* m_pSystem = nullptr;
private:
	std::unordered_map<std::wstring, FMOD::Sound*> m_List;
public:
	bool init();
	bool release();
	bool frame();
	void pause(const JSoundChannel* pChannel);
	void resume(const JSoundChannel* pChannel);
	void volumeUp(const JSoundChannel* pChannel, float fVolume = 0.1f);
	void volumeDown(const JSoundChannel* pChannel, float fVolume = 0.1f);
	bool play(JSoundChannel* pChannel, bool bIsLoop = false);
	bool playEffect(JSoundChannel* pChannel, bool bIsLoop = false);
	void stop(const JSoundChannel* pChannel);
private:
	void setLoop(FMOD::Sound* pSound, bool bIsLoop = false);
	bool load(FMOD::Sound*& m_pSound, std::wstring fileName);
	bool isPlay(FMOD::Channel*& m_pChannel);
private:
	JSoundManager() {};
	~JSoundManager() = default;
	JSoundManager(const JSoundManager&) = delete;
	JSoundManager& operator=(const JSoundManager&) = delete;
};

#define I_Sound JSoundManager::GetInstance()