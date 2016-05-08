#include "Light.h"
#define LIGHTMAX 8

#define WHITE D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
#define RED D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
#define GREEN D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)
#define BLUE D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)
#define BLACK D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f)

DWORD DLight::g_lightCount = 0;

DLight::DLight(D3DLIGHTTYPE lightType, BOOL lightEnabled)
	:DGameObject(),m_isNeedApply(TRUE)
{
	DLight::g_lightCount++;
	if (DLight::g_lightCount > LIGHTMAX)
	{
		m_isEnabled = -1;
		return;
	}
	AddLight(lightType, lightEnabled);
}

DLight::~DLight()
{
	if(m_isEnabled != -1)
		DLight::g_lightCount --;
}

VOID DLight::Run()
{
	//DGameObject::Apply();
	if (m_isEnabled == FALSE)
		return;

	Apply();
}

VOID DLight::Apply()
{
	if (m_isEnabled == -1)
		return;

	if (m_isNeedApply)
	{
		DDEInitialize::gRootDevice->SetLight(DLight::g_lightCount, &m_light);
		m_isNeedApply = FALSE;
	}
}

//增加光照函数未完善
VOID DLight::AddLight(D3DLIGHTTYPE lightType, BOOL lightEnabled)
{
	m_light.Type = lightType;
	switch (lightType)
	{
	case D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL:
		SetLightDirect(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		break;
	case D3DLIGHTTYPE::D3DLIGHT_POINT:
		break;
	case D3DLIGHTTYPE::D3DLIGHT_SPOT:
		break;
	default:
		break;
	}
	SetLightDiffuseColor(WHITE);
	SetLightSpecularColor(WHITE);
	SetLightAmbientColor(WHITE); 

	if(lightEnabled == TRUE)
		LightEnabled(TRUE);
	m_isNeedApply = TRUE;
}

BOOL DLight::LightEnabled(BOOL isEnabled)
{
	if (m_isEnabled == -1)
		return FALSE;

	DDEInitialize::gRootDevice->LightEnable(DLight::g_lightCount, isEnabled);
	return TRUE;
}

BOOL DLight::SetLightDiffuseColor(D3DCOLORVALUE & color)
{
	m_light.Diffuse = color;

	m_isNeedApply = TRUE;
	return 0;
}

BOOL DLight::SetLightSpecularColor(D3DCOLORVALUE & color)
{
	m_light.Specular = color;

	m_isNeedApply = TRUE;
	DDEInitialize::gRootDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	return TRUE;
}

BOOL DLight::SetLightAmbientColor(D3DCOLORVALUE & color)
{
	m_light.Ambient = color;

	m_isNeedApply = TRUE;
	return TRUE;
}

BOOL DLight::SetLightRange(FLOAT range)
{
	D3DLIGHTTYPE lightType = m_light.Type;
	if (lightType == D3DLIGHT_DIRECTIONAL || lightType == D3DLIGHT_FORCE_DWORD)
		return FALSE;
	if (range < 0.0f)
		return FALSE;
	m_light.Range = range;

	m_isNeedApply = TRUE;
	return TRUE;
}

BOOL DLight::SetLightAttenuation(FLOAT attenuation0, FLOAT attenuation1, FLOAT attenuation2)
{
	D3DLIGHTTYPE lightType = m_light.Type;
	if (lightType == D3DLIGHT_DIRECTIONAL || lightType == D3DLIGHT_FORCE_DWORD)
		return FALSE;
	m_light.Attenuation0 = attenuation0;
	m_light.Attenuation1 = attenuation1;
	m_light.Attenuation2 = attenuation2;


	m_isNeedApply = TRUE;
	return TRUE;
}

BOOL DLight::SetLightAngle(FLOAT theta, FLOAT phi)
{
	D3DLIGHTTYPE lightType = m_light.Type;
	if (lightType != D3DLIGHT_SPOT)
		return FALSE;

	m_light.Theta = theta;
	m_light.Phi = phi;

	m_isNeedApply = TRUE;
	return TRUE;
}

BOOL DLight::SetLightFalloff(FLOAT falloff)
{
	D3DLIGHTTYPE lightType = m_light.Type;
	if (lightType != D3DLIGHT_SPOT)
		return FALSE;

	m_light.Falloff = falloff;
	
	m_isNeedApply = TRUE;
	return TRUE;
}

BOOL DLight::SetLightPos(D3DXVECTOR3 & pos)
{
	D3DLIGHTTYPE lightType = m_light.Type;
	if (lightType == D3DLIGHT_DIRECTIONAL || lightType == D3DLIGHT_FORCE_DWORD)
		return FALSE;
	GetTransform()->SetPosition(pos);
	m_light.Position.x = pos.x;
	m_light.Position.y = pos.y;
	m_light.Position.z = pos.z;

	m_isNeedApply = TRUE;
	return TRUE;
}

BOOL DLight::SetLightDirect(D3DXVECTOR3 & rot)
{
	D3DLIGHTTYPE lightType = m_light.Type;
	if (lightType != D3DLIGHT_DIRECTIONAL && lightType != D3DLIGHT_SPOT)
		return FALSE;

	DTransform* transform = GetTransform();
	if (transform == nullptr) return FALSE;
	D3DXVECTOR3 front;
	transform->SetRotation(rot);
	transform->GetSelfFront(&front);
	m_light.Direction= front;

	m_isNeedApply = TRUE;
	return TRUE;
}



D3DLIGHTTYPE DLight::GetLightType()
{
	return m_light.Type;
}

VOID DLight::SetLightType(D3DLIGHTTYPE lightType)
{
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	AddLight(lightType, TRUE);
}

DWORD DLight::GetLightCount()
{
	return DLight::g_lightCount;
}

VOID DLight::GetLight(D3DLIGHT9 * pOutLit, DWORD litIndex)
{
	if (pOutLit == nullptr)
		return;

	memcpy_s(pOutLit, sizeof(D3DLIGHT9), &m_light, sizeof(D3DLIGHT9));
}
