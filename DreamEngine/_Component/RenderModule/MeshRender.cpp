#include "MeshRender.h"


DMeshRender::DMeshRender(DGameObject* gameObj)
	:DBaseCom(L"", COMTYPE::DERenderMesh, gameObj),m_pMess(nullptr), m_isDraw(FALSE)
{
	m_pMatRender = new DMateriaRender(gameObj);
	if (m_pMatRender != nullptr)
		m_pMatRender->SetMaterial();
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
	if (FAILED(D3DXCreateBox(DDEInitialize::GetDevice(), size.x, size.y, size.z, &m_pMess, NULL)))
		return FALSE;

	m_isDraw = TRUE;
	return TRUE;
}

VOID DMeshRender::Run()
{
	if (!m_isDraw)
		return ;

	m_d3dDivce->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_d3dDivce->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pMess->DrawSubset(0);
	m_pMatRender->Run();
}
