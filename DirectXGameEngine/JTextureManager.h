#pragma once
#include "stdafx.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#pragma comment(lib, "../lib/DirectXTK.lib")

struct JTexture {
	ID3D11Texture2D*			m_pTexture;
	ID3D11ShaderResourceView*	m_pTextureSRV;
	D3D11_TEXTURE2D_DESC		m_Desc;
};

class JTextureManager : public JSingleton<JTextureManager>
{
	friend class JSingleton<JTextureManager>;
private:
	std::unordered_map<std::wstring, JTexture*> m_List;
public:
	HRESULT	loadSRV(ID3D11ShaderResourceView* & m_pTextureSRV, std::wstring fileName);
	bool	release();
private:
	JTextureManager() {};
	~JTextureManager();
	JTextureManager(const JTextureManager&) = delete;
	JTextureManager& operator=(const JTextureManager&) = delete;
};

#define I_Tex JTextureManager::GetInstance()
