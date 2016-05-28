#include "Sky.h"

#define SKYBOX_FVF (D3DFVF_XYZ | D3DFVF_TEX1)
struct SkyboxVertex
{
	SkyboxVertex(float x, float y, float z, float u, float v)
	{
		_x = x; _y = y; _z = z, _u = u; _v = v;
	}
	float _x, _y, _z;
	float _u, _v;

};

DSky::DSky(FLOAT length)
	:DGameObject(GAMEOBJTYPE::GameObjSky), m_skyLength(length)
{
}

DSky::~DSky()
{
}

BOOL DSky::CreateSkybox(LPCWSTR frontTextureFile, LPCWSTR backTextureFile, LPCWSTR leftTextureFile, LPCWSTR rightTextureFile, LPCWSTR topTextureFile)
{
	BOOL ret = FALSE;
	DMeshRender* meshRender = (DMeshRender*)AddComponent(COMTYPE::DERenderMesh);
	if (meshRender == nullptr)
		return FALSE;
	LPD3DXMESH skyMesh = nullptr;
	if (FAILED(D3DXCreateMeshFVF(10, 20, D3DXMESH_MANAGED, SKYBOX_FVF, DDEInitialize::gRootDevice, &skyMesh)))
		return FALSE;

	if (!InitVertices(skyMesh))
		return FALSE;
	if (!InitIndices(skyMesh, 5))
		return FALSE;

	LPCWSTR texFiles[5] = { frontTextureFile, backTextureFile, leftTextureFile, rightTextureFile, topTextureFile };
	if (!InitTexture(meshRender, texFiles, 5))
		return FALSE;

	//meshRender->CreateMaterial();
	meshRender->SetMesh(skyMesh);
	InitEffect(meshRender);

	return TRUE;
}

BOOL DSky::InitVertices(LPD3DXMESH skyboxMesh)
{
	if (skyboxMesh == nullptr)
		return FALSE;

	FLOAT vetPos = m_skyLength / 2;
	SkyboxVertex * v = nullptr;
	skyboxMesh->LockVertexBuffer(0, (LPVOID*)&v);
	if (v == nullptr)
		return FALSE;
	//前面
	v[0] = SkyboxVertex(-vetPos, vetPos * 2, vetPos, 0.0f, 0.0f);
	v[1] = SkyboxVertex(vetPos, vetPos * 2, vetPos, 1.0f, 0.0f);
	v[2] = SkyboxVertex(-vetPos, 0.0f, vetPos, 0.0f, 1.0f);
	v[3] = SkyboxVertex(vetPos, 0.0f, vetPos, 1.0f, 1.0f);
	//背面
	v[4] = SkyboxVertex(vetPos, vetPos * 2, -vetPos, 0.0f, 0.0f);
	v[5] = SkyboxVertex(-vetPos, vetPos * 2, -vetPos, 1.0f, 0.0f);
	v[6] = SkyboxVertex(vetPos, 0.0f, -vetPos, 0.0f, 1.0f);
	v[7] = SkyboxVertex(-vetPos, 0.0f, -vetPos, 1.0f, 1.0f);
	//左边
	v[8] = SkyboxVertex(-vetPos, vetPos * 2, -vetPos, 0.0f, 0.0f);
	v[9] = SkyboxVertex(-vetPos, vetPos * 2, vetPos, 1.0f, 0.0f);
	v[10] = SkyboxVertex(-vetPos, 0.0f, -vetPos, 0.0f, 1.0f);
	v[11] = SkyboxVertex(-vetPos, 0.0f, vetPos, 1.0f, 1.0f);
	//右边
	v[12] = SkyboxVertex(vetPos, vetPos * 2, vetPos, 0.0f, 0.0f);
	v[13] = SkyboxVertex(vetPos, vetPos * 2, -vetPos, 1.0f, 0.0f);
	v[14] = SkyboxVertex(vetPos, 0.0f, vetPos, 0.0f, 1.0f);
	v[15] = SkyboxVertex(vetPos, 0.0f, -vetPos, 1.0f, 1.0f);
	//顶点
	v[16] = SkyboxVertex(-vetPos, vetPos * 2, -vetPos, 0.0f, 0.0f);
	v[17] = SkyboxVertex(vetPos, vetPos * 2, -vetPos, 1.0f, 0.0f);
	v[18] = SkyboxVertex(-vetPos, vetPos * 2, vetPos, 0.0f, 1.0f);
	v[19] = SkyboxVertex(vetPos, vetPos * 2, vetPos, 1.0f, 1.0f);
	skyboxMesh->UnlockIndexBuffer();
	return TRUE;
}
BOOL DSky::InitIndices(LPD3DXMESH skyboxMesh, DWORD faceCount)
{
	if (skyboxMesh == nullptr)
		return FALSE;

	WORD * i = nullptr;
	skyboxMesh->LockIndexBuffer(0, (LPVOID*)&i);
	if (i == nullptr)
		return FALSE;
	for (DWORD faceIndex = 0; faceIndex < faceCount; faceIndex++)
	{
		i[0 + faceIndex * 6] = (WORD)(0 + faceIndex * 4); 
		i[1 + faceIndex * 6] = (WORD)(1 + faceIndex * 4);
		i[2 + faceIndex * 6] = (WORD)(2 + faceIndex * 4);

		i[3 + faceIndex * 6] = (WORD)(2 + faceIndex * 4);
		i[4 + faceIndex * 6] = (WORD)(1 + faceIndex * 4);
		i[5 + faceIndex * 6] = (WORD)(3 + faceIndex * 4);
	}
	skyboxMesh->UnlockIndexBuffer();

	DWORD* attributeBuffer = nullptr;
	skyboxMesh->LockAttributeBuffer(0, &attributeBuffer);
	if (attributeBuffer == nullptr)
		return FALSE;
	for (DWORD faceIndex = 0; faceIndex < faceCount; faceIndex++)
	{
		attributeBuffer[0 + faceIndex * 2] = faceIndex;
		attributeBuffer[1 + faceIndex * 2] = faceIndex;
	}
	//attributeBuffer[0] = 0;
	//attributeBuffer[1] = 0;
	skyboxMesh->UnlockAttributeBuffer();

	return TRUE;
}

BOOL DSky::InitTexture(DMeshRender * meshRender, LPCWSTR * textureFiles, INT fileCount)
{
	DMaterialRender* matRender = nullptr;
	for (INT textureIndex = 0; textureIndex < fileCount; textureIndex++)
	{
		matRender = meshRender->CreateMaterial();

		if (!matRender->LoadTexture(textureFiles[textureIndex]))
		{
			meshRender->DestroyMaterialAll();
			return FALSE;
		}
	}
	return TRUE;
}

VOID DSky::InitEffect(DMeshRender * meshRender)
{
	//RENDERSTATE rstate;
	//rstate.rsRenderStateType = D3DRS_FILLMODE;
	//rstate.rsValue = D3DFILL_SOLID;
	////rstate.rsValue = D3DFILL_WIREFRAME;
	//meshRender->AddRenderState(rstate);

	//rstate.rsRenderStateType = D3DRS_CULLMODE;
	//rstate.rsValue = D3DCULL_CCW;
	//meshRender->AddRenderState(rstate);

	//rstate.rsRenderStateType = D3DRS_LIGHTING;
	//rstate.rsValue = FALSE;
	//meshRender->AddRenderState(rstate);

	TEXTURESTATE tstate;
	tstate.tsStage = 0;
	tstate.tsTextureStateType = D3DTSS_COLOROP;
	tstate.tsValue = D3DTOP_SELECTARG1;
	meshRender->AddTextureSate(tstate);		//将纹理颜色混合的第一个参数的颜色值用于输出

	tstate.tsStage = 0;
	tstate.tsTextureStateType = D3DTSS_COLORARG1;
	tstate.tsValue = D3DTA_TEXTURE;
	meshRender->AddTextureSate(tstate);		//纹理颜色混合的第一个参数的值就取纹理颜色值

	SAMPLERSTATE sstate;
	sstate.ssSampler = 0;
	sstate.ssSamplerStateType = D3DSAMP_ADDRESSU;
	sstate.ssValue = D3DTADDRESS_MIRROR;
	meshRender->AddSamplerState(sstate);

	sstate.ssSampler = 0;
	sstate.ssSamplerStateType = D3DSAMP_ADDRESSV;
	sstate.ssValue = D3DTADDRESS_MIRROR;
	meshRender->AddSamplerState(sstate);

}

