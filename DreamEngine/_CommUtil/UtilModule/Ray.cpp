#include "Ray.h"

#include "RenderModule/Transform.h"
#include "RenderModule/MeshRender.h"
#include "GameObject.h"

DRay::DRay()
{
	D3DXVECTOR3 orignPos;
	D3DXVECTOR3 vector;
	ZeroMemory(&orignPos, sizeof(D3DXVECTOR3));
	ZeroMemory(&vector, sizeof(D3DXVECTOR3));
	InitRay(orignPos, vector);
}

DRay::DRay(D3DXVECTOR3 & orignPos, D3DXVECTOR3 & vector)
{
	InitRay(orignPos, vector);
}

DRay::~DRay()
{
}

BOOL DRay::RayHit(DGameObject * gameObj)
{
	if (gameObj == nullptr)
		return FALSE;
	DTransform * transf = gameObj->GetTransform();
	if (transf == nullptr)
		return FALSE;
	DMeshRender* meshRender = (DMeshRender*)gameObj->GetComponent(COMTYPE::DERenderMesh);
	if (meshRender == nullptr)
		return FALSE;
	LPD3DXMESH objMesh = meshRender->GetMesh();
	if (objMesh == nullptr)
		return FALSE;

	D3DXMATRIX tMatrix;
	transf->GetTransformMatrix(&tMatrix);
	D3DXMatrixInverse(&tMatrix, 0, &tMatrix);
	D3DXVec3TransformCoord(&m_orignPos, &m_orignPos, &tMatrix);
	D3DXVec3TransformNormal(&m_vector, &m_vector, &tMatrix);
	D3DXVec3Normalize(&m_vector, &m_vector);

	BOOL isHit = FALSE;
	D3DXIntersect(objMesh, &m_orignPos, &m_vector, &isHit, NULL, NULL, NULL, NULL, NULL, NULL);
	return isHit;
}

BOOL DRay::RayHit(DGameObject * gameObjs[], DWORD count)
{
	return 0;
}


VOID DRay::SetRayPosition(D3DXVECTOR3 & rayPos)
{
	m_orignPos = rayPos;
}

VOID DRay::GetRayPosition(D3DXVECTOR3 * pRayPosOut)
{
	if (pRayPosOut == nullptr)
		return;
	*pRayPosOut = m_orignPos;
}

VOID DRay::SetRayVector(D3DXVECTOR3 & rayVector)
{
	m_vector = rayVector;
}

VOID DRay::GetRayVector(D3DXVECTOR3 * pRayVectorOut)
{
	if (pRayVectorOut == nullptr)
		return;

	*pRayVectorOut == m_vector;
}

BOOL DRay::InitRay(D3DXVECTOR3 & orignPos, D3DXVECTOR3 & vector)
{
	m_orignPos = orignPos;
	m_vector = vector;
	return TRUE;
}
