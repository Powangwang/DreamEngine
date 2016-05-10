#include "MaterialRender.h"

DMateriaRender::DMateriaRender(DGameObject* gameObj, DWORD indexInParent)
	:DBaseCom(L"", COMTYPE::DERenderMaterial, gameObj, indexInParent),
	texture(nullptr)
{
	material.Ambient = D3DXCOLOR(0.0, 0.0f, 0.0f, 0.0f);
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	material.Specular = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
	material.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	material.Power = 0.0f;
}

DMateriaRender::DMateriaRender(DGameObject * gameObj, DWORD indexInParent, D3DMATERIAL9 & mat, LPDIRECT3DTEXTURE9 & texture)
	: DBaseCom(L"", COMTYPE::DERenderMaterial, gameObj, indexInParent),
	material(mat), texture(texture)
{

}

DMateriaRender::~DMateriaRender()
{
	if (texture != nullptr)
		texture->Release();
}

VOID DMateriaRender::Run()
{
	if (m_isEnabled == FALSE)
		return;

	DDEInitialize::gRootDevice->SetMaterial(&material);
	if(texture != nullptr)
		DDEInitialize::gRootDevice->SetTexture(0, texture);
}

//VOID DMateriaRender::SetMaterial(D3DMATERIAL9& mat)
//{
//	ZeroMemory(&m_mat, sizeof(D3DMATERIAL9));
//	m_mat = mat;
//}
//
//VOID DMateriaRender::GetMaterial(D3DMATERIAL9 & pOut)
//{
//	pOut = m_mat;
//}
//
//VOID DMateriaRender::SetTexture(LPDIRECT3DTEXTURE9 & texture)
//{
//	m_texture = texture;
//}
//
//VOID DMateriaRender::GetTexture(LPDIRECT3DTEXTURE9 & pOut)
//{
//	pOut = m_texture;
//}
