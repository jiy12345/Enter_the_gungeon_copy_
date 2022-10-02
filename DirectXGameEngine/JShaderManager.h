#pragma once
#include"stdafx.h"

class JShaderManager : public JSingleton<JShaderManager> {
	friend class JSingleton<JShaderManager>;
private:
	std::unordered_map<std::wstring, std::pair<ID3DBlob* , ID3D11VertexShader*>>	m_VSList;
	std::unordered_map<std::wstring, ID3D11PixelShader*>							m_PSList;
public:
	HRESULT	loadVS(ID3D11VertexShader* &m_pVS, std::wstring fileName, std::string funName = "VS");
	HRESULT	loadVSCode(ID3DBlob* &m_pVSCode, std::wstring fileName, std::string funName = "VS");
	HRESULT	loadPS(ID3D11PixelShader* &m_pPS, std::wstring fileName, std::string funName = "PS");
	bool	Release();
private:
	JShaderManager() {};
	~JShaderManager() { Release(); };
	JShaderManager(const JShaderManager&) = delete;
	JShaderManager& operator=(const JShaderManager&) = delete;
};

#define I_Shader JShaderManager::GetInstance()