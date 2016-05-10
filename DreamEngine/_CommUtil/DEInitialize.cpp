#include "DEInitialize.h"

LPDIRECT3DDEVICE9 DDEInitialize::gRootDevice = nullptr;
DDEInitialize::DDEInitialize()
{
	//InitializeD3D(hWnd, false, 800, 600);
}

DDEInitialize::~DDEInitialize()
{

}

BOOL DDEInitialize::InitializeD3D(HWND hWnd, bool fullscreen, UINT width, UINT height)
{
	LPDIRECT3D9 d3d;
	D3DDISPLAYMODE displayMode;
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == nullptr)
		return FALSE;

	// Get the desktop display mode.
	if (FAILED(d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))
		return FALSE;

	// Set up the structure used to create the D3DDevice
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	// Default to none.
	D3DMULTISAMPLE_TYPE multiType = D3DMULTISAMPLE_NONE;

	// Check if 4x AA is supported, if so use it.
	if (d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, displayMode.Format, !fullscreen,
		D3DMULTISAMPLE_8_SAMPLES,
		nullptr) == D3D_OK) multiType = D3DMULTISAMPLE_8_SAMPLES;

	if (fullscreen)
	{
		d3dpp.Windowed = FALSE;
		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;
	}
	else
		d3dpp.Windowed = TRUE;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 2;
	d3dpp.MultiSampleType = multiType;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Create the D3DDevice
	if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &DDEInitialize::gRootDevice)))
		return FALSE;

	d3d->Release();
	return TRUE;
}

VOID DDEInitialize::EndInitD3D()
{
	if (DDEInitialize::gRootDevice != nullptr)
		while (DDEInitialize::gRootDevice->Release() != 0);

	DDEInitialize::gRootDevice = nullptr;
}
