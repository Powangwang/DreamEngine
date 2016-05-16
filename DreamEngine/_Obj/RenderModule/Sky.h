#pragma once
#include "GameObject.h"

class DSky : public DGameObject
{
public:
	DSky(FLOAT length);
	~DSky();
	BOOL CreateSkybox(LPWSTR frontTextureFile, LPWSTR backTextureFile, LPWSTR leftTextureFile,
		LPWSTR rightTextureFile, LPWSTR topTextureFile);

private:
	BOOL InitVertices(LPD3DXMESH skyboxMesh);
	BOOL InitIndices(LPD3DXMESH skyboxMesh, DWORD faceCount);
	BOOL InitTexture(DMeshRender* meshRender, LPWSTR* textureFiles, INT fileCount);
	VOID InitEffect(DMeshRender* meshRender);
private:
	FLOAT m_skyLength;
};