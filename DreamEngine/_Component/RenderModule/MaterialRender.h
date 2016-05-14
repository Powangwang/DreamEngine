#pragma once
#include "CommRenderHead.h"

typedef struct _TEXTURESTATE
{
	DWORD tsStage;
	D3DTEXTURESTAGESTATETYPE tsTextureStateType;
	DWORD tsValue;
}TEXTURESTATE, *PTEXTURESTATE;

typedef struct _SAMPLERSTATE
{
	DWORD ssSampler;
	D3DSAMPLERSTATETYPE ssSamplerStateType;
	DWORD ssValue;
}SAMPLERSTATE, *PSAMPLERSTATE;

class DMaterialRender : public DBaseCom
{
public:
	DMaterialRender(DGameObject * gameObj, DWORD indexInParent);
	DMaterialRender(DGameObject * gameObj, DWORD indexInParent, D3DMATERIAL9 & mat, LPDIRECT3DTEXTURE9 & texture);
	~DMaterialRender();
	VOID Run();

public:
	BOOL LoadTexture(LPWSTR textureFile);
public:

	VOID AddTextureSate(TEXTURESTATE & textureState);
	VOID AddSamplerState(SAMPLERSTATE & samplerState);
	//VOID SetMaterial(D3DMATERIAL9& mat);
	//VOID GetMaterial(D3DMATERIAL9& pOut);
	//VOID SetTexture(LPDIRECT3DTEXTURE9 & texture);
	//VOID GetTexture(LPDIRECT3DTEXTURE9 & pOut);
public :
	D3DMATERIAL9  material;
	LPDIRECT3DTEXTURE9 texture;

	vector<TEXTURESTATE> m_textureStates;
	vector<SAMPLERSTATE>m_samplerStates;
};