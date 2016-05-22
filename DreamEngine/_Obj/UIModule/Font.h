#pragma once
#include "GameObject.h"

class DFont : public DGameObject
{
public:
	DFont();
	~DFont();
	VOID SetText(WCHAR* textBuff, D3DXCOLOR textColor);
	VOID Run();
private:
	BOOL InitDxFont(INT Height, UINT Width, UINT Weight, UINT MipLevels,
		BOOL Italic, DWORD CharSet, DWORD OutputPrecision, DWORD Quality, DWORD PitchAndFamily, LPCTSTR pFacename);
	BOOL ShowText();
private:
	TCHAR* m_textBuff;
	D3DXCOLOR m_textColor;
	LPD3DXFONT m_dxFont;				
};