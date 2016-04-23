#include "Input.h"

DInput::DInput(HINSTANCE hIns, HWND hWnd):
	m_hIns(hIns), m_hWnd(hWnd), m_input(nullptr), m_mouseDevice(nullptr), m_keyboardDevice(nullptr)
{
	ZeroMemory(&m_diMouseState, sizeof(DIMOUSESTATE));
	ZeroMemory(&m_pKeyStateBuffer, 256);
}

DInput::~DInput()
{
	if (m_input != nullptr)
		m_input->Release();
	if(m_mouseDevice != nullptr)
		m_mouseDevice->Release();
	if(m_keyboardDevice != nullptr)
		m_keyboardDevice->Release();
}

BOOL DInput::CreateDevice(INPUTDEVICE inputDevice, COOPERALEVEL cooperaFlag)
{
	DirectInput8Create(m_hIns, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_input, NULL);
	if (m_input == nullptr)
		return FALSE;

	HRESULT hRes = -1;
	switch (inputDevice)
	{
	case UnkownDevice:
		break;
	case MouseDevice:
		hRes = m_input->CreateDevice(GUID_SysMouse, &m_mouseDevice, NULL);
		hRes = m_mouseDevice->SetDataFormat(&c_dfDIMouse);
		hRes = m_mouseDevice->SetCooperativeLevel(m_hWnd, cooperaFlag);
		break;
	case KeyboardDevice:
		hRes = m_input->CreateDevice(GUID_SysKeyboard, &m_keyboardDevice, NULL);
		hRes = m_keyboardDevice->SetDataFormat(&c_dfDIKeyboard);
		hRes = m_keyboardDevice->SetCooperativeLevel(m_hWnd, cooperaFlag);
		m_keyboardDevice->Poll();
		break;
	default:
		break;
	}
	m_input->Release();
	m_input = nullptr;
	return !FAILED(hRes);
}
