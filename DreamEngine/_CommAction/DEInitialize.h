#pragma once
#include<d3d9.h>
#include<d3dx9.h>

class DDEInitialize
{
public:
	DDEInitialize();
	~DDEInitialize();
public:
	static BOOL InitializeD3D(HWND hWnd, bool fullscreen, UINT width, UINT height);
	static VOID EndInitD3D();
	static LPDIRECT3DDEVICE9 g_device;
	static LPDIRECT3DDEVICE9 GetDevice() { return DDEInitialize::g_device; }
};
