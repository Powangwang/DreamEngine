#include "Terrain.h"
#include "RenderModule/MeshRender.h"

#define VERTEX16BIT	65535
#define TERRAIN_FVF (D3DFVF_XYZ | D3DFVF_TEX1)
struct TerrainVertex
{
	TerrainVertex() {}
	TerrainVertex(float x, float y, float z, float u, float v)
	{
		_x = x; _y = y; _z = z; _u = u; _v = v;
	}
	float _x, _y, _z;
	float _u, _v;

};
DTerrain::DTerrain(INT rows, INT cols, INT cellSpacing, FLOAT terrainHeightScale)
	:DGameObject()
{

	m_terrainInfo.thiHeightScale = terrainHeightScale;
	m_terrainInfo.pthiHeights = nullptr;

	m_cellsPerCol = rows - 1;
	m_cellsPerRow = cols - 1;
	m_cellSpacing = cellSpacing;

}
DTerrain::~DTerrain()
{
}

//地形读取比较耗时，后期采用异步读取方式
BOOL DTerrain::CreateTerrain(LPCWSTR terrainRawPath, LPCWSTR terrainTexturePath)
{
	if (!ReadRawFile(terrainRawPath))
		return FALSE;
	DMeshRender* meshRender = (DMeshRender*)AddComponent(COMTYPE::DERenderMesh);
	if (meshRender == nullptr)
		return FALSE;

	DWORD numVertices = (m_cellsPerRow + 1) * (m_cellsPerCol + 1);
	DWORD numTriangle = m_cellsPerRow * m_cellsPerCol * 2;
	LPD3DXMESH terrainMesh = nullptr;

	DWORD meshOpt = 0;
	if (numVertices > VERTEX16BIT || numTriangle > VERTEX16BIT)
	{
		meshOpt |= D3DXMESH_32BIT;
	}
	if (FAILED(D3DXCreateMeshFVF(numTriangle, numVertices, meshOpt, TERRAIN_FVF, DDEInitialize::gRootDevice, &terrainMesh)))
		return FALSE;

	if (!InitVertices(terrainMesh))
		return FALSE;

	if (!InitIndices(terrainMesh))
		return FALSE;
	if (!InitTexture(meshRender, terrainTexturePath))
		return FALSE;
	meshRender->SetMesh(terrainMesh);

	InitEffect(meshRender);	
	return TRUE;
}

//初始化顶点
BOOL DTerrain::InitVertices(LPD3DXMESH terrainMesh)
{
	HRESULT hr = 0;
	DWORD terrainWidth = m_cellSpacing * m_cellsPerRow;
	DWORD terrainHeight = m_cellSpacing * m_cellsPerCol;


	if (FAILED(hr))
		return FALSE;

	INT startX = -(INT)terrainWidth / 2;
	INT startZ = (INT)terrainHeight / 2;
	INT endX = (INT)terrainWidth / 2;
	INT endZ = -(INT)terrainHeight / 2;

	FLOAT uUnitSizeTex = 1.0f / (FLOAT)m_cellsPerRow;
	FLOAT vUnitSizeTex = 1.0f / (FLOAT)m_cellsPerCol;

	TerrainVertex* v = nullptr;
	terrainMesh->LockVertexBuffer(0, (void**)&v);
	if (v == nullptr)
		return FALSE;

	INT curRow = 0;
	INT curCol = 0;
	INT curIndex = 0;
	for (int z = startZ; z >= endZ; z -= m_cellSpacing)
	{
		curCol = 0;
		for (int x = startX; x <= endX; x += m_cellSpacing)
		{
			curIndex = curRow * (m_cellsPerRow + 1) + curCol;
			v[curIndex] = TerrainVertex(
				(float)x,
				(float)m_terrainInfo.pthiHeights[curIndex],
				(float)z,
				(float)curCol * uUnitSizeTex,
				(float)curRow * vUnitSizeTex);
			curCol++; // next column
		}
		curRow++; // next row
	}

	terrainMesh->UnlockVertexBuffer();
	return TRUE;
}

//初始化索引
BOOL DTerrain::InitIndices(LPD3DXMESH terrainMesh)
{
	HRESULT hr = -1;


	DWORD baseIndex = 0;
	DWORD vertsPerRow = m_cellsPerRow + 1;
	
	VOID* indices = nullptr;
	terrainMesh->LockIndexBuffer(0, &indices);

	DWORD numVertices = (m_cellsPerRow + 1) * (m_cellsPerCol + 1);
	DWORD numTriangle = m_cellsPerRow * m_cellsPerCol * 2;

	if (numVertices > VERTEX16BIT || numTriangle > VERTEX16BIT)
	{
		for (DWORD i = 0; i < m_cellsPerCol; i++)
		{
			for (DWORD j = 0; j < m_cellsPerRow; j++)
			{
				((DWORD*)indices)[baseIndex] = (DWORD)(i   * vertsPerRow + j);
				((DWORD*)indices)[baseIndex + 1] = (DWORD)(i   * vertsPerRow + j + 1);
				((DWORD*)indices)[baseIndex + 2] = (DWORD)((i + 1) * vertsPerRow + j);

				((DWORD*)indices)[baseIndex + 3] = (DWORD)((i + 1) * vertsPerRow + j);
				((DWORD*)indices)[baseIndex + 4] = (DWORD)(i   * vertsPerRow + j + 1);
				((DWORD*)indices)[baseIndex + 5] = (DWORD)((i + 1) * vertsPerRow + j + 1);

				baseIndex += 6;
			}
		}
	}
	else
	{
		for (DWORD i = 0; i < m_cellsPerCol; i++)
		{
			for (DWORD j = 0; j < m_cellsPerRow; j++)
			{
				((WORD*)indices)[baseIndex] = (WORD)(i   * vertsPerRow + j);
				((WORD*)indices)[baseIndex + 1] = (WORD)(i   * vertsPerRow + j + 1);
				((WORD*)indices)[baseIndex + 2] = (WORD)((i + 1) * vertsPerRow + j);

				((WORD*)indices)[baseIndex + 3] = (WORD)((i + 1) * vertsPerRow + j);
				((WORD*)indices)[baseIndex + 4] = (WORD)(i   * vertsPerRow + j + 1);
				((WORD*)indices)[baseIndex + 5] = (WORD)((i + 1) * vertsPerRow + j + 1);

				baseIndex += 6;
			}
		}
	}
	
	terrainMesh->UnlockIndexBuffer();

	return TRUE;
}

BOOL DTerrain::InitTexture(DMeshRender* terrainMesh, LPCWSTR textureFilePath)
{
	HRESULT hr = 0;
	FLOAT terrainScale = m_terrainInfo.thiHeightScale;
	LPDIRECT3DTEXTURE9 pTexture = nullptr;
	if (textureFilePath == nullptr)
	{
		hr = D3DXCreateTexture(DDEInitialize::gRootDevice, m_cellsPerRow, m_cellsPerCol, 0, 0, D3DFMT_X8R8G8B8,
			D3DPOOL_MANAGED, &pTexture);
		if (FAILED(hr))
			return FALSE;

		D3DSURFACE_DESC	texDesc;
		pTexture->GetLevelDesc(0, &texDesc);
		if (texDesc.Format != D3DFMT_X8R8G8B8)
			return FALSE;

		D3DLOCKED_RECT lockedRect;
		pTexture->LockRect(0, &lockedRect, 0, 0);
		DWORD* pixData = (DWORD*)lockedRect.pBits;

		for (DWORD i = 0; i < m_cellsPerCol; i++)
		{
			for (DWORD j = 0; j < m_cellsPerRow; j++)
			{
				D3DXCOLOR c;

				float height = (float)GetTerrainVertHeight(i, j) * 1;

				//颜色设置策略待改
				if ((height) < 42.5f) 		 c = D3DCOLOR_XRGB(255, 249, 157);
				else if ((height) < 85.0f)	 c = D3DCOLOR_XRGB(124, 197, 118);
				else if ((height) < 127.5f) c = D3DCOLOR_XRGB(0, 166, 81);
				else if ((height) < 170.0f) c = D3DCOLOR_XRGB(25, 123, 48);
				else if ((height) < 212.5f) c = D3DCOLOR_XRGB(115, 100, 87);
				else	                     c = D3DCOLOR_XRGB(255, 255, 255);

				// fill locked data, note we divide the pitch by four because the
				// pitch is given in bytes and there are 4 bytes per DWORD.
				pixData[i * lockedRect.Pitch / 4 + j] = (D3DCOLOR)c;
			}
		}
		pTexture->UnlockRect(0);
		hr = D3DXFilterTexture(pTexture, 0, 0, D3DX_DEFAULT); // default filter
		if (FAILED(hr))
			return FALSE;
	}
	else
	{
		hr = D3DXCreateTextureFromFile(DDEInitialize::gRootDevice, textureFilePath, &pTexture);
		if (FAILED(hr))
			return FALSE;
	}
	DMaterialRender* matRender = terrainMesh->CreateMaterial();
	matRender->texture = pTexture;



	//DGameObject::g_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//DGameObject::g_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//DGameObject::g_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);


	return TRUE;
}

FLOAT DTerrain::GetTerrainHeight(FLOAT zPix, FLOAT xPix)
{
	FLOAT xCoord = xPix / m_cellSpacing;
	FLOAT zCoord = zPix / m_cellSpacing;
	xCoord += (m_cellsPerRow + 1) / 2.0f;
	zCoord = (m_cellsPerCol + 1) / 2.0f - zCoord;
	if (xCoord < 0 || zCoord < 0 || xCoord >= m_cellsPerRow || zCoord >= m_cellsPerCol)
		return 0;
	FLOAT xTmpCoord = ::floor(xCoord);				//向下取整，正整数下等价于 xCoord / 1 ；
	FLOAT zTmpCoord = ::floor(zCoord);				//向下取整，同上

	FLOAT aHeight = GetTerrainVertHeight((DWORD)zTmpCoord, (DWORD)xTmpCoord);
	FLOAT bHeight = GetTerrainVertHeight((DWORD)zTmpCoord + 1, (DWORD)xTmpCoord);
	FLOAT cHeight = GetTerrainVertHeight((DWORD)zTmpCoord, (DWORD)xTmpCoord + 1);
	FLOAT dHeight = GetTerrainVertHeight((DWORD)zTmpCoord + 1, (DWORD)xTmpCoord + 1);

	xTmpCoord = xCoord - xTmpCoord;
	zTmpCoord = zCoord - zTmpCoord;

	FLOAT terrainHeight = 0;
	FLOAT uy = 0;
	FLOAT vy = 0;
	if (xTmpCoord + zTmpCoord < 1.0f)
	{
		uy = bHeight - aHeight;		//向量AB
		vy = cHeight - aHeight;		//向量AC
		terrainHeight = aHeight + uy * xTmpCoord + vy * zTmpCoord;
	}
	else
	{
		uy = cHeight - dHeight;		//向量DC
		vy = bHeight - dHeight;		//向量DB
		terrainHeight = dHeight + uy * (1 - xTmpCoord) + vy * (1 - zTmpCoord);
	}
	return terrainHeight;
}

/*
功能：获取地形中某点的高度

参数：rowVert	该点所在行的行数
colVert	该点所在列的列数

返回值：返回高度值。
*/
FLOAT DTerrain::GetTerrainVertHeight(DWORD rowVert, DWORD colVert)
{
	if (m_terrainInfo.pthiHeights == nullptr)
		return -1;

	DWORD terrainIndex = rowVert * (m_cellsPerRow + 1) + colVert;

	if (terrainIndex < m_terrainInfo.thiVertsCount  && terrainIndex > 0)
		return m_terrainInfo.pthiHeights[terrainIndex];
	else
		return -1;
}

VOID DTerrain::InitEffect(DMeshRender* meshRender)
{
	RENDERSTATE rstate;
	rstate.rsRenderStateType = D3DRS_FILLMODE;
	rstate.rsValue = D3DFILL_SOLID;
	meshRender->AddRenderState(rstate);

	rstate.rsRenderStateType = D3DRS_CULLMODE;
	rstate.rsValue = D3DCULL_CCW;
	meshRender->AddRenderState(rstate);

	rstate.rsRenderStateType = D3DRS_LIGHTING;
	rstate.rsValue = FALSE;
	meshRender->AddRenderState(rstate);

	SAMPLERSTATE sstate;
	sstate.ssSampler = 0;
	sstate.ssSamplerStateType = D3DSAMP_MAGFILTER;
	sstate.ssValue = D3DTEXF_LINEAR;
	meshRender->AddSamplerState(sstate);

	sstate.ssSampler = 0;
	sstate.ssSamplerStateType = D3DSAMP_MINFILTER;
	sstate.ssValue = D3DTEXF_LINEAR;
	meshRender->AddSamplerState(sstate);

	sstate.ssSampler = 0;
	sstate.ssSamplerStateType = D3DSAMP_MIPFILTER;
	sstate.ssValue = D3DTEXF_LINEAR;
	meshRender->AddSamplerState(sstate);
}

BOOL  DTerrain::ReadRawFile(LPCWSTR terrainFilePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, terrainFilePath, L"r");
	if (pFile == nullptr)
		return FALSE;

	BYTE* pBuf;
	INT len = 0;
	INT curIndex = 0;

	fseek(pFile, 0, SEEK_END);
	len = ftell(pFile);
	pBuf = new BYTE[len];
	rewind(pFile);
	fread(pBuf, 1, len, pFile);
	fclose(pFile);

	int count = (m_cellsPerCol + 1) * (m_cellsPerRow + 1);
	m_terrainInfo.thiVertsCount = count;

	if (m_terrainInfo.pthiHeights == nullptr )
	{
		m_terrainInfo.pthiHeights = new FLOAT[count];
		ZeroMemory(m_terrainInfo.pthiHeights, count);

	}

	for (DWORD row = 0; row < m_cellsPerCol + 1; row++)
	{
		for (DWORD col = 0; col < m_cellsPerRow + 1; col++)
		{
			if (curIndex <= len)
				m_terrainInfo.pthiHeights[curIndex] = (FLOAT)pBuf[curIndex];
			else
				return TRUE;

			curIndex++;
		}
	}
	return TRUE;
}