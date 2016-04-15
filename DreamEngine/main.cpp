#include "_CommAction\DEInitialize.h"
#include "_Obj\Camera.h"

#define WINDOW_CLASS    L"UGPDX"
#define WINDOW_NAME     L"DREAM ENGINE"
#define WINDOW_WIDTH    1024
#define WINDOW_HEIGHT   768

// Function Prototypes...
bool InitializeD3D(HWND hWnd, bool fullscreen);
bool InitializeObjects();
void RenderScene();
void Shutdown();

//Teapot tp;
Camera* camera;
DGameObject* box;

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
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		WINDOW_CLASS, NULL };
	RegisterClassEx(&wc);

	// Create the application's window
	HWND hWnd = CreateWindow(WINDOW_CLASS, WINDOW_NAME, WS_OVERLAPPEDWINDOW,
		100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,
		GetDesktopWindow(), NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	if (InitializeD3D(hWnd, false))
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
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
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


bool InitializeD3D(HWND hWnd, bool fullscreen)
{
	if (!DDEInitialize::InitializeD3D(hWnd, fullscreen, WINDOW_WIDTH, WINDOW_HEIGHT))
		return false;
	if (!InitializeObjects()) 
		return false;

	//D3DXVECTOR3 pos;
	//pos.x = 1.11;
	//pos.y = 2.22;
	//pos.z = 3.33;
	//D3DXVECTOR3 rotation;
	//rotation.x = D3DX_PI/2;
	//rotation.y = D3DX_PI / 4;
	//rotation.z = D3DX_PI / 3;
	//D3DXVECTOR3 scale;
	//scale.x = 1.11;
	//scale.y = 2.22;
	//scale.z = 3.33;

	//D3DXMATRIX matrix;
	//D3DXMATRIX m_transMatrix;
	//D3DXMatrixIdentity(&m_transMatrix);
	////D3DXMatrixTranslation(&matrix, pos.x, pos.y, pos.y);
	////m_transMatrix *= matrix;

	//D3DXMatrixRotationX(&matrix, rotation.x);
	//m_transMatrix *= matrix;
	//D3DXMatrixRotationY(&matrix, rotation.y);
	//m_transMatrix *= matrix;
	//D3DXMatrixRotationZ(&matrix, rotation.z);
	//m_transMatrix *= matrix;

	//D3DXMatrixScaling(&matrix, scale.x, scale.y, scale.z);
	//m_transMatrix *= matrix;

	//D3DXMATRIX mat1;
	//D3DXMatrixIdentity(&mat1);

	//D3DXMATRIX mat;
	//D3DXMatrixIdentity(&mat);
	//mat._11 = 5;
	//mat._22 = 2;
	//mat._33 = 4;
	//mat = mat1 -mat;
	return true;
}

bool InitializeObjects()
{
	camera = new Camera();
	//camera->CreateCamera(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
	////	camera.Move(-5.0f, -0.3f, -0.0f);
	////camera.SetPosition(0, 0, -0);
	//camera.SetPosition(DIRECT_FRONT, 80);
	//camera.SetPosition(DIRECT_UP, 500);
	//camera.Rotation(DIRECT_RIGHT, D3DX_PI / 2);
	camera->SetCameraZf(300000.0f);
	//camera->OpenCamera();
	
	box = new DGameObject();
	DMeshRender* meshRender =  (DMeshRender*)box->AddComponent(COMTYPE::DERenderMesh);
	if (meshRender != nullptr)
		meshRender->CreateMeshBox(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	//tp.Create();
	////tp.Rotation(DIRECT_RIGHT, 0.0f);


	//light.CreateLight(D3DLIGHT_DIRECTIONAL);
	//light.OpenLight();

	//terrain = new DTerrain(64, 64, 10, 2);
	//terrain->InitTerrain(L"coastMountain64.raw");


	////	terrain->SetTerrainColor(new D3DXVECTOR3(0, 1, 0));
	//ZeroMemory(&mat, sizeof(D3DMATERIAL9));
	//mat.Ambient = RED;
	//mat.Diffuse = RED;
	//mat.Specular = RED;
	//mat.Emissive = BLACK;
	//DGameObject::GetDevice()->SetMaterial(&mat);

	//skybox.CreateSkyBox(20000);
	//skybox.OpenSkyBox(L"frontsnow1.jpg", L"backsnow1.jpg", L"leftsnow1.jpg", L"rightsnow1.jpg", L"topsnow1.jpg");


	//font = new DFont();
	//font->CreateRenderFont();
	return true;
}


void RenderScene()
{
	camera->BegineShowObject();
	box->Run();
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
