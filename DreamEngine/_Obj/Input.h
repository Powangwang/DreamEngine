#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include <Windows.h>
#include <dinput.h>

#define KBPUSHCOUNT		8		//同时响应键盘按下最大数
enum COOPERALEVEL
{
	Exclusive = 0x000001,
	NonExclusive = 0x000002,
	BackGround = 0x000008,
	ForeGround = 0x000004,
	NoWinKey = 0x000010	
};
enum INPUTDEVICE
{
	UnkownDevice,
	MouseDevice,
	KeyboardDevice
};
#pragma region DefineKeyboard
enum KEYBOARDMAP
{	
	BkNonState = 0x00,
	BkEscapeBk = DIK_ESCAPE,
	Bk_1 = DIK_1,
	Bk_2 = DIK_2,
	Bk_3 = DIK_3,
	Bk_4 = DIK_4,
	Bk_5 = DIK_5,
	Bk_6 = DIK_6,
	Bk_7 = DIK_7,
	Bk_8 = DIK_8,
	Bk_9 = DIK_9,
	Bk_0 = DIK_0,
	BkMinus = DIK_MINUS,
	BkEquals = DIK_EQUALS,
	BkBack = DIK_BACK,
	BkTab = DIK_TAB,
	Bk_Q = DIK_Q,
	Bk_W = DIK_W,
	Bk_E = DIK_E,
	Bk_R = DIK_R,
	Bk_T = DIK_T,
	Bk_Y = DIK_Y,
	Bk_U = DIK_U,
	Bk_I = DIK_I,
	Bk_O = DIK_O,
	Bk_P = DIK_P,
	BkLBracket = DIK_LBRACKET,
	BkRBracket = DIK_RBRACKET,
	BkReturn = DIK_RETURN,
	BkLControl = DIK_LCONTROL,
	Bk_A = DIK_A,
	Bk_S = DIK_S,
	Bk_D = DIK_D,
	Bk_F = DIK_F,
	Bk_G = DIK_G,
	Bk_H = DIK_H,
	Bk_J = DIK_J,
	Bk_K = DIK_K,
	Bk_L = DIK_L,
	BkSemicolon = DIK_SEMICOLON,
	BkApostrophe = DIK_APOSTROPHE,
	BkGrave = DIK_GRAVE,
	BkLShift = DIK_LSHIFT,
	BkBackslash = DIK_BACKSLASH,
	Bk_Z = DIK_Z,
	Bk_X = DIK_X,
	Bk_C = DIK_C,
	Bk_V = DIK_V,
	Bk_B = DIK_B,
	Bk_N = DIK_N,
	Bk_M = DIK_M,
	BkCommA = DIK_COMMA,
	BkPeriod = DIK_PERIOD,
	BkSlash = DIK_SLASH,
	BkRShift = DIK_RSHIFT,
	BkMultiply = DIK_MULTIPLY,
	BkLMenu = DIK_LMENU,
	BkSpace = DIK_SPACE,
	BkCapital = DIK_CAPITAL,
	Bk_F1 = DIK_F1,
	Bk_F2= DIK_F2,
	Bk_F3 = DIK_F3,
	Bk_F4 = DIK_F4,
	Bk_F5 = DIK_F5,
	Bk_F6 = DIK_F6,
	Bk_F7 = DIK_F7,
	Bk_F8 = DIK_F8,
	Bk_F9 = DIK_F9,
	Bk_F10 = DIK_F10,
	BkNumLock = DIK_NUMLOCK,
	BkScroll = DIK_SCROLL,
	BkNumpad7 = DIK_NUMPAD7,
	BkNumpad8 = DIK_NUMPAD8,
	BkNumpad9 = DIK_NUMPAD9,
	Bk_Subtract= DIK_SUBTRACT,
	BkNumpad4 = DIK_NUMPAD4,
	BkNumpad5 = DIK_NUMPAD5,
	BkNumpad6 = DIK_NUMPAD6,
	BkAdd = DIK_ADD,
	BkNumpad1 = DIK_NUMPAD1,
	BkNumpad2 = DIK_NUMPAD2,
	BkNumpad3 = DIK_NUMPAD3,
	BkNumpad0 = DIK_NUMPAD0,
	BkDecimal = DIK_DECIMAL,
	BkOEM102 = DIK_OEM_102,
	Bk_F11 = DIK_F11,
	Bk_F12 = DIK_F12,
	Bk_F13 = DIK_F13,
	Bk_F14 = DIK_F14,
	Bk_F15 = DIK_F15,
	BkKana = DIK_KANA,
	BkAbntC1 = DIK_ABNT_C1,
	BkConvert = DIK_CONVERT,
	BkNonconvert = DIK_NOCONVERT,
	BkYen = DIK_YEN,
	BkAbntC2 = DIK_ABNT_C2,
	BkNumpadEquals = DIK_NUMPADEQUALS,
	BkPrevtrack = DIK_PREVTRACK,
	BkAt = DIK_AT,
	BkColon = DIK_COLON,
	BkUnderline = DIK_UNDERLINE,
	BkKanji = DIK_KANJI,
	BkStop = DIK_STOP,
	BkAx = DIK_AX,
	BkUnlabeled = DIK_UNLABELED,
	BkNexttrack = DIK_NEXTTRACK,
	BkNumpadEnter = DIK_NUMPADENTER,
	BkRControl = DIK_RCONTROL,
	BkMute = DIK_MUTE,
	BkCalculator = DIK_CALCULATOR,
	BkPlayPause = DIK_PLAYPAUSE,
	BkMediaStop = DIK_MEDIASTOP,
	BkVolumeDown = DIK_VOLUMEDOWN,
	BkVolumeUp = DIK_VOLUMEUP,
	BkWebHome = DIK_WEBHOME,
	BkNumpadComma = DIK_NUMPADCOMMA,
	BkDivide = DIK_DIVIDE,
	BkSysRQ = DIK_SYSRQ,
	BkRMenu = DIK_RMENU,
	BkPause = DIK_PAUSE,
	BkHome = DIK_HOME,
	BkUp = DIK_UP,
	BkPrior = DIK_PRIOR,
	BkLeft = DIK_LEFT,
	BkRight = DIK_RIGHT,
	BkEnd = DIK_END,
	BkDown = DIK_DOWN,
	BkNext = DIK_NEXT,
	BkInsert = DIK_INSERT,
	BkDelete = DIK_DELETE,
	BkLWin = DIK_LWIN,
	BkRWin = DIK_RWIN,
	BkApps = DIK_APPS,
	BkPower = DIK_POWER,
	BkSleep = DIK_SLEEP,
	BkWake = DIK_WAKE,
	BkWebSearch = DIK_WEBSEARCH,
	BkWebFavorites = DIK_WEBFAVORITES,
	BkWebRefresh = DIK_WEBREFRESH,
	BkWebStop = DIK_WEBSTOP,
	BkWebForward = DIK_WEBFORWARD,
	BkWebBack = DIK_WEBBACK,
	BkMycomputer = DIK_MYCOMPUTER,
	BkMail = DIK_MAIL,
	BkMediaSelect = DIK_MEDIASELECT
};
enum KEYBOARDSTATE
{
	KeyNonState,
	KeyPress,
	KeyPressing,
	KeyRelease
};
typedef struct _KEYBOARDINFO
{
	KEYBOARDMAP kiKeyboardMap;
	KEYBOARDSTATE kiKeyboardState;
}KEYBOARDINFO, *pKEYBOARDINFO;
#pragma endregion

#pragma region DefineMouse
enum MOUSESTATE
{
	NonState = 0x0000,
	LeftClick = 0x0001,
	LeftDoubleClick = 0x0002,
	LeftDrag = 0x0004,
	LeftPress = 0x0008,
	LeftPressing = 0x0010,
	LeftRelease = 0x0020,

	RightClick = 0x0040,
	RightDoubleClick = 0x0080,
	RightDrag = 0x0100,
	RightPress = 0x0200,
	RightPressing = 0x0400,
	RightRelease = 0x0800,

	Move = 0x1000,
	Wheel = 0x2000
};
#pragma endregion
class DInput
{
public:
	DInput(HINSTANCE hIns, HWND hWnd);
	~DInput();
	BOOL CreateDevice(INPUTDEVICE inputDevice, DWORD cooperaFlag);

	BOOL GetMouseState();
	BOOL MatchMouseState(MOUSESTATE  mouseState);

	BOOL GetKeyboardState();
	BOOL MatchKeyboardState(KEYBOARDINFO keyboardInfo);

private:
	BOOL GetDeviceState(INPUTDEVICE queryDevice);
private:
	HINSTANCE m_hIns;
	HWND m_hWnd;
	LPDIRECTINPUT8	m_input; 
	LPDIRECTINPUTDEVICE8 m_mouseDevice;
	LPDIRECTINPUTDEVICE8 m_keyboardDevice;

	DIMOUSESTATE m_diMouseState;
	CHAR m_keyStateBuffer[256];

	D3DXVECTOR3 m_mousePos;
	MOUSESTATE m_prevMouseState;
	KEYBOARDINFO m_prevKbState[KBPUSHCOUNT];

	BOOL m_isMouseAction;
	BOOL m_isKeyboardAction;
};