#include "MaterialRender.h"

DMateriaRender::DMateriaRender(DGameObject* gameObj)
	:DBaseCom(L"", COMTYPE::DERenderMaterial, gameObj),
	m_pMat(nullptr), m_pTexture(nullptr)
{

}

DMateriaRender::~DMateriaRender()
{
	if (m_pMat != nullptr)
		delete m_pMat;

}

VOID DMateriaRender::Run()
{
	if (m_pMat != nullptr)
		m_d3dDivce->SetMaterial(m_pMat);
}

VOID DMateriaRender::SetMaterial()
{
	if (m_pMat == nullptr)
		m_pMat = new D3DMATERIAL9;
	m_pMat->Ambient = D3DXCOLOR(0.0, 0.0f, 0.0f, 0.0f);
	m_pMat->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_pMat->Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_pMat->Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_pMat->Power = 0.0f;
}

VOID DMateriaRender::GetMaterial()
{
	return VOID();
}
