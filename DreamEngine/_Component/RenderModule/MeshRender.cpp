#include "MeshRender.h"


DMeshRender::DMeshRender(DGameObject* gameObj, DWORD indexInParent)
	:DBaseCom(L"", COMTYPE::DERenderMesh, gameObj, indexInParent),m_pMess(nullptr)
{
	m_isEnabled = TRUE;
	DMateriaRender * matRender = new DMateriaRender(gameObj, 0);
	m_matRenders.push_back(matRender);
	//if (m_pMatRender != nullptr)
	//	m_pMatRender->SetMaterial();
}

DMeshRender::~DMeshRender()
{
	int matRenderCount = m_matRenders.size();
	for (int matRenderIndex = 0; matRenderIndex < matRenderCount; matRenderIndex++)
	{
		delete m_matRenders[matRenderIndex];
	}
	m_matRenders.clear();

	if(m_pMess != nullptr)
		m_pMess->Release();
}

BOOL DMeshRender::CreateMeshBox(D3DXVECTOR3 size)
{
	if (FAILED(D3DXCreateBox(DDEInitialize::gRootDevice, size.x, size.y, size.z, &m_pMess, nullptr)))
		return FALSE;

	m_isEnabled = TRUE;
	return TRUE;
}

BOOL DMeshRender::CreateMeshSphere(FLOAT radius)
{
	if (FAILED(D3DXCreateSphere(DDEInitialize::gRootDevice, radius, 32, 32, &m_pMess, nullptr)))
		return FALSE;

	m_isEnabled = TRUE;
	return TRUE;
}

BOOL DMeshRender::CreateMeshTeapot()
{
	if (FAILED(D3DXCreateTeapot(DDEInitialize::gRootDevice, &m_pMess, nullptr)))
		return FALSE;

	m_isEnabled = TRUE;
	return TRUE;
}

BOOL DMeshRender::CreateMeshFromFileX(LPCWSTR pFileName, DWORD options)
{

	LPD3DXBUFFER ppAdjacency;
	LPD3DXBUFFER ppMaterials;
	LPD3DXBUFFER ppEffectInstances;
	DWORD NumMaterials;

	if (FAILED(D3DXLoadMeshFromX(pFileName, options, DDEInitialize::gRootDevice, 
		&ppAdjacency, &ppMaterials, &ppEffectInstances, &NumMaterials, &m_pMess)))
		return FALSE;

	D3DXMATERIAL *pMtrls = (D3DXMATERIAL*)ppMaterials->GetBufferPointer();
	LPDIRECT3DTEXTURE9 tmpTexture = nullptr;
	for (DWORD matRenderIndex = 0; matRenderIndex < NumMaterials; matRenderIndex++)
	{
		if (!FAILED(D3DXCreateTextureFromFileA(DDEInitialize::gRootDevice, pMtrls[matRenderIndex].pTextureFilename, &tmpTexture)))
		{
			DMateriaRender* matRender = new DMateriaRender(m_gameObj, 0, pMtrls[matRenderIndex].MatD3D, tmpTexture);
			m_matRenders.push_back(matRender);
		}
	}
	m_isEnabled = TRUE;
	return TRUE;
}

VOID DMeshRender::Run()
{
	if (!m_isEnabled)
		return ;
	DDEInitialize::gRootDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	DDEInitialize::gRootDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	DWORD NumMaterials = m_matRenders.size();
	for (DWORD runIndex = 0; runIndex < NumMaterials; runIndex++)
	{
		m_pMess->DrawSubset(runIndex);
		m_matRenders[runIndex]->Run();
	}

}

DMateriaRender * DMeshRender::GetMaterialRender(DWORD matIndex)
{
	if (matIndex >= m_matRenders.size())
		return nullptr;

	return m_matRenders[matIndex];
}

LPD3DXMESH DMeshRender::GetMesh()
{
	return m_pMess;
}

VOID DMeshRender::SetMesh(LPD3DXMESH mess)
{
	m_pMess = mess;
}
