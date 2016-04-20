#pragma once
//#include "../../_Component\RenderModule/CommRenderHead.h"
#include "../GameObject.h"

#define VIEW_ANGLE (0.5f)
#define VIEW_WIDTH 640
#define VIEW_HEIGHT 480

enum DISPLAYTYPE
{
	PerspectiveFovLH,
	OrthoLH,
	InvalidType
};

class Camera : public DGameObject
{
public:
	Camera();
	Camera(float viewAngle, float viewWidth, float viewHeight, DISPLAYTYPE displayType, float zn, float zf,
		D3DXVECTOR3& pos, D3DXVECTOR3& rotation, D3DXVECTOR3& scale);
	~Camera();
	BOOL BegineShowObject();
	BOOL EndShowObject();
	BOOL SetViewPort(const D3DVIEWPORT9* pViewPort);

public:
	VOID SetProjectAngle(float angle) { m_viewAngle = angle; SetCameraProjection(); }
	VOID SetProjectWidth(float width) { m_viewWidth = width; SetCameraProjection(); }
	VOID SetProjectHeight(float height) { m_viewHeight = height; SetCameraProjection();	}
	VOID SetCameraType(DISPLAYTYPE type) { m_displayType = type; SetCameraProjection(); }
	VOID SetCameraZn(FLOAT zn) { m_zn = zn; SetCameraProjection(); }
	VOID SetCameraZf(FLOAT zf) { m_zf = zf; SetCameraProjection(); }

	FLOAT GetProjectAngle() { return m_viewAngle; }
	FLOAT GetProjectWidth() { return m_viewWidth; }
	FLOAT GetProjectHeight() { return m_viewHeight; }
	DISPLAYTYPE GetCameraType() { return m_displayType; }
	FLOAT GetCameraZn() { return m_zn; }
	FLOAT GetCameraZf() { return m_zf; }

protected:
	BOOL SetCameraProjection();
	BOOL SetCameraView();
	VOID GetViewMatrix(D3DXMATRIX* viewMatrix);
public :
	virtual VOID Run();

private:
	BOOL m_isEnable;
	FLOAT m_viewAngle;
	FLOAT m_viewWidth;
	FLOAT m_viewHeight;
	DISPLAYTYPE m_displayType;
	FLOAT m_zn;
	FLOAT m_zf;
	//DTransform m_transform;
};
