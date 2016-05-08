#include"Camera.h"
//#include "../_CommAction/DEInitialize.h"
DCamera::DCamera() : DGameObject(),
	m_viewAngle(VIEW_ANGLE),
	m_viewWidth(VIEW_WIDTH), m_viewHeight(VIEW_HEIGHT),
	m_displayType(DISPLAYTYPE::PerspectiveFovLH), m_zn(0.1f), m_zf(1.0f)
{
	D3DXVECTOR3 pos(0, 0, -5.0f);
	GetTransform()->SetPosition(pos);
	if (!SetCameraProjection()) return ;
	if (!SetCameraView()) return ;
}
DCamera::DCamera(float viewAngle, float viewWidth, float viewHeight, DISPLAYTYPE displayType, float zn, float zf,
	D3DXVECTOR3 & pos, D3DXVECTOR3 & rotation):
	DGameObject(pos, rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f),GAMEOBJTYPE::GameObjCamera), 
	m_viewAngle(viewAngle), m_viewWidth(viewWidth), m_viewHeight(viewHeight),
	m_displayType(displayType),m_zn(zn),m_zf(zf)
{
	if (!SetCameraProjection()) return ;
	if (!SetCameraView()) return ;
}
DCamera::~DCamera()
{
}

BOOL DCamera::SetCameraProjection()
{
	if (!m_isEnabled)
		return FALSE;

	D3DXMATRIX projection;
	if (m_displayType == PerspectiveFovLH)
		D3DXMatrixPerspectiveFovLH(&projection, D3DX_PI * m_viewAngle, m_viewWidth / m_viewHeight, m_zn, m_zf);
	else if (m_displayType == OrthoLH)
		D3DXMatrixOrthoLH(&projection, m_viewWidth, m_viewHeight, 0.1f, 1000.0f);
	if (FAILED(DDEInitialize::gRootDevice->SetTransform(D3DTS_PROJECTION, &projection)))
		return FALSE;
	return TRUE;
}

BOOL DCamera::SetCameraView()
{
	if (!m_isEnabled)
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
	lookAt += pos;					//摄像机看向的坐标点
	D3DXMatrixLookAtLH(&viewMatrix, &pos, &lookAt, &lookUp);
	if (FAILED(DDEInitialize::gRootDevice->SetTransform(D3DTS_VIEW, &viewMatrix)))
		return FALSE;
	return TRUE;
}

VOID DCamera::GetViewMatrix(D3DXMATRIX* viewMatrix)
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

BOOL DCamera::BegineShowObject()
{
	if (!m_isEnabled)
		return FALSE;
	DDEInitialize::gRootDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	DDEInitialize::gRootDevice->BeginScene();
	return TRUE;
}
BOOL DCamera::EndShowObject()
{
	if (!m_isEnabled)
		return FALSE;
	DDEInitialize::gRootDevice->EndScene();
	DDEInitialize::gRootDevice->Present(NULL, NULL, NULL, NULL);
	return TRUE;
}

BOOL DCamera::SetViewPort(const D3DVIEWPORT9* pViewPort)
{
	DDEInitialize::gRootDevice->SetViewport(pViewPort);
	return TRUE;
}

VOID DCamera::Apply()
{
	if (m_isApply & APPLYTYPE::ApplyNone)
		return;
	if (m_isApply & APPLYTYPE::ApplyProject)
		SetCameraProjection();
	if (m_isApply & APPLYTYPE::ApplyView)
		SetCameraView();

	m_isApply = ApplyNone;

}

VOID DCamera::SetProjectAngle(float angle)
{
	m_viewAngle = angle; 
	m_isApply = ApplyProject; 
}

VOID DCamera::SetProjectWidth(float width)
{
	m_viewWidth = width; 
	m_isApply = ApplyProject;
}

VOID DCamera::SetProjectHeight(float height)
{
	m_viewHeight = height; 
	m_isApply = ApplyProject;
}

VOID DCamera::SetCameraType(DISPLAYTYPE type)
{
	m_displayType = type; 
	m_isApply = ApplyProject;
}

VOID DCamera::SetCameraZn(FLOAT zn)
{
	m_zn = zn; 
	m_isApply = ApplyProject;
}

VOID DCamera::SetCameraZf(FLOAT zf)
{
	m_zf = zf; 
	m_isApply = ApplyProject;
}

VOID DCamera::Run()
{
	if (m_isEnabled == FALSE)
		return;

	Apply();
}



