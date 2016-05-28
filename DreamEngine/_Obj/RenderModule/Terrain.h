#pragma once
#include "GameObject.h"

class DTerrain : public DGameObject
{
public:
	DTerrain(INT rows, INT cols, INT cellSpacing, FLOAT terrainHeightScale);
	~DTerrain();
	BOOL CreateTerrain(LPCWSTR terrainRawPath, LPCWSTR terrainTexturePath = nullptr);
	FLOAT GetTerrainHeight(FLOAT zPix, FLOAT xPix);

private:
	BOOL ReadRawFile(LPCWSTR terrainFilePath);
	BOOL InitVertices(LPD3DXMESH terrainMesh);
	BOOL InitIndices(LPD3DXMESH terrainMesh);
	BOOL InitTexture(DMeshRender* terrainMesh, LPCWSTR textureFilePath = nullptr);
	FLOAT GetTerrainVertHeight(DWORD rowVert, DWORD colVert);
	VOID InitEffect(DMeshRender* meshRender);
private:
	struct TERRAINHEIGHTINFO
	{
		//	WCHAR* thiTerrainFilePath;
		FLOAT* pthiHeights;				//����߶ȵ�ָ��
		DWORD thiVertsCount;				//����ָ����ָ�����ݵ�����
		FLOAT thiHeightScale;				//��ͼ�߶ȵ���������
	}m_terrainInfo;

	DWORD m_cellsPerRow;				//ÿ�еĵĸ���������������-1��
	DWORD m_cellsPerCol;				//ÿ�еĸ���������������-1��
	DWORD m_cellSpacing;			//����֮��Ŀ��

};