#include "Transform.h"

DTransform::DTransform(DGameObject* gameObj, DWORD indexInParent):
	DBaseCom(L"", COMTYPE::DERenderTransform, gameObj, indexInParent)
{
	//D3DXMatrixIdentity(&m_transMatrix);
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;


	m_scale.x = 1.0f;
	m_scale.y = 1.0f;
	m_scale.z = 1.0f;
	D3DXQuaternionIdentity(&m_rQuat);
	//D3DXMatrixIdentity(&m_psMatrix);

}

DTransform::DTransform(D3DXVECTOR3& pos, D3DXVECTOR3& rotation, D3DXVECTOR3& scale,
													DGameObject* gameObj, DWORD indexInParent, wstring comName ):
	DBaseCom(comName, COMTYPE::DERenderTransform, gameObj, indexInParent)
{
	m_position = pos;
	m_scale = scale;
	RotationEulerToQuaternion(&m_rQuat, rotation);
	//D3DXMatrixIdentity(&m_psMatrix);

	//D3DXMATRIX matrix;
	//D3DXMatrixTranslation(&matrix, pos.x, pos.y, pos.z);
	//m_psMatrix *= matrix;
	//D3DXMatrixScaling(&matrix, scale.x, scale.y, scale.z);
	//m_psMatrix *= matrix;
}

DTransform::~DTransform()
{
}

VOID DTransform::Translate(D3DXVECTOR3 & translation, Space space)
{
	D3DXMATRIX rMatrix;
	D3DXMATRIX posMatrix;
	D3DXMatrixIdentity(&posMatrix);
	//D3DXMatrixTranslation(&matrix, translation.x, translation.y, translation.z);
	//m_psMatrix *= matrix;
	m_position += translation;
	if (space == Local)
	{
		posMatrix._41 = m_position.x;
		posMatrix._42 = m_position.y;
		posMatrix._43 = m_position.z;
		D3DXMatrixRotationQuaternion(&rMatrix, &m_rQuat);
		posMatrix *= rMatrix;
		m_position.x = posMatrix._41;
		m_position.y = posMatrix._42;
		m_position.z = posMatrix._43;
	}
}

VOID DTransform::Rotate(D3DXVECTOR3 & eulerAngles, Space space)
{
	D3DXQUATERNION rQuat;
	RotationEulerToQuaternion(&rQuat, eulerAngles);
	if (space == World)
	{
		D3DXMATRIX posMatrix;
		D3DXMATRIX rMatrix;
		D3DXMatrixRotationQuaternion(&posMatrix, &m_rQuat);
		D3DXMatrixRotationQuaternion(&rMatrix, &rQuat);
		//m_rQuat *= rQuat;
		posMatrix._41 = m_position.x;
		posMatrix._42 = m_position.y;
		posMatrix._43 = m_position.z;
		posMatrix *= rMatrix;

		m_position.x = posMatrix._41;
		m_position.y = posMatrix._42;
		m_position.z = posMatrix._43;

		posMatrix._41 = 0.0f;
		posMatrix._42 = 0.0f;
		posMatrix._43 = 0.0f;
		D3DXQuaternionRotationMatrix(&m_rQuat, &posMatrix);
	}
	else
	{
		m_rQuat = rQuat * m_rQuat;
	}
	D3DXQuaternionNormalize(&m_rQuat, &m_rQuat);
}

VOID DTransform::SetPosition(D3DXVECTOR3 & pos)
{
	m_position = pos;
}

VOID DTransform::SetRotation(D3DXVECTOR3 & eulerAngles)
{
	RotationEulerToQuaternion(&m_rQuat, eulerAngles);
}

VOID DTransform::SetScale(D3DXVECTOR3 & scale)
{
	m_scale = scale;
}

VOID DTransform::GetSelfFront(D3DXVECTOR3 * vOut)
{
	if (vOut == NULL)
		return;

	D3DXMATRIX rMatrix;
	D3DXMatrixRotationQuaternion(&rMatrix, &m_rQuat);
	D3DXVECTOR3 vFont(0, 0, 1);
	D3DXVec3TransformCoord(vOut, &vFont,&rMatrix);
}

VOID DTransform::GetSelfUp(D3DXVECTOR3 * vOut)
{
	if (vOut == NULL)
		return;

	D3DXMATRIX rMatrix;
	D3DXMatrixRotationQuaternion(&rMatrix, &m_rQuat);
	D3DXVECTOR3 vFont(0, 1, 0);
	D3DXVec3TransformCoord(vOut, &vFont, &rMatrix);
}

VOID DTransform::GetSelfRight(D3DXVECTOR3 * vOut)
{
	if (vOut == NULL)
		return;

	D3DXMATRIX rMatrix;
	D3DXMatrixRotationQuaternion(&rMatrix, &m_rQuat);
	D3DXVECTOR3 vFont(1, 0, 0);
	D3DXVec3TransformCoord(vOut, &vFont, &rMatrix);

}

//space.Local 表示为相对于父对象的位置，space.World 表示相对于世界坐标系的位置
VOID DTransform::GetPosition(D3DXVECTOR3 * pOut, Space space)
{
	if (pOut == NULL)
		return;

	//D3DXMATRIX rMatrix;
	//D3DXQUATERNION rQuat;
	if (space == World)
	{
		//D3DXQuaternionInverse(&rQuat, &m_rQuat);
		//D3DXMatrixRotationQuaternion(&rMatrix, &rQuat);
		//rMatrix = rMatrix * m_transMatrix;
		//pOut->x = rMatrix._41;
		//pOut->y = rMatrix._42;
		//pOut->z = rMatrix._43;
	}
	else
	{
		*pOut = m_position;
		//代码待加
	}
}

VOID DTransform::GetScale(D3DXVECTOR3 * sOut)
{
	if (sOut == NULL)
		return;
	*sOut = m_scale;

}

VOID DTransform::Run()
{
	if (m_d3dDivce == NULL)
		return;
	D3DXMATRIX tMatrix;
	D3DXMATRIX rMatrix;
	D3DXMatrixRotationQuaternion(&rMatrix, &m_rQuat);

	D3DXMatrixIdentity(&tMatrix);
	tMatrix._11 = m_scale.x;
	tMatrix._22 = m_scale.y;
	tMatrix._33 = m_scale.z;
	tMatrix._41 = m_position.x;
	tMatrix._42 = m_position.y;
	tMatrix._43 = m_position.z;
	tMatrix = rMatrix * tMatrix;
	m_d3dDivce->SetTransform(D3DTS_WORLD, &tMatrix);
}

VOID DTransform::RotationEulerToQuaternion(D3DXQUATERNION * qOut, D3DXVECTOR3 & rotation)
{
	if (qOut == NULL)
		return;

	D3DXVECTOR3 vX(1, 0, 0);
	D3DXVECTOR3 vY(0, 1, 0);
	D3DXVECTOR3 vZ(0, 0, 1);

	D3DXQUATERNION quatX(vX.x, vX.y, vX.z, rotation.x * D3DX_PI / 180.0f);
	D3DXQUATERNION quatY(vY.x, vY.y, vY.z, rotation.y * D3DX_PI / 180.0f);
	D3DXQUATERNION quatZ(vZ.x, vZ.y, vZ.z, rotation.z * D3DX_PI / 180.0f);

	*qOut = quatX * quatY * quatZ;
	
	D3DXQuaternionRotationYawPitchRoll(qOut, rotation.y, rotation.x, rotation.z);
	D3DXQuaternionNormalize(qOut, qOut);
}

//VOID DTransform::VectorEulerToQuaternion(D3DXVECTOR3 * v, float euler, D3DXQUATERNION * q)
//{
//	//w = cos(theta / 2)
//
//	//	x = ax * sin(theta / 2)
//
//	//	y = ay * sin(theta / 2)
//
//	//	z = az * sin(theta / 2)
//	//q->w = cos(euler * D3DX_PI / 180.0f );
//	//q->x = v->x * sin()
//}

VOID DTransform::QuaternionToEuler(D3DXVECTOR3* vOut, D3DXQUATERNION* q)
{
	double q0 = q->w;
	double q1 = q->x;
	double q2 = q->y;
	double q3 = q->z;

	vOut->x = float(atan2(2 * (q2*q3 + q0*q1), (q0*q0 - q1*q1 - q2*q2 + q3*q3)));
	vOut->y = float(asin(-2 * (q1*q3 - q0*q2)));
	vOut->z = float(atan2(2 * (q1*q2 + q0*q3), (q0*q0 + q1*q1 - q2*q2 - q3*q3)));
}