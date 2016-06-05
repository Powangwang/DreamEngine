#include "DEngine.h"
#include <math.h>
#define WINDOW_CLASS    L"UGPDX"
#define WINDOW_NAME     L"DREAM ENGINE"
#define WINDOW_WIDTH    1024
#define WINDOW_HEIGHT   768

// Function Prototypes...
bool InitializeD3D(HINSTANCE hInst, HWND hWnd, bool fullscreen);
bool InitializeObjects();
void RenderScene();
void Shutdown();
void InputCotrol();


//Teapot tp;
DSky* skybox;
DTerrain* terrain;
DCamera* camera;
DLight* light;
DGameObject* gameObject;
DInput* input;
DFont * font;

DRay * ray;
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
	input->CreateDevice(INPUTDEVICE::KeyboardDevice, COOPERALEVEL::BackGround | COOPERALEVEL::Exclusive);

	return true;
}

bool InitializeObjects()
{
	camera = new DCamera();
	camera->SetCameraZf(300000.0f);
	//camera->GetTransform()->Translate(D3DXVECTOR3(0.0f, 300.0f, -15.0f), Space::World);
	camera->GetTransform()->Translate(D3DXVECTOR3(0.0f, 300.0f, -600.0f), Space::World);

	terrain = new DTerrain(256, 256, 20, 2);
	terrain->CreateTerrain(L"..\\Resource\\coastMountainEx.raw", L"..\\Resource\\terrainstone.jpg");	
	//terrain = new DTerrain(64, 64, 10, 2);
	//terrain->CreateTerrain(L"..\\Resource\\coastMountain64.raw");

	wstring skyPath = L"..\\Resource\\skybox\\Sun\\";
	//LPCWSTR pp = skyPath.data();
	skybox = new DSky(10000.0f);
	skybox->CreateSkybox( (skyPath + wstring(L"Front.png")).data(), (skyPath + wstring(L"Back.png")).data(),
		(skyPath + wstring(L"Left.png")).data(), (skyPath + wstring(L"Right.png")).data(), (skyPath + wstring(L"Top.png")).data());
	skybox->GetTransform()->Translate(D3DXVECTOR3(0.0f, -5000.0f, 0.0f), Space::World);

	gameObject = new DGameObject();
	gameObject->GetTransform()->Translate(D3DXVECTOR3(0.0f, 280.0f, -560.0f), Space::World);
	//DMeshRender* meshRender =  (DMeshRender*)gameObject->AddComponent(COMTYPE::DERenderMesh);
	//meshRender->CreateMeshFromFileX(L"..\\Resource\\MeshFile\\King\\knight.X", D3DXMESH_MANAGED);
	DAnimator* animator = (DAnimator*)gameObject->AddComponent(COMTYPE::DEAnimator);
	animator->LoadAnimatorFromXFile(L"..\\Resource\\MeshFile\\lxq\\lxq.X", D3DXMESH_MANAGED);
	//animator->LoadAnimatorFromXFile(L"..\\Resource\\MeshFile\\King\\knight.X", D3DXMESH_MANAGED);

	//meshRender->CreateMeshTeapot();
	//meshRender->CreateMeshBox(D3DXVECTOR3(1, 1, 1));
	//meshRender->CreateBox();

	
	light = new DLight();

	font = new DFont();


	font->SetText(L"hello world", D3DXCOLOR(0, 0, 0, 255));
	font->GetTransform()->Translate(D3DXVECTOR3(10.0f, 5.0f, 0), Space::World);
	return true;
}


void RenderScene()
{

	camera->Run();
	light->Run();

	camera->BegineShowObject();
	skybox->Run();
	gameObject->Run();
	font->Run();
	terrain->Run();
	camera->EndShowObject();

	//Sleep(100);
	InputCotrol();
}


void Shutdown()
{
	//camera.DestroyCamera();
	//tp.Destroy();

	DDEInitialize::EndInitD3D();
}

void InputCotrol()
{
	if (input->GetMouseState())
	{
		//MOUSESTATE mouseState;
		//mouseState = MOUSESTATE::LeftClick;

		WCHAR msgbuf[256];
		D3DXVECTOR3 mousePos;
		//sprintf_s(msgbuf, "mouse Xxxxxxxx is %d\n", mouseState);
		if (input->MatchMouseState(MOUSESTATE::LeftClick))
		{
			D3DXVECTOR2 pos;
			input->GetMousePos(&pos);
			//swprintf_s(msgbuf, L"mouse clicked");
			//font->SetText(msgbuf, D3DXCOLOR(255, 255, 255, 255));
			//pos.x = mousePos.x;
			//pos.y = mousePos.y;
			ray = camera->ViewportPointToRay(pos);
			if (ray != nullptr)
			{
				if (ray->RayHit(gameObject))
					font->SetText(L"hit", D3DXCOLOR(255, 255, 255, 255));
				else
					font->SetText(L"not hit", D3DXCOLOR(255, 255, 255, 255));
			}
		}
		else if (input->MatchMouseState((MOUSESTATE)(MOUSESTATE::LeftDrag | MOUSESTATE::Wheel)))
		{
			input->GetRltMousePos(&mousePos);
			mousePos.x = -mousePos.x;
			DTransform* cameraTrans = camera->GetTransform();
			cameraTrans->Translate(mousePos, Space::Local);

			D3DXVECTOR3 cameraPos;
			cameraTrans->GetPosition(&cameraPos, Space::Local);
			swprintf_s(msgbuf, L"camera pos is %f  %f  %f \n", cameraPos.x, cameraPos.y, cameraPos.z);
			font->SetText(msgbuf, D3DXCOLOR(255, 255, 255, 255));
		}
		else if (input->MatchMouseState(MOUSESTATE::RightDrag))
		{
			input->GetRltMousePos(&mousePos);
			D3DXVECTOR3 cameraRotate;
			
			if(abs(mousePos.x) - abs(mousePos.y) > 0)
				mousePos.y = 0;
			if(abs(mousePos.y) - abs(mousePos.x) > 0)
				mousePos.x = 0;

			cameraRotate.x = mousePos.y;
			cameraRotate.y = mousePos.x;
			cameraRotate.z = 0;
			cameraRotate *= D3DX_PI * 0.1f;
			camera->GetTransform()->Rotate(cameraRotate, Space::Local);
		}



	}


	KEYBOARDINFO keyInfo;
	keyInfo.kiKeyboardState = KEYBOARDSTATE::KeyPressing;
	if (input->GetKeyboardState())
	{
		float angle = 5.0f;
		keyInfo.kiKeyboardMap = KEYBOARDMAP::Bk_W;
		if (input->MatchKeyboardState(keyInfo))
		{
			gameObject->GetTransform()->Translate(D3DXVECTOR3(0.0f, angle, 0.0f), Space::World);
		}
		keyInfo.kiKeyboardMap = KEYBOARDMAP::Bk_S;
		if (input->MatchKeyboardState(keyInfo))
		{
			gameObject->GetTransform()->Translate(D3DXVECTOR3(0.0f, -angle, 0.0f), Space::World);
		}

		keyInfo.kiKeyboardMap = KEYBOARDMAP::Bk_A;
		if (input->MatchKeyboardState(keyInfo))
		{
			gameObject->GetTransform()->Translate(D3DXVECTOR3(-angle, 0.0f, 0.0f), Space::World);
		}
		keyInfo.kiKeyboardMap = KEYBOARDMAP::Bk_D;
		if (input->MatchKeyboardState(keyInfo))
		{
			gameObject->GetTransform()->Translate(D3DXVECTOR3(angle, 0.0f, 0.0f), Space::World);
		}
		keyInfo.kiKeyboardMap = KEYBOARDMAP::Bk_Z;
		if (input->MatchKeyboardState(keyInfo))
		{
			gameObject->GetTransform()->Translate(D3DXVECTOR3(0.0f, 0.0f, -angle * 0.1f ), Space::World);
		}
		keyInfo.kiKeyboardMap = KEYBOARDMAP::Bk_C;
		if (input->MatchKeyboardState(keyInfo))
		{
			gameObject->GetTransform()->Translate(D3DXVECTOR3(0.0f, 0.0f,angle * 0.1f), Space::World);
		}
		keyInfo.kiKeyboardMap = KEYBOARDMAP::Bk_Q;
		if (input->MatchKeyboardState(keyInfo))
		{
			gameObject->GetTransform()->Rotate(D3DXVECTOR3(0.0f, angle, 0.0f), Space::Local);
		}
		keyInfo.kiKeyboardMap = KEYBOARDMAP::Bk_E;
		if (input->MatchKeyboardState(keyInfo))
		{
			gameObject->GetTransform()->Rotate(D3DXVECTOR3(0.0f, -angle, 0.0f), Space::Local);
		}
	}
}


