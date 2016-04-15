#include"Camera.h"
//#include "../_CommAction/DEInitialize.h"
Camera::Camera() : DGameObject()
{
	m_isEnable = TRUE;	

	m_viewAngle = VIEW_ANGLE;
	m_viewWidth = VIEW_WIDTH;
	m_viewHeight = VIEW_HEIGHT;

	m_displayType = PerspectiveFovLH;
	m_zn = 0.1f;
	m_zf = 1.0f;
	D3DXVECTOR3 pos(0, 0, -5.0f);
	GetTransform()->SetPosition(pos);
	if (!SetCameraProjection()) return ;
	if (!SetCameraView()) return ;
}
Camera::Camera(float viewAngle, float viewWidth, float viewHeight, DISPLAYTYPE displayType, float zn, float zf,
	D3DXVECTOR3 & pos, D3DXVECTOR3 & rotation, D3DXVECTOR3 & scale):
	DGameObject(pos, rotation, scale), 
	m_viewAngle(viewAngle), m_viewWidth(viewWidth), m_viewHeight(viewHeight),
	m_displayType(displayType),m_zn(zn),m_zf(zf)
{
	m_isEnable = TRUE;
	if (!SetCameraProjection()) return ;
	if (!SetCameraView()) return ;
}
Camera::~Camera()
{
}

BOOL Camera::SetCameraProjection()
{
	if (!m_isEnable)
		return FALSE;

	D3DXMATRIX projection;
	if (m_displayType == PerspectiveFovLH)
		D3DXMatrixPerspectiveFovLH(&projection, D3DX_PI * m_viewAngle, m_viewWidth / m_viewHeight, m_zn, m_zf);
	else if (m_displayType == OrthoLH)
		D3DXMatrixOrthoLH(&projection, m_viewWidth, m_viewHeight, 0.1f, 1000.0f);
	if (FAILED(DDEInitialize::GetDevice()->SetTransform(D3DTS_PROJECTION, &projection)))
		return FALSE;
	return TRUE;
}

BOOL Camera::SetCameraView()
{
	if (!m_isEnable)
		return FALSE;

	// Build view matrix.
	D3DXMATRIX viewMatrix;
	D3DXVECTOR3 lookUp;
	D3DXVECTOR3 lookAt ;
	D3DXVECTOR3 pos;
	DTransform* transform = (DTransform*)GetComponent(COMTYPE::DERenderTransform);
	if (transform == nullptr)
		return FALSE;
	transform->GetPosition(&pos, Space::Local);
	transform->GetSelfFront(&lookAt);
	transform->GetSelfUp(&lookUp);
	D3DXMatrixLookAtLH(&viewMatrix, &pos, &lookAt, &lookUp);
	if (FAILED(DDEInitialize::GetDevice()->SetTransform(D3DTS_VIEW, &viewMatrix)))
		return FALSE;
	return TRUE;
}

VOID Camera::GetViewMatrix(D3DXMATRIX* viewMatrix)
{
	if (viewMatrix == nullptr)
		return;
	DTransform* transform = (DTransform*)GetComponent(COMTYPE::DERenderTransform);
	if (transform == nullptr)
		return ;

	//D3DXMATRIX rMatrix;
	//D3DXQUATERNION rQuat;
	//D3DXQuaternionInverse(&rQuat, &transform->m_rQuat);
	//D3DXMatrixRotationQuaternion(&rMatrix, &rQuat);
}

BOOL Camera::BegineShowObject()
{
	if (!m_isEnable)
		return FALSE;
	DDEInitialize::GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(60, 150, 150), 1.0f, 0);
	DDEInitialize::GetDevice()->BeginScene();
	return TRUE;
}
BOOL Camera::EndShowObject()
{
	if (!m_isEnable)
		return FALSE;
	DDEInitialize::GetDevice()->EndScene();
	DDEInitialize::GetDevice()->Present(NULL, NULL, NULL, NULL);
	return TRUE;
}

BOOL Camera::SetViewPort(const D3DVIEWPORT9* pViewPort)
{
	DDEInitialize::GetDevice()->SetViewport(pViewPort);
	return TRUE;
}

VOID Camera::Run()
{
	return VOID();
}



