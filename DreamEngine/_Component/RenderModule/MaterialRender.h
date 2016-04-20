#pragma once
#include "CommRenderHead.h"

class DMateriaRender : public DBaseCom
{
public:
	DMateriaRender(DGameObject* gameObj);
	~DMateriaRender();
	VOID Run();

public:
	VOID SetMaterial();
	VOID GetMaterial();
private :
	D3DMATERIAL9 * m_pMat;
	LPDIRECT3DTEXTURE9 * m_pTexture;
};