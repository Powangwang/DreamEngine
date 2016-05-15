#include "MaterialRender.h"

DMaterialRender::DMaterialRender(DGameObject* gameObj, DWORD indexInParent)
	:DBaseCom(L"", COMTYPE::DERenderMaterial, gameObj, indexInParent),
	texture(nullptr)
{
	material.Ambient = D3DXCOLOR(0.0, 0.0f, 0.0f, 0.0f);
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	material.Specular = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
	material.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	material.Power = 0.0f;
}

DMaterialRender::DMaterialRender(DGameObject * gameObj, DWORD indexInParent, D3DMATERIAL9 & mat, LPDIRECT3DTEXTURE9 & texture)
	: DBaseCom(L"", COMTYPE::DERenderMaterial, gameObj, indexInParent),
	material(mat), texture(texture)
{

}

DMaterialRender::~DMaterialRender()
{
	if (texture != nullptr)
		texture->Release();
}

VOID DMaterialRender::Run()
{
	if (m_isEnabled == FALSE)
		return;

	DDEInitialize::gRootDevice->SetMaterial(&material);
	if(texture != nullptr)
		DDEInitialize::gRootDevice->SetTexture(0, texture);
}

BOOL DMaterialRender::LoadTexture(LPWSTR textureFile)
{
	if (FAILED(D3DXCreateTextureFromFile(DDEInitialize::gRootDevice, textureFile, &texture)))
		return FALSE;
	return TRUE;
}


//VOID DMaterialRender::SetMaterial(D3DMATERIAL9& mat)
//{
//	ZeroMemory(&m_mat, sizeof(D3DMATERIAL9));
//	m_mat = mat;
//}
//
//VOID DMaterialRender::GetMaterial(D3DMATERIAL9 & pOut)
//{
//	pOut = m_mat;
//}
//
//VOID DMaterialRender::SetTexture(LPDIRECT3DTEXTURE9 & texture)
//{
//	m_texture = texture;
//}
//
//VOID DMaterialRender::GetTexture(LPDIRECT3DTEXTURE9 & pOut)
//{
//	pOut = m_texture;
//}
