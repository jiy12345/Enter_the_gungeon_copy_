#include "JTextureManager.h"

HRESULT JTextureManager::loadSRV(ID3D11ShaderResourceView*& m_pTextureSRV, std::wstring fileName)
{
	auto iter = m_List.find(fileName);
	if (iter != m_List.end())
	{
		m_pTextureSRV = (iter->second)->m_pTextureSRV;
		return S_OK;
	}

	JTexture* pJTexture = new JTexture;

	HRESULT hr = DirectX::CreateWICTextureFromFile(
		I_Device.m_pd3dDevice,
		I_Device.m_pImmediateContext,
		fileName.c_str(),
		(ID3D11Resource**)&pJTexture->m_pTexture,
		&pJTexture->m_pTextureSRV);
	if (FAILED(hr))
	{
		hr = DirectX::CreateDDSTextureFromFile(
			I_Device.m_pd3dDevice,
			I_Device.m_pImmediateContext,
			fileName.c_str(),
			(ID3D11Resource**)&pJTexture->m_pTexture,
			&pJTexture->m_pTextureSRV);
	}

	if (FAILED(hr)) {
		return hr;
	}
	
	(pJTexture->m_pTexture)->GetDesc(&pJTexture->m_Desc);

	m_pTextureSRV = pJTexture->m_pTextureSRV;
	m_List.insert({ fileName, pJTexture });

	return hr;
}

bool JTextureManager::release()
{
	for (auto data : m_List)
	{
		JTexture* pTexture = data.second;
		if (pTexture->m_pTexture) pTexture->m_pTexture->Release();
		if (pTexture->m_pTextureSRV) pTexture->m_pTextureSRV->Release();
		delete pTexture;
	}
	m_List.clear();
    return true;
}

JTextureManager::~JTextureManager()
{
	release();
}
