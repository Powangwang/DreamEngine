#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include <string>
#include <vector>
using namespace std;

class DGameObject;
enum  COMTYPE
{
	DERenderUnkown,
	DERenderTransform,
	DERenderMesh,
	DERenderMaterial,
	DEAnimator
};



class DBaseCom
{
public:
	DBaseCom(wstring comName, COMTYPE type, DGameObject* gameObj, DWORD indexInParent);
	~DBaseCom();
	VOID SetEnabled(BOOL isEnabled) { m_isEnabled = isEnabled; }
	BOOL GetEnabled() { return m_isEnabled; }
	//GetParent();
public:
	virtual VOID Run() = 0;
	COMTYPE GetComponentType();

protected:
	wstring m_comName;
	COMTYPE m_comType;
	DGameObject* m_gameObj;
	DWORD m_indexInParent;
	BOOL m_isEnabled;
};