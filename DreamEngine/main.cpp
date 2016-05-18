//#include "_CommAction\DEInitialize.h"
//#include "_Obj\RenderModule\DCamera.h"

#include "DEInitialize.h"
#include "CommObj.h"

#define WINDOW_CLASS    L"UGPDX"
#define WINDOW_NAME     L"DREAM ENGINE"
#define WINDOW_WIDTH    1024
#define WINDOW_HEIGHT   768

// Function Prototypes...
bool InitializeD3D(HINSTANCE hInst, HWND hWnd, bool fullscreen);
bool InitializeObjects();
void RenderScene();
void Shutdown();

//Teapot tp;
DSky* skybox;
DTerrain* terrain;
DCamera* camera;
DLight* light;
DGameObject* box;
DInput* input;
DFont * font;

WCHAR buff[1024] = { 0 };
//ID3DXMesh* Objects[4] = { 0, 0, 0, 0 };
//D3DXMATRIX  Worlds[4];
//D3DMATERIAL9 Mtrls[4];


LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	POINT p = { 0 };
	//D3DXVECTOR3 cameraPos;
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYUP:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'A':
			//tp.Move(DIRECT_RIGHT, -10.0f);
			break;
		case 'D':
			//tp.Move(DIRECT_RIGHT, 10.0f);
			break;
		case 'W':
			//tp.Move(DIRECT_FRONT, 10);
			break;
		case 'S':
			//tp.Move(DIRECT_FRONT, -10);
			break;
		case 'Q':
			//camera.Rotation(DIRECT_RIGHT, -0.05f);
			break;
		case 'E':
			//camera.Rotation(DIRECT_RIGHT, 0.05f);
			break;
		default:
			break;
		}
		//cameraPos = tp.GetPosition();
		//cameraPos.y = terrain->GetTerrainHeight(cameraPos.z, cameraPos.x);
		//tp.SetPosition(DIRECT_UP, cameraPos.y + 120);

		//swprintf_s(buff, L"camera position x %f  z %f \nmap height is %f", cameraPos.x, cameraPos.z,
		//	cameraPos.y);
		//camera.SetCameraView();
		break;
	case WM_LBUTTONDOWN:
		break;

	case WM_LBUTTONUP:
		break;

	case WM_MOUSEMOVE:
		int xPos = LOWORD(lParam);
		int yPos = HIWORD(lParam);
		//font->ShowText(0, 0, D3DXCOLOR(255, 0, 0, 255), buff);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE prevhInst, LPSTR cmdLine, int show)
{
	// Register the window class
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr,
		WINDOW_CLASS, nullptr };
	RegisterClassEx(&wc);

	// Create the application's window
	HWND hWnd = CreateWindow(WINDOW_CLASS, WINDOW_NAME, WS_OVERLAPPEDWINDOW,
		100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,
		GetDesktopWindow(), nullptr, wc.hInstance, nullptr);

	// Initialize Direct3D
	if (InitializeD3D(hInst, hWnd, false))
	{
		// Show the window
		MoveWindow(hWnd, 100, 0, WINDOW_WIDTH, WINDOW_HEIGHT, true);
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);

		// Enter the message loop
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));

		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
				RenderScene();
		}
	}
	// Release any and all resources.
	Shutdown();

	// Unregister our window.
	UnregisterClass(WINDOW_CLASS, wc.hInstance);
	return 0;
}


bool InitializeD3D(HINSTANCE hInst, HWND hWnd, bool fullscreen)
{
	if (!DDEInitialize::InitializeD3D(hWnd, fullscreen, WINDOW_WIDTH, WINDOW_HEIGHT))
		return false;
	if (!InitializeObjects()) 
		return false;

	input = new DInput(hInst, hWnd);
	input->CreateDevice(INPUTDEVICE::MouseDevice, COOPERALEVEL::ForeGround | COOPERALEVEL::NonExclusive);
	input->CreateDevice(INPUTDEVICE::KeyboardDevice, COOPERALEVEL::ForeGround | COOPERALEVEL::Exclusive);

	return true;
}

bool InitializeObjects()
{
	camera = new DCamera();
	camera->SetCameraZf(300000.0f);
	//camera->GetTransform()->Translate(D3DXVECTOR3(0.0f, 500.0f, -15.0f), Space::World);
	camera->GetTransform()->Translate(D3DXVECTOR3(0.0f, 0.0f, -5.0f), Space::World);

	terrain = new DTerrain(64, 64, 10, 2);
	terrain->CreateTerrain(L"..\\Resource\\coastMountain64.raw");

	skybox = new DSky(20000.0f);
	skybox->CreateSkybox(L"..\\Resource\\skybox\\frontsnow1.jpg", L"..\\Resource\\skybox\\backsnow1.jpg",
		L"..\\Resource\\skybox\\leftsnow1.jpg", L"..\\Resource\\skybox\\rightsnow1.jpg", L"..\\Resource\\skybox\\topsnow1.jpg");
	skybox->GetTransform()->Translate(D3DXVECTOR3(0.0f, -5000.0f, 0.0f), Space::World);

	box = new DGameObject();
	DMeshRender* meshRender =  (DMeshRender*)box->AddComponent(COMTYPE::DERenderMesh);
	meshRender->CreateMeshTeapot();
	//meshRender->CreateMeshBox(D3DXVECTOR3(1, 1, 1));
	//meshRender->CreateBox();

	
	light = new DLight();

	font = new DFont();
	font->SetText(L"hello world", D3DXCOLOR(255, 0, 0, 255));
	font->GetTransform()->Translate(D3DXVECTOR3(10.0f, 5.0f, 0), Space::World);
	return true;
}


void RenderScene()
{

	camera->Run();
	light->Run();


	camera->BegineShowObject();
	skybox->Run();
	font->Run();
	//box->Run();
	//terrain->Run();

	//MOUSESTATE mouseState;
	//input->GetMouseState();
	//char msgbuf[256];
	//sprintf_s(msgbuf, "mouse Xxxxxxxx is %d\n", mouseState);
	//OutputDebugStringA(msgbuf);
	//char msgbuf[256];
	//sprintf_s(msgbuf, "mouse X is %d, Y is %d, LClick is %d, RClick is %d aaaaaa is %d\n", 
	//	mouseState.lX, mouseState.lY, mouseState.rgbButtons[0], mouseState.rgbButtons[1], mouseState.lZ);
	//OutputDebugStringA(msgbuf;)

	KEYBOARDINFO keyInfo;
	keyInfo.kiKeyboardState = KEYBOARDSTATE::KeyPressing;
	if(input->GetKeyboardState())
	{
		float angle = -5.0f;
		keyInfo.kiKeyboardMap = KEYBOARDMAP::Bk_A;
		if (input->MatchKeyboardState(keyInfo))
		{
			camera->GetTransform()->Rotate(D3DXVECTOR3(angle, 0.0f, 0.0f), Space::Local);
		}
		keyInfo.kiKeyboardMap = KEYBOARDMAP::Bk_D;
		if(input->MatchKeyboardState(keyInfo))
		{
			camera->GetTransform()->Rotate(D3DXVECTOR3(-angle, 0.0f, 0.0f), Space::Local);
		}

		keyInfo.kiKeyboardMap = KEYBOARDMAP::Bk_W;
		if (input->MatchKeyboardState(keyInfo))
		{
			box->GetTransform()->Rotate(D3DXVECTOR3(-angle, 0.0f, 0.0f), Space::Local);
		}
	}


	Sleep(100);


	//terrain->ShowTerrain(TRUE);
	//skybox.ShowSkyBox(FALSE);
	//tp.Show();
	////WCHAR buff[1024] = { 0 };
	////D3DXVECTOR3 vector = camera.GetPosition();
	////swprintf_s(buff, L"camera position x %f  y %f  z %f", vector.x, vector.y, vector.z);
	//font->ShowText(0, 0, D3DXCOLOR(255, 0, 0, 255), buff);


	camera->EndShowObject();
}


void Shutdown()
{
	//camera.DestroyCamera();
	//tp.Destroy();

	DDEInitialize::EndInitD3D();
}


