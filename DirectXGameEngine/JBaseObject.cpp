#include "JBaseObject.h"

void JBaseObject::getNDC(nCube<2>& rtArea)
{
	rtArea.m_vLeftTop[0] = rtArea.m_vLeftTop[0] / I_Window.m_rtClient.right * 2 - 1;
	rtArea.m_vLeftTop[1] = -((rtArea.m_vLeftTop[1] + rtArea.m_vSize[1]) / I_Window.m_rtClient.bottom * 2 - 1);
	rtArea.m_vSize[0] = rtArea.m_vSize[0] / I_Window.m_rtClient.right * 2;
	rtArea.m_vSize[1] = rtArea.m_vSize[1] / I_Window.m_rtClient.bottom * 2;
}

void JBaseObject::setVSName(std::wstring wstrVSName)
{
	m_wstrVSName = wstrVSName;
}

void JBaseObject::setPSName(std::wstring wstrPSName)
{
	m_wstrPSName = wstrPSName;
}

void JBaseObject::setVSFuncName(std::string strVSFuncName)
{
	m_strVSFuncName = strVSFuncName;
}

void JBaseObject::setPSFuncName(std::string strPSFuncName)
{
	m_strPSFuncName = strPSFuncName;
}

void JBaseObject::setTextureName(std::wstring wstrTextureName)
{
	m_wstrTextureName = wstrTextureName;
}

void JBaseObject::setVertexData()
{
	m_VertexList.resize(4);
	m_VertexList[0].p = { -1.0f, 1.0f, 0.0f };
	m_VertexList[1].p = { 1.0f, 1.0f,  0.0f };
	m_VertexList[2].p = { -1.0f, -1.0f, 0.0f };
	m_VertexList[3].p = { 1.0f, -1.0f, 0.0f };

	m_VertexList[0].c = { 1.0f, 0.5f, 1.0f, 1.0f };
	m_VertexList[1].c = { 1.0f, 1.0f, 0.0f, 1.0f };
	m_VertexList[2].c = { 0.0f, 1.0f, 1.0f, 1.0f };
	m_VertexList[3].c = { 1.0f, 1.0f, 0.0f, 1.0f };

	m_VertexList[0].t = { 0.0f, 0.0f };
	m_VertexList[1].t = { 1.0f, 0.0f };
	m_VertexList[2].t = { 0.0f, 1.0f };
	m_VertexList[3].t = { 1.0f, 1.0f };
}

void JBaseObject::setIndexData()
{
	m_IndexList.resize(6);
	m_IndexList[0] = 0;
	m_IndexList[1] = 1;
	m_IndexList[2] = 2;
	m_IndexList[3] = 2;
	m_IndexList[4] = 1;
	m_IndexList[5] = 3;
}

HRESULT JBaseObject::createVertexBuffer()
{
	setVertexData();
	D3D11_BUFFER_DESC       bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(SimpleVertex) * m_VertexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA  sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_VertexList.at(0);
	return I_Device.m_pd3dDevice->CreateBuffer(
		&bd,
		&sd,
		&m_pVertexBuffer);
}

HRESULT JBaseObject::createIndexBuffer()
{
	setIndexData();
	D3D11_BUFFER_DESC       bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(DWORD) * m_IndexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA  sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_IndexList.at(0);
	return I_Device.m_pd3dDevice->CreateBuffer(
		&bd,
		&sd,
		&m_pIndexBuffer);
}

HRESULT JBaseObject::createVertexLayout()
{
	HRESULT hr;
	ID3DBlob* pVSCode = nullptr;
	hr = I_Shader.loadVSCode(pVSCode, m_wstrVSName, m_strVSFuncName);
	if (FAILED(hr)) return hr;

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,12,D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0,28,D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT NumElements = sizeof(ied) / sizeof(ied[0]);
	hr = I_Device.m_pd3dDevice->CreateInputLayout(
		ied,
		NumElements,
		pVSCode->GetBufferPointer(),
		pVSCode->GetBufferSize(),
		&m_pVertexLayout);

	return hr;
}

void JBaseObject::updateUVCoord()
{
	if (m_curSprite == IS_NOT_SPRITE) return;
	m_fEffectTimer += I_Timer.m_fElapseTimer;
	if (m_fStep <= m_fEffectTimer)
	{
		m_fEffectTimer -= m_fStep;
		m_iIndexOfSprite++;
	}
	if (m_iIndexOfSprite >= m_vSpriteInfo->at(m_curSprite).m_iNumFrame)
	{
		m_fEffectTimer = 0;
		m_iIndexOfSprite = 0;
	}
	m_rtUV = m_vSpriteInfo->at(m_curSprite).m_vSpriteRtLists[m_iIndexOfSprite];

	m_rtUV.m_vLeftTop[0] /= m_vSpriteInfo->at(m_curSprite).m_vTotalTextureSize[0];
	m_rtUV.m_vLeftTop[1] /= m_vSpriteInfo->at(m_curSprite).m_vTotalTextureSize[1];
	m_rtUV.m_vSize[0] /= m_vSpriteInfo->at(m_curSprite).m_vTotalTextureSize[0];
	m_rtUV.m_vSize[1] /= m_vSpriteInfo->at(m_curSprite).m_vTotalTextureSize[1];
}

void JBaseObject::updateVertexBuffer()
{
	nCube<2> rtNDC = m_rtArea;
	I_Camera.getCameraCoord(rtNDC);
	getNDC(rtNDC);
	std::cout << rtNDC.m_vLeftTop[0] << " " << rtNDC.m_vLeftTop[1] << '\n';
	m_VertexList[0].p = { rtNDC.m_vLeftTop[0], rtNDC.m_vLeftTop[1] + rtNDC.m_vSize[1], 0.0f };
	m_VertexList[0].t = { m_rtUV.m_vLeftTop[0], m_rtUV.m_vLeftTop[1] };

	m_VertexList[1].p = { rtNDC.m_vLeftTop[0] + rtNDC.m_vSize[0],  rtNDC.m_vLeftTop[1] + rtNDC.m_vSize[1],  0.0f };
	m_VertexList[1].t = { m_rtUV.m_vLeftTop[0] + m_rtUV.m_vSize[0], m_rtUV.m_vLeftTop[1] };

	m_VertexList[2].p = { rtNDC.m_vLeftTop[0],  rtNDC.m_vLeftTop[1], 0.0f };
	m_VertexList[2].t = { m_rtUV.m_vLeftTop[0], m_rtUV.m_vLeftTop[1] + m_rtUV.m_vSize[1] };

	m_VertexList[3].p = { rtNDC.m_vLeftTop[0] + rtNDC.m_vSize[0],  rtNDC.m_vLeftTop[1], 0.0f };
	m_VertexList[3].t = { m_rtUV.m_vLeftTop[0] + m_rtUV.m_vSize[0], m_rtUV.m_vLeftTop[1] + m_rtUV.m_vSize[1] };

	I_Device.m_pImmediateContext->UpdateSubresource(
		m_pVertexBuffer, NULL, NULL, &m_VertexList.at(0), 0, 0);
}

bool JBaseObject::init()
{
	createVertexBuffer();
	createIndexBuffer();
	createVertexLayout();
	return true;
}

bool JBaseObject::frame()
{
	return true;
}

bool JBaseObject::preRender()
{
	HRESULT hr;
	ID3D11ShaderResourceView* pSRV = nullptr;
	hr = I_Tex.loadSRV(pSRV, m_wstrTextureName);

	ID3D11VertexShader* pVS = nullptr;
	hr = I_Shader.loadVS(pVS, m_wstrVSName, m_strVSFuncName);
	if (FAILED(hr)) return false;

	ID3D11PixelShader* pPS = nullptr;
	hr = I_Shader.loadPS(pPS, m_wstrPSName, m_strPSFuncName);
	if (FAILED(hr)) return false;

	updateUVCoord();
	updateVertexBuffer();

	I_Device.m_pImmediateContext->PSSetShaderResources(0, 1, &pSRV);
	I_Device.m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
	I_Device.m_pImmediateContext->VSSetShader(pVS, NULL, 0);
	I_Device.m_pImmediateContext->PSSetShader(pPS, NULL, 0);
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	I_Device.m_pImmediateContext->IASetVertexBuffers(0, 1,
		&m_pVertexBuffer, &stride, &offset);
	I_Device.m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer,
		DXGI_FORMAT_R32_UINT, 0);
	return true;
}

bool JBaseObject::render()
{
	preRender();
	postRender();
	return true;
}

bool JBaseObject::postRender()
{
	if (m_pIndexBuffer == nullptr)
		I_Device.m_pImmediateContext->Draw(m_VertexList.size(), 0);
	else
		I_Device.m_pImmediateContext->DrawIndexed(m_IndexList.size(), 0, 0);
	return true;
}

bool JBaseObject::release()
{
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pIndexBuffer) m_pIndexBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();
	return true;
}

JBaseObject::~JBaseObject()
{
	release();
}
