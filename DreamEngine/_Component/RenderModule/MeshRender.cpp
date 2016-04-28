#include "MeshRender.h"


DMeshRender::DMeshRender(DGameObject* gameObj, DWORD indexInParent)
	:DBaseCom(L"", COMTYPE::DERenderMesh, gameObj, indexInParent),m_pMess(nullptr),
	m_ppAdjacency(nullptr),m_ppMaterials(nullptr),m_ppEffectInstances(nullptr), m_pNumMaterials(0)
{
	m_isEnabled = FALSE;
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
	if (FAILED(D3DXCreateBox(m_d3dDivce, size.x, size.y, size.z, &m_pMess, NULL)))
		return FALSE;

	m_isEnabled = TRUE;
	m_pNumMaterials = 1;
	return TRUE;
}

BOOL DMeshRender::CreateMeshSphere(FLOAT radius)
{
	if (FAILED(D3DXCreateSphere(m_d3dDivce, radius, 32, 32, &m_pMess, NULL)))
		return FALSE;

	m_isEnabled = TRUE;
	m_pNumMaterials = 1;
	return TRUE;
}

BOOL DMeshRender::CreateMeshTeapot()
{
	if (FAILED(D3DXCreateTeapot(m_d3dDivce, &m_pMess, NULL)))
		return FALSE;

	m_isEnabled = TRUE;
	m_pNumMaterials = 1;
	return TRUE;
}

BOOL DMeshRender::CreateMeshFromFileX(LPCWSTR pFileName, DWORD options)
{
	if (FAILED(D3DXLoadMeshFromX(pFileName, options, m_d3dDivce, 
		&m_ppAdjacency, &m_ppMaterials, &m_ppEffectInstances, &m_pNumMaterials, &m_pMess)))
		return FALSE;

	D3DXMATERIAL *pMtrls = (D3DXMATERIAL*)m_ppMaterials->GetBufferPointer();
	LPDIRECT3DTEXTURE9 tmpTexture = nullptr;
	for (DWORD matRenderIndex = 0; matRenderIndex < m_pNumMaterials; matRenderIndex++)
	{
		if (!FAILED(D3DXCreateTextureFromFileA(m_d3dDivce, pMtrls[matRenderIndex].pTextureFilename, &tmpTexture)))
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
	m_d3dDivce->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_d3dDivce->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	for (DWORD runIndex = 0; runIndex < m_pNumMaterials; runIndex++)
	{
		m_pMess->DrawSubset(runIndex);
		m_matRenders[runIndex]->Run();
	}

}
