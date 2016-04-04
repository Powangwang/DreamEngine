#include "Transform.h"

DTransform::DTransform()
{
	D3DXMatrixIdentity(&m_transMatrix);
}

DTransform::DTransform(D3DXVECTOR3* pos, D3DXVECTOR3* rotation, D3DXVECTOR3* scale)
{
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&m_transMatrix);

	D3DXMatrixRotationX(&matrix, rotation->x);
	m_transMatrix *= matrix;
	D3DXMatrixRotationY(&matrix, rotation->y);
	m_transMatrix *= matrix;
	D3DXMatrixRotationZ(&matrix, rotation->z);
	m_transMatrix *= matrix;

	D3DXMatrixTranslation(&matrix, pos->x, pos->y, pos->z);
	m_transMatrix *= matrix;
	D3DXMatrixScaling(&matrix, scale->x, scale->y, scale->z);
	m_transMatrix *= matrix;
}

DTransform::~DTransform()
{
}

BOOL DTransform::Translate(D3DXVECTOR3 * translation, Space space)
{
	D3DXMATRIX matrix;
	D3DXMatrixTranslation(&matrix, translation->x, translation->y, translation->z);
	m_transMatrix *= matrix;
	if (space == Local)
	{

	}
	return 0;
}

BOOL DTransform::Rotation(D3DXVECTOR3 * eulerAngles, Space space)
{
	return 0;
}
