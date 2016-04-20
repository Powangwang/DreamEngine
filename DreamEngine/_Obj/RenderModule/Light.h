#pragma once
#include "../GameObject.h"
#include <vector>
//#include <map>
//#include <string>
using namespace std;

#define WHITE D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
#define RED D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
#define GREEN D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)
#define BLUE D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)
#define BLACK D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f)

class DLight : public DGameObject
{
public:
	DLight();
	~DLight();
	VOID Run();
	DWORD AddLight(D3DLIGHTTYPE lightType = D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL);
	BOOL DelLight(DWORD index = -1);

	BOOL SetLightDiffuseColor(D3DCOLORVALUE color, BOOL isImmdApply = TRUE);
	BOOL SetLightSpecularColor(D3DCOLORVALUE color, BOOL isImmdApply = TRUE);
	BOOL SetLightAmbientColor(D3DCOLORVALUE color, BOOL isImmdApply = TRUE);
	BOOL SetLightRange(FLOAT range, BOOL isImmdApply = TRUE);
	BOOL SetLightAttenuation(FLOAT attenuation0, FLOAT attenuation1, FLOAT attenuation2, BOOL isImmdApply = TRUE);
	BOOL SetLightAngle(FLOAT theta, FLOAT phi, BOOL isImmdApply = TRUE);
	BOOL SetLightFalloff(FLOAT falloff, BOOL isImmdApply = TRUE);
	BOOL SetLightPosition(float x, float y, float z, BOOL isImmdApply = TRUE);

	VOID SetCurrentIndex(DWORD index) { Run(); m_curIdx = index; }
	DWORD GetCurrentIndex() { return m_curIdx; }
	D3DLIGHTTYPE GetLightType(DWORD index);
	VOID  SetLightType(DWORD index, D3DLIGHTTYPE lightType);
	DWORD GetLightCount();

private:
	//map<string, D3DLIGHT9*> m_lights;
	vector<D3DLIGHT9*> m_lights;
	DWORD m_curIdx;
	BOOL m_isNeedApply;		//true表示当前索引的光照不是最新需要更新， false表示当前索引的光照是最新的，不需要更新
};