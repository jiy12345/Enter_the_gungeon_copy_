#pragma once
#include "JSingleton.h"
#include "JWindow.h"
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")

class JDevice : public JSingleton<JDevice>
{
	friend class JSingleton<JDevice>;
public:
	ID3D11Device*			m_pd3dDevice = nullptr;
	ID3D11DeviceContext*	m_pImmediateContext = nullptr;
	IDXGIFactory*			m_pGIFactory = nullptr;
	IDXGISwapChain*			m_pSwapChain = nullptr;
	ID3D11RenderTargetView* m_pRTV = nullptr;
public:
	HRESULT createDevice();
	HRESULT createDXGIDevice();
	HRESULT createSwapChain();
	HRESULT createRenderTargetView();
	void	createViewport();
public:
	virtual bool init();
	virtual bool frame();
	virtual bool render();
	virtual bool release();
private:
	JDevice() {};
	~JDevice() = default;
	JDevice(const JDevice&) = delete;
	JDevice& operator=(const JDevice&) = delete;
};
#define I_Device JDevice::GetInstance()