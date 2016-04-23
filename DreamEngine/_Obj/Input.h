#pragma once
#include <dinput.h>

enum COOPERALEVEL
{
	Exclusive = 0x00000001,
	NonExclusive = 0x00000002,
	BackGround = 0x00000008,
	ForeGround = 0x00000004,
	NoWinKey = 0x00000010
};
enum INPUTDEVICE
{
	UnkownDevice,
	MouseDevice,
	KeyboardDevice
};
class DInput
{
public:
	DInput(HINSTANCE hIns, HWND hWnd);
	~DInput();
	BOOL CreateDevice(INPUTDEVICE inputDevice, COOPERALEVEL cooperaFlag);



private:
	HINSTANCE m_hIns;
	HWND m_hWnd;
	LPDIRECTINPUT8	m_input; 
	LPDIRECTINPUTDEVICE8 m_mouseDevice;
	LPDIRECTINPUTDEVICE8 m_keyboardDevice;

	DIMOUSESTATE m_diMouseState;
	CHAR m_pKeyStateBuffer[256];
};