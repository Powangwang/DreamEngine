#include "MeshRender.h"


DMeshRender::DMeshRender(DGameObject* gameObj)
	:DBaseCom(L"", COMTYPE::DERenderMesh, gameObj),m_pMess(NULL), m_isDraw(FALSE)
{
}
DMeshRender::~DMeshRender()
{
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

	DDEInitialize::GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	DDEInitialize::GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pMess->DrawSubset(0);

}
