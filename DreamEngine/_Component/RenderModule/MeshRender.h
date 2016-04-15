#pragma once
#include "CommRenderHead.h"
//#include "BaseCom.h"
class DMeshRender : public DBaseCom
{
public:
	DMeshRender(DGameObject* gameObj);
	~DMeshRender();
	BOOL CreateMeshBox(D3DXVECTOR3 size);
	VOID Run();

public :
	VOID SetDrawEnabled(BOOL isEnable) { m_isDraw = isEnable; }
private:
	LPD3DXMESH m_pMess;
	BOOL m_isDraw;
};