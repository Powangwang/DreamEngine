#pragma once
#include <Windows.h>
#include <string>
using namespace std;

class DString
{
public:
	DString();
	~DString();
	BOOL SetData(LPCWSTR data);
	BOOL GetData(LPCWSTR* data);
public:
	static BOOL GetFilePath(LPCWSTR pFileName, LPWSTR* pFilePathOut);
	static BOOL GetFilePath(LPCWSTR pFileName, wstring* pDStr);
	static BOOL Ansi2WChar(string* src, wstring* des);
private:
	wstring m_string;
};