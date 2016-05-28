#pragma once
#include "CommRenderHead.h"

class DMaterialRender : public DBaseCom
{
public:
	DMaterialRender(DGameObject * gameObj, DWORD indexInParent);
	DMaterialRender(DGameObject * gameObj, DWORD indexInParent, D3DMATERIAL9 & mat, LPDIRECT3DTEXTURE9 & texture);
	~DMaterialRender();
	VOID Run();

public:
	BOOL LoadTexture(LPCWSTR textureFile);
public:

	//VOID SetMaterial(D3DMATERIAL9& mat);
	//VOID GetMaterial(D3DMATERIAL9& pOut);
	//VOID SetTexture(LPDIRECT3DTEXTURE9 & texture);
	//VOID GetTexture(LPDIRECT3DTEXTURE9 & pOut);

public :
	D3DMATERIAL9  material;
	LPDIRECT3DTEXTURE9 texture;



};