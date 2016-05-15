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

BOOL DSky::CreateSkybox(LPWSTR frontTextureFile, LPWSTR backTextureFile, LPWSTR leftTextureFile, LPWSTR rightTextureFile, LPWSTR topTextureFile)
{
	BOOL ret = FALSE;
	DMeshRender* meshRender = (DMeshRender*)AddComponent(COMTYPE::DERenderMesh);
	if (meshRender == nullptr)
		return FALSE;
	LPD3DXMESH skyMesh = nullptr;
	if (FAILED(D3DXCreateMeshFVF(2, 4, D3DXMESH_MANAGED, SKYBOX_FVF, DDEInitialize::gRootDevice, &skyMesh)))
		return FALSE;

	if (!InitVertices(skyMesh))
		return FALSE;
	if (!InitIndices(skyMesh))
		return FALSE;

	LPWSTR texFiles[5] = { frontTextureFile, backTextureFile, leftTextureFile, rightTextureFile, topTextureFile };
	if (!InitTexture(meshRender, texFiles, 1))
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

	//v[0] = SkyboxVertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f);
	//v[1] = SkyboxVertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f);
	//v[2] = SkyboxVertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f);
	//v[3] = SkyboxVertex(1.0f, -1.0f, -1.0f, 1.0f, 0.0f);
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
BOOL DSky::InitIndices(LPD3DXMESH skyboxMesh)
{
	if (skyboxMesh == nullptr)
		return FALSE;

	WORD * i = nullptr;
	skyboxMesh->LockIndexBuffer(0, (LPVOID*)&i);
	if (i == nullptr)
		return FALSE;
	for (int faceCount = 0; faceCount < 1; faceCount++)
	{
		i[0 + faceCount * 6] = (WORD)(0 + faceCount * 4); 
		i[1 + faceCount * 6] = (WORD)(1 + faceCount * 4);
		i[2 + faceCount * 6] = (WORD)(2 + faceCount * 4);

		i[3 + faceCount * 6] = (WORD)(2 + faceCount * 4);
		i[4 + faceCount * 6] = (WORD)(1 + faceCount * 4);
		i[5 + faceCount * 6] = (WORD)(3 + faceCount * 4);
	}
	//i[0] = 0; i[1] = 1; i[2] = 2;
	//i[3] = 1; i[4] = 2; i[5] = 3;
	skyboxMesh->UnlockIndexBuffer();

	DWORD* attributeBuffer = nullptr;
	skyboxMesh->LockAttributeBuffer(0, &attributeBuffer);
	if (attributeBuffer == nullptr)
		return FALSE;
	for (int faceCount = 0; faceCount < 1; faceCount++)
	{
		attributeBuffer[0 + faceCount * 2] = faceCount;
		attributeBuffer[1 + faceCount * 2] = faceCount;
	}
	//attributeBuffer[0] = 0;
	//attributeBuffer[1] = 0;
	skyboxMesh->UnlockAttributeBuffer();

	return TRUE;
}

BOOL DSky::InitTexture(DMeshRender * meshRender, LPWSTR * textureFiles, INT fileCount)
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
	RENDERSTATE rstate;
	rstate.rsRenderStateType = D3DRS_FILLMODE;
	rstate.rsValue = D3DFILL_SOLID;
	//rstate.rsValue = D3DFILL_WIREFRAME;
	meshRender->AddRenderState(rstate);

	rstate.rsRenderStateType = D3DRS_CULLMODE;
	rstate.rsValue = D3DCULL_NONE;
	meshRender->AddRenderState(rstate);

	rstate.rsRenderStateType = D3DRS_LIGHTING;
	rstate.rsValue = FALSE;
	meshRender->AddRenderState(rstate);

	TEXTURESTATE tstate;
	tstate.tsStage = 0;
	tstate.tsTextureStateType = D3DTSS_COLOROP;
	tstate.tsValue = D3DTOP_SELECTARG1;
	meshRender->AddTextureSate(tstate);		//将纹理颜色混合的第一个参数的颜色值用于输出

	tstate.tsStage = 0;
	tstate.tsTextureStateType = D3DTSS_COLORARG1;
	tstate.tsValue = D3DTA_TEXTURE;
	meshRender->AddTextureSate(tstate);		//纹理颜色混合的第一个参数的值就取纹理颜色值

}

