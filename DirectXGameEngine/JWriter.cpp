#include "JWriter.h"

bool JWriter::init()
{
	HRESULT hr;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_d2dFactory);
	if (FAILED(hr)) return false;
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&m_pDWriteFactory);
	if (FAILED(hr)) return false;
	hr = m_pDWriteFactory->CreateTextFormat(
		L"°íµñ",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		30,
		L"en-us",
		&m_pTextFormat);
	if (FAILED(hr)) return false;
	m_szDefaultText = L"KGCA Game Academy";

	return true;
}

bool JWriter::frame()
{
	m_szDefaultText = I_Timer.m_szTimer;
	return true;
}

bool JWriter::render()
{
	draw(0, 0, m_szDefaultText, { 0,1,1,1 });
	return true;
}

bool JWriter::release()
{
	if (m_pColorBrush) m_pColorBrush->Release();
	if (m_pDWriteFactory) m_pDWriteFactory->Release();
	if (m_d2dRT) m_d2dRT->Release();
	if (m_d2dFactory) m_d2dFactory->Release();
	return true;
}

bool JWriter::set(IDXGISurface1* dxgiSurface)
{
	D2D1_RENDER_TARGET_PROPERTIES props;
	ZeroMemory(&props, sizeof(props));
	props.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	props.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
	props.dpiX = 96;
	props.dpiY = 96;
	props.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	props.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

	HRESULT hr = m_d2dFactory->CreateDxgiSurfaceRenderTarget(
		dxgiSurface,
		&props,
		&m_d2dRT);
	if (FAILED(hr)) return false;

	hr = m_d2dRT->CreateSolidColorBrush({ 0, 0, 0, 1 }, &m_pColorBrush);
	if (FAILED(hr)) return false;

	return true;
}

bool JWriter::draw(float x, float y, std::wstring text, D2D1_COLOR_F color)
{
	m_d2dRT->BeginDraw();

	D2D1_RECT_F rt = { x, y, I_Window.m_rtClient.right, I_Window.m_rtClient.bottom };
	m_pColorBrush->SetColor(color);
	m_pColorBrush->SetOpacity(1.0f);
	m_d2dRT->DrawText(text.c_str(), text.size(), m_pTextFormat, rt, m_pColorBrush);
	m_d2dRT->EndDraw();
	return true;
}
