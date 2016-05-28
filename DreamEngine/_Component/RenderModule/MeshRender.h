#pragma once
#include "CommRenderHead.h"
#include "MaterialRender.h"
#include <vector>


typedef struct _RENDERSTATE
{
	D3DRENDERSTATETYPE rsRenderStateType;
	DWORD rsValue;
}RENDERSTATE, *PRENDERSTATE;

typedef struct _TEXTURESTATE
{
	DWORD tsStage;
	D3DTEXTURESTAGESTATETYPE tsTextureStateType;
	DWORD tsValue;
}TEXTURESTATE, *PTEXTURESTATE;

typedef struct _SAMPLERSTATE
{
	DWORD ssSampler;
	D3DSAMPLERSTATETYPE ssSamplerStateType;
	DWORD ssValue;
}SAMPLERSTATE, *PSAMPLERSTATE;

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
	DMaterialRender* CreateMaterial();
	BOOL DestroyMaterial(DWORD matIndex);
	VOID DestroyMaterialAll();

public:
	VOID Run();
	DMaterialRender* GetMaterialRender(DWORD matIndex = 0);
	LPD3DXMESH GetMesh();
	VOID SetMesh(LPD3DXMESH mess);
	VOID AddRenderState(RENDERSTATE & renderState);
	VOID AddTextureSate(TEXTURESTATE & textureState);
	VOID AddSamplerState(SAMPLERSTATE & samplerState);

private:
	VOID ApplyRenderState();
	VOID ApplyOrignRenderState();
private:
	//DMaterialRender* m_pMatRender;
	vector<DMaterialRender*> m_matRenders;
	LPD3DXMESH m_pMesh;

	vector<RENDERSTATE> m_renderStates;
	vector<RENDERSTATE> m_orignRenderStates;
	vector<TEXTURESTATE> m_textureStates;
	vector<SAMPLERSTATE>m_samplerStates;
	vector<TEXTURESTATE> m_orignTextureStates;
	vector<SAMPLERSTATE>m_orignSamplerStates;
	//BOOL m_isDraw;

public:
	BOOL CreateBox();
};