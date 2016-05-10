#pragma once
#include "CommRenderHead.h"
#include "MaterialRender.h"
#include <vector>

enum MESHOPTION
{
	MeshOpt32Bit= D3DXMESH_32BIT ,
	MeshOptDonotClip = D3DXMESH_DONOTCLIP,
	MeshOptPoints = D3DXMESH_POINTS ,
	MeshOptRTPatches = D3DXMESH_RTPATCHES ,
	MeshOptNPatches = D3DXMESH_NPATCHES ,
	MeshOptVbSystemmem = D3DXMESH_VB_SYSTEMMEM ,
	MeshOptVbManaged = D3DXMESH_VB_MANAGED ,
	MeshOptVbWriteOnly = D3DXMESH_VB_WRITEONLY ,
	MeshOptVbDynamic = D3DXMESH_VB_DYNAMIC ,
	MeshOptVbSoftwareProcessing = D3DXMESH_VB_SOFTWAREPROCESSING ,
	MeshOptSysIbtemmem = D3DXMESH_IB_SYSTEMMEM ,
	MeshOptIbManaged = D3DXMESH_IB_MANAGED ,
	MeshOptIbWriteOnly = D3DXMESH_IB_WRITEONLY ,
	MeshOptIbDynamic = D3DXMESH_IB_DYNAMIC ,
	MeshOptIbSoftwareProcessing = D3DXMESH_IB_SOFTWAREPROCESSING ,
	MeshOptVbShare = D3DXMESH_VB_SHARE ,
	MeshOptUseHWOnly = D3DXMESH_USEHWONLY ,
	MeshOptSystemmem = D3DXMESH_SYSTEMMEM ,
	MeshOptManaged = D3DXMESH_MANAGED ,
	MeshOptWriteOnly = D3DXMESH_WRITEONLY ,
	MeshOptDynamic = D3DXMESH_DYNAMIC ,
	MeshOptSoftwareProcessing = D3DXMESH_SOFTWAREPROCESSING
};

class DMeshRender : public DBaseCom
{
public:
	DMeshRender(DGameObject* gameObj, DWORD indexInParent);
	~DMeshRender();
	BOOL CreateMeshBox(D3DXVECTOR3 size);
	BOOL CreateMeshSphere(FLOAT radius);
	BOOL CreateMeshTeapot();
	BOOL CreateMeshFromFileX(LPCWSTR pFileName, DWORD options);
public:
	VOID Run();
	DMateriaRender* GetMaterialRender(DWORD matIndex = 0);
	LPD3DXMESH GetMesh();
	VOID SetMesh(LPD3DXMESH mess);
private:
	//DMateriaRender* m_pMatRender;
	vector<DMateriaRender*> m_matRenders;
	LPD3DXMESH m_pMess;
	//BOOL m_isDraw;
};