#pragma once
#include<d3d9.h>
#include<d3dx9.h>

class DGameObject;
class DRay
{
public:
	DRay();
	DRay(D3DXVECTOR3 & orignPos, D3DXVECTOR3 & vector);
	~DRay();
	BOOL RayHit(DGameObject * gameObj);
	BOOL RayHit(DGameObject * gameObjs[], DWORD count);
public:
	VOID SetRayPosition(D3DXVECTOR3 & rayPos);
	VOID GetRayPosition(D3DXVECTOR3 * pRayPosOut);
	VOID SetRayVector(D3DXVECTOR3 & rayVector);
	VOID GetRayVector(D3DXVECTOR3 * pRayVectorOut);

private:
	BOOL InitRay(D3DXVECTOR3 & orignPos, D3DXVECTOR3 & vector);
private:
	D3DXVECTOR3 m_orignPos;
	D3DXVECTOR3 m_vector;
};
