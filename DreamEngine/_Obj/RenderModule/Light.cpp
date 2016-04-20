#include "Light.h"
#define LIGHTMAX 8

DLight::DLight()
{
}

DLight::~DLight()
{
}

VOID DLight::Run()
{
	DGameObject::Run();

	if (m_isNeedApply)
	{
		m_d3dDivce->SetLight(m_curIdx, m_lights[m_curIdx]);
		m_isNeedApply = FALSE;
	}
}

DWORD DLight::AddLight(D3DLIGHTTYPE lightType)
{
	D3DLIGHT9* tmpLight = new D3DLIGHT9;
	tmpLight->Type = lightType;
	m_lights.push_back(tmpLight);
	return 0;
}

BOOL DLight::DelLight(DWORD index)
{
	if (index < 0 || index >= LIGHTMAX)
		return FALSE;
	D3DLIGHT9* deleteLight = m_lights[index];
	if (deleteLight != nullptr)
	{
		delete deleteLight;
		if(index > 0 && m_curIdx <= LIGHTMAX)
			m_curIdx++;
		return TRUE;
	}
	return FALSE;
}

BOOL DLight::SetLightDiffuseColor(D3DCOLORVALUE color, BOOL isImmdApply)
{
	m_lights[m_curIdx]->Diffuse = color;
	return 0;
}

BOOL DLight::SetLightSpecularColor(D3DCOLORVALUE color, BOOL isImmdApply)
{
	m_lights[m_curIdx]->Specular = color;
	return 0;
}

BOOL DLight::SetLightAmbientColor(D3DCOLORVALUE color, BOOL isImmdApply)
{
	m_lights[m_curIdx]->Ambient = color;
	return 0;
}

BOOL DLight::SetLightRange(FLOAT range, BOOL isImmdApply)
{
	D3DLIGHTTYPE lightType = m_lights[m_curIdx]->Type;
	if (lightType == D3DLIGHT_DIRECTIONAL || lightType == D3DLIGHT_FORCE_DWORD)
		return FALSE;
	if (range < 0.0f)
		return FALSE;
	m_lights[m_curIdx]->Range = range;
	return TRUE;
}

BOOL DLight::SetLightAttenuation(FLOAT attenuation0, FLOAT attenuation1, FLOAT attenuation2, BOOL isImmdApply)
{
	D3DLIGHTTYPE lightType = m_lights[m_curIdx]->Type;
	if (lightType == D3DLIGHT_DIRECTIONAL || lightType == D3DLIGHT_FORCE_DWORD)
		return FALSE;
	m_lights[m_curIdx]->Attenuation0 = attenuation0;
	m_lights[m_curIdx]->Attenuation1 = attenuation1;
	m_lights[m_curIdx]->Attenuation2 = attenuation2;
	return TRUE;
}

BOOL DLight::SetLightAngle(FLOAT theta, FLOAT phi, BOOL isImmdApply)
{
	D3DLIGHTTYPE lightType = m_lights[m_curIdx]->Type;
	if (lightType == D3DLIGHT_SPOT)
	{
		m_lights[m_curIdx]->Theta = theta;
		m_lights[m_curIdx]->Phi = phi;
		return TRUE;
	}
	return FALSE;
}

BOOL DLight::SetLightFalloff(FLOAT falloff, BOOL isImmdApply)
{
	D3DLIGHTTYPE lightType = m_lights[m_curIdx]->Type;
	if (lightType == D3DLIGHT_SPOT)
	{
		m_lights[m_curIdx]->Falloff = falloff;
		return TRUE;
	}
	return FALSE;
}

BOOL DLight::SetLightPosition(float x, float y, float z, BOOL isImmdApply)
{
	D3DLIGHTTYPE lightType = m_lights[m_curIdx]->Type;
	if (lightType == D3DLIGHT_DIRECTIONAL || lightType == D3DLIGHT_FORCE_DWORD)
		return FALSE;
	m_lights[m_curIdx]->Position.x = x;
	m_lights[m_curIdx]->Position.y = y;
	m_lights[m_curIdx]->Position.z = z;
	return TRUE;
}

D3DLIGHTTYPE DLight::GetLightType(DWORD index)
{
	if (index < 0 || index >= LIGHTMAX)
		return (D3DLIGHTTYPE)0;

	D3DLIGHT9* light = m_lights[m_curIdx];
	if(light == nullptr) return (D3DLIGHTTYPE)0;

	return m_lights[m_curIdx]->Type;
}

VOID DLight::SetLightType(DWORD index, D3DLIGHTTYPE lightType)
{
	
}

DWORD DLight::GetLightCount()
{
	return m_lights.size();
}
