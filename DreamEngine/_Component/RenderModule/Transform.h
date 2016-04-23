#pragma once
#include "CommRenderHead.h"
//#include "BaseCom.h"

enum Space
{
	Local,
	World
};
class DTransform : public DBaseCom
{
public:
	DTransform(DGameObject* gameObj, DWORD indexInParent);
	DTransform(D3DXVECTOR3& pos, D3DXVECTOR3& rotation, D3DXVECTOR3& scale, DGameObject* gameObj, DWORD indexInParent, wstring comName = L"");
	~DTransform();

public:
	VOID Translate(D3DXVECTOR3 & translation, Space space);
	VOID Rotate(D3DXVECTOR3 & eulerAngles, Space space);
	VOID SetPosition(D3DXVECTOR3& pos);
	VOID SetRotation(D3DXVECTOR3 & eulerAngles);
	VOID SetScale(D3DXVECTOR3 & scale);

	VOID GetSelfFront(D3DXVECTOR3* vOut);
	VOID GetSelfUp(D3DXVECTOR3* vOut);
	VOID GetSelfRight(D3DXVECTOR3* vOut);
	VOID GetPosition(D3DXVECTOR3* pOut, Space space);
	VOID GetScale(D3DXVECTOR3 * sOut);
	VOID Run();

	VOID QuaternionToEuler(D3DXVECTOR3* vOut, D3DXQUATERNION* q);
private :
	VOID RotationEulerToQuaternion(D3DXQUATERNION * qOut, D3DXVECTOR3 & rotation);
	//VOID VectorEulerToQuaternion(D3DXVECTOR3* v, float euler, D3DXQUATERNION* q);

private:
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_scale;
	D3DXQUATERNION m_rQuat;		//存储旋转信息
	//D3DXVECTOR3 m_rotation;
	//D3DXMATRIX m_psMatrix;			//存贮位置和缩放信息
};
