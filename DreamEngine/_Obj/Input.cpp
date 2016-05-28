#include "Input.h"
#include <stdio.h>
/*
* Input类不完善后期改进
*
*
*/
#define DEVICEPUSH	0x80

DInput::DInput(HINSTANCE hIns, HWND hWnd) :
	m_hIns(hIns), m_hWnd(hWnd), m_input(nullptr), m_mouseDevice(nullptr), m_keyboardDevice(nullptr),
	m_prevMouseState(MOUSESTATE::NonState), m_prevTick(0),
	m_isMouseAction(FALSE),m_isKeyboardAction(FALSE)
{
	ZeroMemory(m_mousePos, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_diMouseState, sizeof(DIMOUSESTATE));
	ZeroMemory(&m_keyStateBuffer, 256);
	ZeroMemory(m_prevKbState, 8 * sizeof(KEYBOARDINFO));
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

BOOL DInput::CreateDevice(INPUTDEVICE inputDevice, DWORD cooperaFlag)
{
	DirectInput8Create(m_hIns, DIRECTINPUT_HEADER_VERSION, IID_IDirectInput8, (VOID**)&m_input, nullptr);
	if (m_input == nullptr)
		return FALSE;

	HRESULT hRes = -1;
	switch (inputDevice)
	{
	case UnkownDevice:
		break;
	case MouseDevice:
		hRes = m_input->CreateDevice(GUID_SysMouse, &m_mouseDevice, nullptr);
		hRes = m_mouseDevice->SetDataFormat(&c_dfDIMouse);
		hRes = m_mouseDevice->SetCooperativeLevel(m_hWnd, cooperaFlag);
		break;
	case KeyboardDevice:
		hRes = m_input->CreateDevice(GUID_SysKeyboard, &m_keyboardDevice, nullptr);
		hRes = m_keyboardDevice->SetDataFormat(&c_dfDIKeyboard);
		hRes = m_keyboardDevice->SetCooperativeLevel(m_hWnd, cooperaFlag);
		break;
	default:
		break;
	}
	m_input->Release();
	m_input = nullptr;
	return !FAILED(hRes);
}



//DoubleClick响应判断不正确，待改
BOOL DInput::GetMouseState()
{

	//OutputDebugStringA("111111111111\n");
	DWORD tInterval = 100;		//间隔100ms
	DWORD curTick = GetTickCount();

	BOOL isAction = TRUE;
	MOUSESTATE tmpMouseState = MOUSESTATE::NonState;
	if (GetDeviceState(INPUTDEVICE::MouseDevice) == TRUE)
	{
		switch (tmpMouseState)
		{
		case NonState:
			if (m_diMouseState.lX == 0 && m_diMouseState.lY == 0 && m_diMouseState.lZ == 0 &&
				*(LONG*)m_diMouseState.rgbButtons == 0 && !(m_prevMouseState & LeftPress) && !(m_prevMouseState & LeftPressing)
				&& !(m_prevMouseState & RightPress) && !(m_prevMouseState & RightPressing))
			{
				break;
			}
		case LeftClick:
			if ((m_prevMouseState & MOUSESTATE::LeftPress) && !(m_diMouseState.rgbButtons[0] & DEVICEPUSH))
			{
				tmpMouseState = (MOUSESTATE)(tmpMouseState | MOUSESTATE::LeftClick);
			}
		case LeftDoubleClick:
			if ((m_prevMouseState & MOUSESTATE::LeftClick) && (m_prevMouseState & MOUSESTATE::LeftPress) && 
				!(m_diMouseState.rgbButtons[0] & DEVICEPUSH))
			{
				tmpMouseState = (MOUSESTATE)(tmpMouseState | MOUSESTATE::LeftDoubleClick);
			}
		case LeftDrag:
			if ((m_diMouseState.lX != 0 || m_diMouseState.lY != 0) && (m_prevMouseState & MOUSESTATE::LeftPressing))
			{
				tmpMouseState = (MOUSESTATE)(tmpMouseState | MOUSESTATE::LeftDrag);
			}
		case LeftPress:
			if ( m_diMouseState.rgbButtons[0] & DEVICEPUSH && !(m_prevMouseState & LeftPress) && !(m_prevMouseState & LeftPressing))
			{
				tmpMouseState = (MOUSESTATE)(tmpMouseState | MOUSESTATE::LeftPress);
				m_prevTick = curTick;
			}
		case LeftPressing:
			if (m_diMouseState.rgbButtons[0] & DEVICEPUSH )
			{
				if( (m_prevMouseState & MOUSESTATE::LeftPress  && ((curTick - m_prevTick) >= tInterval)) ||
					m_prevMouseState & MOUSESTATE::LeftPressing )
					tmpMouseState = (MOUSESTATE)(tmpMouseState | MOUSESTATE::LeftPressing);
			}
		case LeftRelease:
			if  ( !(m_diMouseState.rgbButtons[0] & DEVICEPUSH) && (m_prevMouseState & LeftPress || m_prevMouseState & LeftPressing))
			{
				tmpMouseState = (MOUSESTATE)(tmpMouseState | MOUSESTATE::LeftRelease);
			}
		case RightClick:
			if ((m_prevMouseState & MOUSESTATE::RightPress) && !(m_diMouseState.rgbButtons[1] & DEVICEPUSH))
			{
				tmpMouseState = (MOUSESTATE)(tmpMouseState | MOUSESTATE::RightClick);
			}
		case RightDoubleClick:
			if ((m_prevMouseState & MOUSESTATE::RightClick) && (m_prevMouseState & MOUSESTATE::RightPress) &&
				!(m_diMouseState.rgbButtons[1] & DEVICEPUSH))
			{
				tmpMouseState = (MOUSESTATE)(tmpMouseState | MOUSESTATE::RightDoubleClick);
			}
		case RightDrag:
			if ((m_diMouseState.lX != 0 || m_diMouseState.lY != 0) && (m_prevMouseState & MOUSESTATE::RightPressing))
			{
				tmpMouseState = (MOUSESTATE)(tmpMouseState | MOUSESTATE::RightDrag);
			}
		case RightPress:
			if (m_diMouseState.rgbButtons[1] & DEVICEPUSH && !(m_prevMouseState & RightPress) && !(m_prevMouseState & RightPressing))
			{
				tmpMouseState = (MOUSESTATE)(tmpMouseState | MOUSESTATE::RightPress);
				m_prevTick = curTick;
			}
		case RightPressing:
			if (m_diMouseState.rgbButtons[1] & DEVICEPUSH)
			{
				if ((m_prevMouseState & MOUSESTATE::RightPress && ((curTick - m_prevTick) >= tInterval)) ||
					m_prevMouseState & MOUSESTATE::RightPressing)
					tmpMouseState = (MOUSESTATE)(tmpMouseState | MOUSESTATE::RightPressing);
			}
		case RightRelease:
			if (!(m_diMouseState.rgbButtons[1] & DEVICEPUSH) && (m_prevMouseState & RightPress || m_prevMouseState & RightPressing))
			{
				tmpMouseState = (MOUSESTATE)(tmpMouseState | MOUSESTATE::RightRelease);
			}
		case Move:
			if (m_diMouseState.lX != 0 || m_diMouseState.lY != 0)
			{
				tmpMouseState = (MOUSESTATE)(tmpMouseState | MOUSESTATE::Move);
			}
		case Wheel:
			if (m_diMouseState.lZ != 0)
			{
				tmpMouseState = (MOUSESTATE)(tmpMouseState | MOUSESTATE::Wheel);
			}
		}
	}

	if (tmpMouseState == MOUSESTATE::NonState)
		isAction = FALSE;
	if ((curTick - m_prevTick) < tInterval)
	{
		if (m_prevMouseState & MOUSESTATE::LeftPress)
			tmpMouseState = (MOUSESTATE)(tmpMouseState | MOUSESTATE::LeftPress);
		if(m_prevMouseState & MOUSESTATE::RightPress)
			tmpMouseState = (MOUSESTATE)(tmpMouseState | MOUSESTATE::RightPress);
	}
	//else
	//{
	//	m_prevTick = curTick;
	//}
	m_prevMouseState = tmpMouseState;
	m_isMouseAction = isAction;
	return isAction;
}

BOOL DInput::MatchMouseState(MOUSESTATE mouseState)
{
	if (m_isMouseAction == FALSE )
		return FALSE;
	//DWORD curTick = GetTickCount();
	//if(curTick - m_prevTick > )

	return (BOOL)(m_prevMouseState & mouseState);
}

BOOL DInput::GetKeyboardState()
{
	BOOL isAction = FALSE;
	INT pushCount = 0;
	if (GetDeviceState(INPUTDEVICE::KeyboardDevice) == TRUE)
	{
		KEYBOARDINFO tmpKbState[KBPUSHCOUNT];
		ZeroMemory(tmpKbState, KBPUSHCOUNT * sizeof(KEYBOARDINFO));
		for (INT stateIndex = BkEscapeBk; stateIndex <= BkMediaSelect; stateIndex++)
		{
			if (m_keyStateBuffer[stateIndex] & DEVICEPUSH)
			{
				tmpKbState[pushCount].kiKeyboardMap = (KEYBOARDMAP)stateIndex;
				tmpKbState[pushCount].kiKeyboardState = KEYBOARDSTATE::KeyPress;
				for (INT prevStateIndex = 0; prevStateIndex < KBPUSHCOUNT; prevStateIndex++)
				{
					if (m_prevKbState[prevStateIndex].kiKeyboardMap == stateIndex && 
						m_prevKbState[prevStateIndex].kiKeyboardState != KEYBOARDSTATE::KeyRelease)
					{
						tmpKbState[pushCount].kiKeyboardState = KEYBOARDSTATE::KeyPressing;
						break;
					}
				}
				pushCount++;
				if (pushCount >= KBPUSHCOUNT)
					break;
			}
		}

		for (INT prevStateIndex = 0; prevStateIndex < KBPUSHCOUNT && (pushCount < KBPUSHCOUNT); prevStateIndex++)
		{
			if ( (m_prevKbState[prevStateIndex].kiKeyboardState == KEYBOARDSTATE::KeyPress ||
				m_prevKbState[prevStateIndex].kiKeyboardState == KEYBOARDSTATE::KeyPressing) &&
				!(m_keyStateBuffer[m_prevKbState[prevStateIndex].kiKeyboardMap] & DEVICEPUSH))
			{
				tmpKbState[pushCount].kiKeyboardMap = m_prevKbState[prevStateIndex].kiKeyboardMap;
				tmpKbState[pushCount].kiKeyboardState = KEYBOARDSTATE::KeyRelease;
				pushCount++;
			}
		}		

		if (pushCount > 0)
		{
			memcpy_s(m_prevKbState, KBPUSHCOUNT * sizeof(KEYBOARDINFO), tmpKbState, KBPUSHCOUNT * sizeof(KEYBOARDINFO));
			isAction = TRUE;
			//char msgbuf[512];
			//sprintf_s(msgbuf, "KB0 is %d, STATE is %d, \tKB1 is %d,  STATE is %d\nKB2 is %d,  STATE is %d,\tKB3 is %d,  STATE is %d\nKB4 is %d,  STATE is %d\n\n\n", 
			//	m_prevKbState[0].kiKeyboardMap, m_prevKbState[0].kiKeyboardState, 
			//	m_prevKbState[1].kiKeyboardMap, m_prevKbState[1].kiKeyboardState,
			//	m_prevKbState[2].kiKeyboardMap, m_prevKbState[2].kiKeyboardState,
			//	m_prevKbState[3].kiKeyboardMap, m_prevKbState[3].kiKeyboardState,
			//	m_prevKbState[4].kiKeyboardMap, m_prevKbState[4].kiKeyboardState);
			//OutputDebugStringA(msgbuf);
		}
	}
	return isAction;
}

BOOL DInput::MatchKeyboardState(KEYBOARDINFO keyboardInfo)
{
	BOOL isMatch = FALSE;
	for (INT prevStateIndex = 0; prevStateIndex < KBPUSHCOUNT; prevStateIndex++)
	{
		if ((m_prevKbState[prevStateIndex].kiKeyboardMap == keyboardInfo.kiKeyboardMap) &&
			(m_prevKbState[prevStateIndex].kiKeyboardState == keyboardInfo.kiKeyboardState))
			isMatch = TRUE;
	}
	return isMatch;
}

VOID DInput::GetMousePos(D3DXVECTOR2 * pMousePosOut)
{
	if (pMousePosOut == nullptr)
		return;
	POINT mousePos;
	::GetCursorPos(&mousePos);
	::ScreenToClient(m_hWnd, &mousePos);
	//pMousePosOut->x = m_diMouseState.lX;
	//pMousePosOut->y = m_diMouseState.lY;
	//pMousePosOut->z = m_diMouseState.lZ;	
	pMousePosOut->x = mousePos.x;
	pMousePosOut->y = mousePos.y;
}

VOID DInput::GetRltMousePos(D3DXVECTOR3 * pRltMousePosOut)
{
	if (pRltMousePosOut == nullptr)
		return;

	pRltMousePosOut->x = m_diMouseState.lX;
	pRltMousePosOut->y = m_diMouseState.lY;
	pRltMousePosOut->z = m_diMouseState.lZ;
}

BOOL DInput::GetDeviceState(INPUTDEVICE queryDevice)
{
	HRESULT hr = -1;
	switch (queryDevice)
	{
	case UnkownDevice:
		break;
	case MouseDevice:
		if (FAILED(m_mouseDevice->Acquire()))	return FALSE;
		if (FAILED(m_mouseDevice->Poll()))	return FALSE;
		hr = m_mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_diMouseState);
		break;
	case KeyboardDevice:	
		if (FAILED(m_keyboardDevice->Acquire()))	return FALSE;
		if (FAILED(m_keyboardDevice->Poll()))	return FALSE;
		hr = m_keyboardDevice->GetDeviceState(256, &m_keyStateBuffer);
		break;
	default:
		break;
	}
	return SUCCEEDED(hr);
}
