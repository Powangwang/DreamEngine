#include "Font.h"

#include <tchar.h>
DFont::DFont()
{
	WCHAR fontName[] = L"Times New Roman";
	BOOL ret = FALSE;
	ret = InitDxFont(20, 0, 0, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, fontName);

	if (ret == FALSE)
	{
		m_dxFont = nullptr;
		m_isEnabled = FALSE;	
	}
}

DFont::~DFont()
{
	if (m_dxFont != nullptr)
		m_dxFont->Release();
}

VOID DFont::SetText(WCHAR * textBuff, D3DXCOLOR textColor)
{
	m_textColor = textColor;
	int length = wcslen(textBuff) + 1;

	m_textBuff = new WCHAR[length];
	_tcsncpy_s(m_textBuff, length, textBuff, length);
}

VOID DFont::Run()
{
	if (!m_isEnabled)
		return;

	ShowText();
}


BOOL DFont::InitDxFont(INT Height, UINT Width, UINT Weight, UINT MipLevels,
	BOOL Italic, DWORD CharSet, DWORD OutputPrecision, DWORD Quality, DWORD PitchAndFamily, LPCTSTR pFacename)
{
	HRESULT hr = -1;
	hr = D3DXCreateFont(DDEInitialize::gRootDevice, Height, Width, Weight, MipLevels,
		Italic, CharSet, OutputPrecision, Quality, PitchAndFamily, pFacename, &m_dxFont);

	return SUCCEEDED(hr);
}

BOOL DFont::ShowText()
{
	HRESULT hr = -1;
	if (m_dxFont == nullptr)
		return FALSE;

	RECT textRect = { 0 };
	D3DXVECTOR3 textPos;
	GetTransform()->GetPosition(&textPos, Space::Local);
	textRect.left = (LONG)textPos.x;
	textRect.top = (LONG)textPos.y;

	INT retUnit = 0;
	retUnit = m_dxFont->DrawTextW(NULL, m_textBuff, -1, &textRect, DT_NOCLIP | DT_LEFT, m_textColor);

	if(retUnit > 0)
		return TRUE;

	return FALSE;
}
