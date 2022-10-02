#pragma once
#include "stdafx.h"
class JDXState
{
public:
	static ID3D11SamplerState* g_pDefaultSSWrap;
	static ID3D11SamplerState* g_pDefaultSSMirror;
	static ID3D11RasterizerState* g_pDefaultRSWireFrame;
	static ID3D11RasterizerState* g_pDefaultRSSolid;
	static ID3D11BlendState* g_pAlphaBlend;

	static bool setState();
	static bool release();
};


