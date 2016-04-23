#pragma once
#include "CommRenderHead.h"
#include "MaterialRender.h"

//class DMateriaRender;
//#include "BaseCom.h"
class DMeshRender : public DBaseCom
{
public:
	DMeshRender(DGameObject* gameObj, DWORD indexInParent);
	~DMeshRender();
	BOOL CreateMeshBox(D3DXVECTOR3 size);
	BOOL CreateMeshSphere(FLOAT radius);
	BOOL CreateMeshTeapot();
	VOID Run();
public:
	DMateriaRender* GetMaterialRender() { return m_pMatRender; }
private:
	LPD3DXMESH m_pMess;
	DMateriaRender* m_pMatRender;
	//BOOL m_isDraw;
};