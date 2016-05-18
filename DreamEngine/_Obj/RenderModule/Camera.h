#pragma once

#include "GameObject.h"

#define VIEW_ANGLE (0.5f)
#define VIEW_WIDTH 640
#define VIEW_HEIGHT 480

enum DISPLAYTYPE
{
	NoneType,
	PerspectiveFovLH,
	OrthoLH
};

class DCamera : public DGameObject
{
public:
	DCamera();
	DCamera(float viewAngle, float viewWidth, float viewHeight, DISPLAYTYPE displayType, float zn, float zf,
		D3DXVECTOR3& pos, D3DXVECTOR3& rotation);
	~DCamera();
	BOOL BegineShowObject();
	BOOL EndShowObject();
	BOOL SetViewPort(const D3DVIEWPORT9* pViewPort);

public:
	virtual VOID Run();

public:
	//VOID SetPostion(D3DXVECTOR3 & pos);
	//VOID SetRotation(D3DXVECTOR3 & rot);
	//VOID Translate

	VOID SetProjectAngle(float angle);
	VOID SetProjectWidth(float width);
	VOID SetProjectHeight(float height);
	VOID SetCameraType(DISPLAYTYPE type);
	VOID SetCameraZn(FLOAT zn);
	VOID SetCameraZf(FLOAT zf);

	FLOAT GetProjectAngle() { return m_viewAngle; }
	FLOAT GetProjectWidth() { return m_viewWidth; }
	FLOAT GetProjectHeight() { return m_viewHeight; }
	DISPLAYTYPE GetCameraType() { return m_displayType; }
	FLOAT GetCameraZn() { return m_zn; }
	FLOAT GetCameraZf() { return m_zf; }

private:
	BOOL SetCameraProjection();
	BOOL SetCameraView();
	VOID GetViewMatrix(D3DXMATRIX* viewMatrix);
	virtual VOID Apply();


public:
	friend class DTransform;
private:
	FLOAT m_viewAngle;
	FLOAT m_viewWidth;
	FLOAT m_viewHeight;
	DISPLAYTYPE m_displayType;
	FLOAT m_zn;
	FLOAT m_zf;
	enum APPLYTYPE
	{
		ApplyNone = 0x1,
		ApplyProject = 0x2,
		ApplyView = 0x4
	} m_isApply;		//当前更改了需要保存的类型
	//DTransform m_transform;
};
