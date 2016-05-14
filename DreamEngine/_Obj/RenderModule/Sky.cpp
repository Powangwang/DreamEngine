#include "Sky.h"

#define SKYBOX_FVF (D3DFVF_XYZ | D3DFVF_TEX1)
struct SkyboxVertex
{
	SkyboxVertex(float x, float y, float z, float u, float v)
	{
		_x = x; _y = y; _z = z; _u = u; _v = v;
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
	LPDIRECT3DTEXTURE9 sky;
	if (FAILED(D3DXCreateMeshFVF(10, 20, 0, SKYBOX_FVF, DDEInitialize::gRootDevice, &skyMesh)))
		return FALSE;

	if (!InitVertices(skyMesh))
		return FALSE;
	if (!InitIndices(skyMesh))
		return FALSE;

	LPWSTR texFiles[5] = { frontTextureFile, backTextureFile, leftTextureFile, rightTextureFile, topTextureFile };
	if (!InitTexture(meshRender, texFiles, 5))
		return FALSE;

	meshRender->SetMesh(skyMesh);
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
BOOL DSky::InitIndices(LPD3DXMESH skyboxMesh)
{
	if (skyboxMesh == nullptr)
		return FALSE;

	DWORD * i = nullptr;
	skyboxMesh->LockIndexBuffer(0, (LPVOID*)&i);
	if (i == nullptr)
		return FALSE;
	for (int faceCount = 0; faceCount < 5; faceCount++)
	{
		i[0 + faceCount * 6] = 0 + faceCount * 4; 
		i[1 + faceCount * 6] = 1 + faceCount * 4; 
		i[2 + faceCount * 6] = 2 + faceCount * 4; 
		i[3 + faceCount * 6] = 2 + faceCount * 4;
		i[4 + faceCount * 6] = 1 + faceCount * 4; 
		i[5 + faceCount * 6] = 3 + faceCount * 4;
	}
	skyboxMesh->UnlockIndexBuffer();

	DWORD* attributeBuffer = nullptr;
	skyboxMesh->LockAttributeBuffer(0, &attributeBuffer);
	if (attributeBuffer == nullptr)
		return FALSE;
	for (int faceCount = 0; faceCount < 5; faceCount++)
	{
		attributeBuffer[0 + faceCount * 2] = faceCount;
		attributeBuffer[1 + faceCount * 2] = faceCount;
	}
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

