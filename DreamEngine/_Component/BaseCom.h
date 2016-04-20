#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include <string>
//#include "CommRenderHead.h"
//#include "../_Obj/GameObject.h"
using namespace std;

class DGameObject;
enum  COMTYPE
{
	Unkown,
	DERenderTransform,
	DERenderMesh,
	DERenderMaterial
};
class DBaseCom
{
public:
	DBaseCom(wstring comName, COMTYPE type, DGameObject* gameObj);
	~DBaseCom();
	//GetParent();
public:
	virtual VOID Run() = 0;
	COMTYPE GetComponentType();

protected:
	LPDIRECT3DDEVICE9 m_d3dDivce;
	wstring m_comName;
	COMTYPE m_comType;
	DGameObject* m_gameObj;

};