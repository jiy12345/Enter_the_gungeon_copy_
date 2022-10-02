#include "JDXState.h"

ID3D11SamplerState* JDXState::g_pDefaultSSWrap = nullptr;
ID3D11SamplerState* JDXState::g_pDefaultSSMirror = nullptr;
ID3D11BlendState* JDXState::g_pAlphaBlend = nullptr;
ID3D11RasterizerState* JDXState::g_pDefaultRSWireFrame = nullptr;
ID3D11RasterizerState* JDXState::g_pDefaultRSSolid = nullptr;

bool JDXState::setState()
{
    HRESULT hr;
    D3D11_SAMPLER_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    hr = I_Device.m_pd3dDevice->CreateSamplerState(&sd, &g_pDefaultSSWrap);
    if (FAILED(hr)) return false;

    sd.Filter = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
    hr = I_Device.m_pd3dDevice->CreateSamplerState(&sd, &g_pDefaultSSMirror);
    if (FAILED(hr)) return false;

    D3D11_RASTERIZER_DESC rd;
    ZeroMemory(&rd, sizeof(rd));
    rd.DepthClipEnable = TRUE;
    rd.FillMode = D3D11_FILL_WIREFRAME;
    rd.CullMode = D3D11_CULL_NONE;
    hr = I_Device.m_pd3dDevice->CreateRasterizerState(&rd,
        &g_pDefaultRSWireFrame);
    if (FAILED(hr)) return false;

    rd.FillMode = D3D11_FILL_SOLID;
    hr = I_Device.m_pd3dDevice->CreateRasterizerState(&rd,
        &g_pDefaultRSSolid);
    if (FAILED(hr)) return false;

    D3D11_BLEND_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.RenderTarget[0].BlendEnable = TRUE;
    bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    hr = I_Device.m_pd3dDevice->CreateBlendState(&bd, &g_pAlphaBlend);
    if (FAILED(hr)) return false;

    return true;
}

bool JDXState::release()
{
    if (g_pAlphaBlend) g_pAlphaBlend->Release();
    if (g_pDefaultSSWrap) g_pDefaultSSWrap->Release();
    if (g_pDefaultSSMirror) g_pDefaultSSMirror->Release();
    if (g_pDefaultRSSolid)g_pDefaultRSSolid->Release();
    if (g_pDefaultRSWireFrame)g_pDefaultRSWireFrame->Release();
    return true;
}
