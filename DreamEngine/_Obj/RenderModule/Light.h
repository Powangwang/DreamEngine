#pragma once
#include "GameObject.h"
#include <vector>
//#include <map>
//#include <string>
using namespace std;


class DLight : public DGameObject
{
public:
	DLight(D3DLIGHTTYPE lightType = D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL, BOOL lightEnabled = TRUE);
	~DLight();
	virtual VOID Run();
	virtual VOID Apply();
	BOOL LightEnabled(BOOL isEnabled);

	BOOL SetLightDiffuseColor(D3DCOLORVALUE & color);
	BOOL SetLightSpecularColor(D3DCOLORVALUE & color);
	BOOL SetLightAmbientColor(D3DCOLORVALUE & color);
	BOOL SetLightRange(FLOAT range);
	BOOL SetLightAttenuation(FLOAT attenuation0, FLOAT attenuation1, FLOAT attenuation2);
	BOOL SetLightAngle(FLOAT theta, FLOAT phi);
	BOOL SetLightFalloff(FLOAT falloff);
	BOOL SetLightPos(D3DXVECTOR3 & pos);
	BOOL SetLightDirect(D3DXVECTOR3 & rot);

	D3DLIGHTTYPE GetLightType();
	VOID  SetLightType(D3DLIGHTTYPE lightType);
	VOID GetLight(D3DLIGHT9* pOutLit, DWORD litIndex);


	static DWORD GetLightCount();

private:
	VOID AddLight(D3DLIGHTTYPE lightType, BOOL lightEnabled );

private:
	//map<string, D3DLIGHT9*> m_light;
	D3DLIGHT9 m_light;
	BOOL m_isNeedApply;		//true��ʾ��ǰ�����Ĺ��ղ���������Ҫ���£� false��ʾ��ǰ�����Ĺ��������µģ�����Ҫ����
	static DWORD g_lightCount;
};