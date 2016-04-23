#include "MaterialRender.h"

DMateriaRender::DMateriaRender(DGameObject* gameObj, DWORD indexInParent)
	:DBaseCom(L"", COMTYPE::DERenderMaterial, gameObj, indexInParent),
	m_pTexture(nullptr)
{
	D3DMATERIAL9 mat;
	mat.Ambient = D3DXCOLOR(0.0, 0.0f, 0.0f, 0.0f);
	mat.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	mat.Specular = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
	mat.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	mat.Power = 0.0f;
	SetMaterial(mat);
}

DMateriaRender::~DMateriaRender()
{

}

VOID DMateriaRender::Run()
{
	if (m_isEnabled == FALSE)
		return;

	m_d3dDivce->SetMaterial(&m_mat);
}

VOID DMateriaRender::SetMaterial(D3DMATERIAL9& mat)
{
	ZeroMemory(&m_mat, sizeof(D3DMATERIAL9));
	m_mat = mat;
}

VOID DMateriaRender::GetMaterial(D3DMATERIAL9 & pOut)
{
	pOut = m_mat;
}
