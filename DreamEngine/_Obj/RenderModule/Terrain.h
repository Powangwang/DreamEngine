#pragma once
#include "GameObject.h"

class DTerrain : public DGameObject
{
public:
	DTerrain(INT rows, INT cols, INT cellSpacing, FLOAT terrainHeightScale);
	~DTerrain();
	BOOL CreateTerrain(WCHAR* terrainFilePath);
	FLOAT GetTerrainHeight(FLOAT zPix, FLOAT xPix);

private:
	BOOL ReadRawFile(WCHAR* terrainFilePath);
	BOOL InitVertices(LPD3DXMESH terrainMesh);
	BOOL InitIndices(LPD3DXMESH terrainMesh);
	BOOL InitTexture(DMeshRender* terrainMesh, WCHAR* textureFilePath = nullptr);
	FLOAT GetTerrainVertHeight(DWORD rowVert, DWORD colVert);
	VOID InitEffect(DMeshRender* meshRender);
private:
	struct TERRAINHEIGHTINFO
	{
		//	WCHAR* thiTerrainFilePath;
		FLOAT* pthiHeights;				//保存高度的指针
		DWORD thiVertsCount;				//保存指针所指向数据的数量
		FLOAT thiHeightScale;				//地图高度的缩放因子
	}m_terrainInfo;

	DWORD m_cellsPerRow;				//每行的的格子数（等于列数-1）
	DWORD m_cellsPerCol;				//每列的格子数（等于行数-1）
	DWORD m_cellSpacing;			//顶点之间的宽度

};