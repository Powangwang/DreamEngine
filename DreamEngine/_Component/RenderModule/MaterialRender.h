#pragma once
#include "CommRenderHead.h"

class DMateriaRender : public DBaseCom
{
public:
	DMateriaRender(DGameObject * gameObj, DWORD indexInParent);
	~DMateriaRender();
	VOID Run();

public:
	VOID SetMaterial(D3DMATERIAL9& mat);
	VOID GetMaterial(D3DMATERIAL9& pOut);
private :
	D3DMATERIAL9  m_mat;
	LPDIRECT3DTEXTURE9 * m_pTexture;
};