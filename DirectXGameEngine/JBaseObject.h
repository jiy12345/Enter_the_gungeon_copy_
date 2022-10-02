#pragma once
#include "stdafx.h"
#include "JDevice.h"
#include "JShaderManager.h"
#include "JTextureManager.h"
#include "JSpriteManager.h"
#include "JCamera.h"

#define IS_NOT_SPRITE -1

struct SimpleVertex
{
	JVector<3> p;
	JVector<4> c;
	JVector<2> t;
};

class JBaseObject
{
public:
	int 					m_curSprite = IS_NOT_SPRITE;
	int						m_iIndexOfSprite = 0;
	float					m_fStep;
	float					m_fEffectTimer = 0.0f;
	std::vector<JSprite>*	m_vSpriteInfo;
public:
	nCube<2>				m_rtUV;
	nCube<2>				m_rtArea;
public:
	float					m_fSpeed = 500.0f;
public:
	std::wstring				m_wstrVSName = L"DefaulTextureShader.hlsl";
	std::wstring				m_wstrPSName = L"DefaulTextureShader.hlsl";
	std::string					m_strVSFuncName = "VS";
	std::string					m_strPSFuncName = "PS";
	std::wstring				m_wstrTextureName = L"_RAINBOW.bmp";
	ID3D11Buffer*				m_pVertexBuffer;
	ID3D11Buffer*				m_pIndexBuffer;
	ID3D11InputLayout*			m_pVertexLayout;
	std::vector<SimpleVertex>   m_VertexList;
	std::vector<DWORD>			m_IndexList;
public:
	void				getNDC(nCube<2>& rtArea);
public:
	void				setVSName(std::wstring wstrVSName);
	void				setPSName(std::wstring wstrPSName);
	void				setVSFuncName(std::string strVSFuncName);
	void				setPSFuncName(std::string strPSFuncName);
	void				setTextureName(std::wstring strTextureName);
public:
	virtual void		setVertexData();
	virtual void		setIndexData();
	virtual HRESULT		createVertexBuffer();
	virtual HRESULT		createIndexBuffer();
	virtual HRESULT     createVertexLayout();
	virtual void		updateUVCoord();
	virtual void		updateVertexBuffer();
public:
	virtual bool		init();
	virtual bool		frame();
	virtual bool		render();
	virtual bool		release();
protected:
	bool				preRender();
	bool				postRender();
public:
	JBaseObject() {
		m_wstrTextureName = L"../data/sprites/pilot.png";
		m_rtUV.Set({ 0 / 988.0f, 24 / 811.0f }, { 15 / 988.0f, 22 / 811.0f });
		float ratio = 15 / 22.0f;
		m_rtArea.Set({ 0, 0 }, { 40 * ratio, 40 });
	}
	virtual				 ~JBaseObject();
};