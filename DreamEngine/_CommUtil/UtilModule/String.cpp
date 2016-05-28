#include"String.h"

DString::DString()
{

}

DString::~DString()
{
}

BOOL DString::SetData(LPCWSTR data)
{
	m_string = data;
	return 0;
}

BOOL DString::GetData(LPCWSTR * data)
{
	if (data == nullptr)
		return FALSE;

	*data = m_string.data();
	return 0;
}

BOOL DString::GetFilePath(LPCWSTR pFileName, LPWSTR* pFilePathOut)
{

	wstring fileName = pFileName;
	if (fileName.find(L'.') < 0)
	{
		*pFilePathOut = nullptr;
		return FALSE;
	}
	int pathCount = fileName.rfind(L"\\", fileName.size());
	fileName = fileName.substr(0, pathCount + 1);
	pathCount = fileName.size();
	*pFilePathOut = new WCHAR[pathCount + 1];
	const WCHAR * data = fileName.data();
	memcpy_s(*pFilePathOut, pathCount * sizeof(WCHAR), data, pathCount * sizeof(WCHAR));
	*pFilePathOut[pathCount] = L'\0';
	return TRUE;
}
BOOL DString::GetFilePath(LPCWSTR pFileName, wstring* pStr)
{
	wstring fileName = pFileName;
	if (pStr == nullptr || fileName.find(L'.') < 0)
	{
		return FALSE;
	}

	int pathCount = fileName.rfind(L"\\", fileName.size());
	fileName = fileName.substr(0, pathCount + 1);
	*pStr = fileName.data();

}

BOOL DString::Ansi2WChar(string * src, wstring * des)
{
	if (src == nullptr || des == nullptr)
		return FALSE;

	LPCSTR strSrc = src->data();
	int srcLen = src->size();
	WCHAR * strDes = new WCHAR[srcLen + 1];
	int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strSrc, srcLen, strDes, srcLen);
	if (nSize != srcLen) 
		return FALSE;
	strDes[srcLen] = L'\0';
	*des = strDes;
	delete strDes;
	return TRUE;
}
