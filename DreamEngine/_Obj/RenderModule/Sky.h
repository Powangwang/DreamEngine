#pragma once
#include "GameObject.h"

class DSky : public DGameObject
{
public:
	DSky(FLOAT length);
	~DSky();
	BOOL CreateSkybox(LPCWSTR frontTextureFile, LPCWSTR backTextureFile, LPCWSTR leftTextureFile,
		LPCWSTR rightTextureFile, LPCWSTR topTextureFile);

private:
	BOOL InitVertices(LPD3DXMESH skyboxMesh);
	BOOL InitIndices(LPD3DXMESH skyboxMesh, DWORD faceCount);
	BOOL InitTexture(DMeshRender* meshRender, LPCWSTR* textureFiles, INT fileCount);
	VOID InitEffect(DMeshRender* meshRender);
private:
	FLOAT m_skyLength;
};