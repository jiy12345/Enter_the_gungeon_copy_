#include "JShaderManager.h"

HRESULT JShaderManager::loadVS(ID3D11VertexShader* &m_pVS, std::wstring fileName, std::string funName)
{
    HRESULT hr;
    ID3DBlob* pErrorCode = nullptr;

    auto iter = m_VSList.find(fileName);
    if (iter != m_VSList.end())
    {
        m_pVS = (iter->second).second;
        return S_OK;
    }

    ID3DBlob* pVSCode = nullptr;
    hr = D3DCompileFromFile(
        fileName.c_str(),
        NULL,
        NULL,
        funName.c_str(),
        "vs_5_0",
        0,
        0,
        &pVSCode,
        &pErrorCode);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }

    hr = I_Device.m_pd3dDevice->CreateVertexShader(
        pVSCode->GetBufferPointer(),
        pVSCode->GetBufferSize(),
        NULL,
        &m_pVS);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }

    if (m_pVS)
    {
        if (SUCCEEDED(hr))
        {
            m_VSList.insert({ fileName, {pVSCode, m_pVS} });
        }
    }

    return hr;
}

HRESULT JShaderManager::loadVSCode(ID3DBlob* &m_pVSCode, std::wstring fileName, std::string funName)
{
    HRESULT hr;
    ID3DBlob* pErrorCode = nullptr;

    auto iter = m_VSList.find(fileName);
    if (iter != m_VSList.end())
    {
        m_pVSCode = (iter->second).first;
        return S_OK;
    }

    hr = D3DCompileFromFile(
        fileName.c_str(),
        NULL,
        NULL,
        funName.c_str(),
        "vs_5_0",
        0,
        0,
        &m_pVSCode,
        &pErrorCode);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }

    ID3D11VertexShader* pVS = nullptr;
    hr = I_Device.m_pd3dDevice->CreateVertexShader(
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
        NULL,
        &pVS);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }

    if (pVS)
    {
        if (SUCCEEDED(hr))
        {
            m_VSList.insert({ fileName, {m_pVSCode, pVS} });
        }
    }

    return hr;
}

HRESULT JShaderManager::loadPS(ID3D11PixelShader* &m_pPS, std::wstring fileName, std::string funName)
{
    HRESULT hr;
    ID3DBlob* pErrorCode = nullptr;

    auto iter = m_PSList.find(fileName);
    if (iter != m_PSList.end())
    {
        m_pPS = iter->second;
        return S_OK;
    }

    ID3DBlob* pPSCode = nullptr;
    hr = D3DCompileFromFile(
        fileName.c_str(),
        NULL,
        NULL,
        funName.c_str(),
        "ps_5_0",
        0,
        0,
        &pPSCode,
        &pErrorCode);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }

    hr = I_Device.m_pd3dDevice->CreatePixelShader(
        pPSCode->GetBufferPointer(),
        pPSCode->GetBufferSize(),
        NULL,
        &m_pPS);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }

    if (m_pPS)
    {
        if (SUCCEEDED(hr))
        {
            m_PSList.insert(std::make_pair(fileName, m_pPS));
        }
    }

    pPSCode->Release();
    return hr;
}

bool JShaderManager::Release()
{
    for (auto data : m_VSList)
    {
        ID3DBlob* pData1           = data.second.first;
        ID3D11VertexShader* pData2 = data.second.second;
        if (pData1) pData1->Release();
        if (pData1) pData2->Release();
        pData1 = nullptr;
        pData2 = nullptr;
    }
    m_VSList.clear();

    for (auto data : m_PSList)
    {
        ID3D11PixelShader* pData = data.second;
        if (pData) pData->Release();
        pData = nullptr;
    }
    m_VSList.clear();
    return true;
}
