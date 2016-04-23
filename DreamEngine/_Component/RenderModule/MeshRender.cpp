#include "MeshRender.h"


DMeshRender::DMeshRender(DGameObject* gameObj, DWORD indexInParent)
	:DBaseCom(L"", COMTYPE::DERenderMesh, gameObj, indexInParent),m_pMess(nullptr)
{
	m_isEnabled = FALSE;
	m_pMatRender = new DMateriaRender(gameObj, 0);
	//if (m_pMatRender != nullptr)
	//	m_pMatRender->SetMaterial();
}

DMeshRender::~DMeshRender()
{
	if (m_pMatRender != nullptr)
		delete m_pMatRender;

	if(m_pMess != nullptr)
		m_pMess->Release();
}

BOOL DMeshRender::CreateMeshBox(D3DXVECTOR3 size)
{
	if (FAILED(D3DXCreateBox(m_d3dDivce, size.x, size.y, size.z, &m_pMess, NULL)))
		return FALSE;

	m_isEnabled = TRUE;
	return TRUE;
}

BOOL DMeshRender::CreateMeshSphere(FLOAT radius)
{
	if (FAILED(D3DXCreateSphere(m_d3dDivce, radius, 32, 32, &m_pMess, NULL)))
		return FALSE;

	m_isEnabled = TRUE;
	return TRUE;
}

BOOL DMeshRender::CreateMeshTeapot()
{
	if (FAILED(D3DXCreateTeapot(m_d3dDivce, &m_pMess, NULL)))
		return FALSE;

	m_isEnabled = TRUE;
	return TRUE;
}

VOID DMeshRender::Run()
{
	if (!m_isEnabled)
		return ;
	m_d3dDivce->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_d3dDivce->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pMess->DrawSubset(0);
	m_pMatRender->Run();
}
