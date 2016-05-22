#include "MeshRender.h"


DMeshRender::DMeshRender(DGameObject* gameObj, DWORD indexInParent)
	:DBaseCom(L"", COMTYPE::DERenderMesh, gameObj, indexInParent),
	m_pMess(nullptr)
{
	//DMaterialRender * matRender = new DMaterialRender(gameObj, 0);
	//m_matRenders.push_back(matRender);
	//if (m_pMatRender != nullptr)
	//	m_pMatRender->SetMaterial();
}

DMeshRender::~DMeshRender()
{
	int matRenderCount = m_matRenders.size();
	for (int matRenderIndex = 0; matRenderIndex < matRenderCount; matRenderIndex++)
	{
		delete m_matRenders[matRenderIndex];
	}
	m_matRenders.clear();

	if(m_pMess != nullptr)
		m_pMess->Release();
}

BOOL DMeshRender::CreateMeshBox(D3DXVECTOR3 size)
{
	if (FAILED(D3DXCreateBox(DDEInitialize::gRootDevice, size.x, size.y, size.z, &m_pMess, nullptr)))
		return FALSE;
	CreateMaterial();
	//m_isEnabled = TRUE;
	return TRUE;
}

BOOL DMeshRender::CreateMeshSphere(FLOAT radius)
{
	if (FAILED(D3DXCreateSphere(DDEInitialize::gRootDevice, radius, 32, 32, &m_pMess, nullptr)))
		return FALSE;
	CreateMaterial();
	m_isEnabled = TRUE;
	return TRUE;
}

BOOL DMeshRender::CreateMeshTeapot()
{
	if (FAILED(D3DXCreateTeapot(DDEInitialize::gRootDevice, &m_pMess, nullptr)))
		return FALSE;
	CreateMaterial();
	m_isEnabled = TRUE;
	return TRUE;
}

BOOL DMeshRender::CreateMeshFromFileX(LPCWSTR pFileName, DWORD options)
{

	LPD3DXBUFFER ppAdjacency;
	LPD3DXBUFFER ppMaterials;
	LPD3DXBUFFER ppEffectInstances;
	DWORD NumMaterials;

	if (FAILED(D3DXLoadMeshFromX(pFileName, options, DDEInitialize::gRootDevice, 
		&ppAdjacency, &ppMaterials, &ppEffectInstances, &NumMaterials, &m_pMess)))
		return FALSE;

	D3DXMATERIAL *pMtrls = (D3DXMATERIAL*)ppMaterials->GetBufferPointer();
	LPDIRECT3DTEXTURE9 tmpTexture = nullptr;
	for (DWORD matRenderIndex = 0; matRenderIndex < NumMaterials; matRenderIndex++)
	{
		if (!FAILED(D3DXCreateTextureFromFileA(DDEInitialize::gRootDevice, pMtrls[matRenderIndex].pTextureFilename, &tmpTexture)))
		{
			DMaterialRender* matRender = new DMaterialRender(m_gameObj, 0, pMtrls[matRenderIndex].MatD3D, tmpTexture);
			m_matRenders.push_back(matRender);
		}
	}
	m_isEnabled = TRUE;
	return TRUE;
}

DMaterialRender* DMeshRender::CreateMaterial()
{
	DMaterialRender* matRender = new DMaterialRender(m_gameObj, m_matRenders.size());
	m_matRenders.push_back(matRender);
	return matRender;
}

VOID DMeshRender::Run()
{
	if (!m_isEnabled)
		return ;
	//DDEInitialize::gRootDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//DDEInitialize::gRootDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//DDEInitialize::gRootDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//DDEInitialize::gRootDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	ApplyRenderState();

	DWORD NumMaterials = m_matRenders.size();
	for (DWORD runIndex = 0; runIndex < NumMaterials; runIndex++)
	{
		m_matRenders[runIndex]->Run();
		m_pMess->DrawSubset(runIndex);
	}

	ApplyOrignRenderState();
}

DMaterialRender * DMeshRender::GetMaterialRender(DWORD matIndex)
{
	if (matIndex >= m_matRenders.size())
		return nullptr;

	return m_matRenders[matIndex];
}

LPD3DXMESH DMeshRender::GetMesh()
{
	return m_pMess;
}

VOID DMeshRender::SetMesh(LPD3DXMESH mess)
{
	m_pMess = mess;
}

VOID DMeshRender::AddRenderState(RENDERSTATE & renderState)
{
	DWORD value = 0;
	DDEInitialize::gRootDevice->GetRenderState(renderState.rsRenderStateType, &value);
	if (value == renderState.rsValue)
		return;
	
	m_renderStates.push_back(renderState);

	RENDERSTATE rstate;
	rstate.rsRenderStateType = renderState.rsRenderStateType;
	rstate.rsValue = value;
	m_orignRenderStates.push_back(rstate);
}
VOID DMeshRender::AddTextureSate(TEXTURESTATE & textureState)
{
	DWORD value = 0;
	DDEInitialize::gRootDevice->GetTextureStageState(textureState.tsStage, textureState.tsTextureStateType, &value);
	if (value == textureState.tsValue)
		return;

	m_textureStates.push_back(textureState);

	TEXTURESTATE tstate;
	tstate.tsStage = textureState.tsStage;
	tstate.tsTextureStateType = textureState.tsTextureStateType;
	tstate.tsValue = value;
	m_orignTextureStates.push_back(tstate);
}

VOID DMeshRender::AddSamplerState(SAMPLERSTATE & samplerState)
{
	DWORD value = 0;
	DDEInitialize::gRootDevice->GetSamplerState(samplerState.ssSampler, samplerState.ssSamplerStateType, &value);
	if (value == samplerState.ssValue)
		return;

	m_samplerStates.push_back(samplerState);

	SAMPLERSTATE sstate;
	sstate.ssSampler = samplerState.ssSampler;
	sstate.ssSamplerStateType = samplerState.ssSamplerStateType;
	sstate.ssValue = value;
	m_orignSamplerStates.push_back(sstate);
	
}

VOID DMeshRender::ApplyRenderState()
{
	for each (RENDERSTATE rstate in m_renderStates)
	{
		DDEInitialize::gRootDevice->SetRenderState(rstate.rsRenderStateType, rstate.rsValue);
	}
	for each (TEXTURESTATE tstate in m_textureStates)
	{
		DDEInitialize::gRootDevice->SetTextureStageState(tstate.tsStage, tstate.tsTextureStateType, tstate.tsValue);
	}
	for each (SAMPLERSTATE sstate in m_samplerStates)
	{
		DDEInitialize::gRootDevice->SetSamplerState(sstate.ssSampler, sstate.ssSamplerStateType, sstate.ssValue);
	}
}

VOID DMeshRender::ApplyOrignRenderState()
{
	for each (RENDERSTATE rstate in m_orignRenderStates)
	{
		DDEInitialize::gRootDevice->SetRenderState(rstate.rsRenderStateType, rstate.rsValue);
	}
	for each (TEXTURESTATE tstate in m_orignTextureStates)
	{
		DDEInitialize::gRootDevice->SetTextureStageState(tstate.tsStage, tstate.tsTextureStateType, tstate.tsValue);
	}
	for each (SAMPLERSTATE sstate in m_orignSamplerStates)
	{
		DDEInitialize::gRootDevice->SetSamplerState(sstate.ssSampler, sstate.ssSamplerStateType, sstate.ssValue);
	}
}


BOOL DMeshRender::DestroyMaterial(DWORD matIndex)
{
	DWORD matCount = m_matRenders.size();
	if (matIndex < 0 || matIndex >= matCount)
		return FALSE;

	vector<DMaterialRender*>::iterator iDel = m_matRenders.begin();
	m_matRenders.erase(iDel + matIndex);
	return TRUE;
}

VOID DMeshRender::DestroyMaterialAll()
{
	for (vector<DMaterialRender*>::iterator iDel = m_matRenders.begin(); iDel != m_matRenders.end(); iDel++)
	{
		delete *iDel;
	}
	m_matRenders.clear();
}


struct SkyboxVertex
{
	SkyboxVertex(float x, float y, float z)
	{
		_x = x; _y = y; _z = z;
	}
	float _x, _y, _z;

};

//BOOL DMeshRender::CreateMeshBox(D3DXVECTOR3 size)
//{
//	if (FAILED(D3DXCreateBox(DDEInitialize::gRootDevice, size.x, size.y, size.z, &m_pMess, nullptr)))
//		return FALSE;
//	CreateMaterial();
//	//m_isEnabled = TRUE;
//	return TRUE;
//}
BOOL DMeshRender::CreateBox()
{
	if (FAILED(D3DXCreateBox(DDEInitialize::gRootDevice, 1, 1, 1, &m_pMess, NULL)))
		return FALSE;

	CreateMaterial();
	//m_isEnabled = TRUE;
	if (FAILED(D3DXCreateMeshFVF(2, 4, D3DXMESH_32BIT, D3DFVF_XYZ, DDEInitialize::gRootDevice, &m_pMess)))
		return FALSE;
	SkyboxVertex* v = nullptr;
	m_pMess->LockVertexBuffer(0, (LPVOID*)&v);
	//v[0] = SkyboxVertex(-1.0f, 1.0f, 1.0f);
	//v[1] = SkyboxVertex(1.0f, 1.0f, 1.0f);
	//v[2] = SkyboxVertex(-1.0f, -1.0f, 1.0f);
	//v[3] = SkyboxVertex(1.0f, -1.0f, 1.0f);
	v[0] = SkyboxVertex(-1.0f, -1.0f, -1.0f);
	v[1] = SkyboxVertex(-1.0f, 1.0f, -1.0f);
	v[2] = SkyboxVertex(1.0f, 1.0f, -1.0f);
	v[3] = SkyboxVertex(1.0f, -1.0f, -1.0f);

	m_pMess->UnlockVertexBuffer();

	DWORD * i = nullptr;
	m_pMess->LockIndexBuffer(0, (LPVOID*)&i);
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;
	m_pMess->UnlockIndexBuffer();

	//WORD* i = 0;
	//m_pMess->LockIndexBuffer(0, (void**)&i);

	//// fill in the front face index data
	//i[0] = 0; i[1] = 1; i[2] = 2;
	//i[3] = 0; i[4] = 2; i[5] = 3;
	//m_pMess->UnlockIndexBuffer();



	RENDERSTATE rstate;
	rstate.rsRenderStateType = D3DRS_FILLMODE;
	rstate.rsValue = D3DFILL_SOLID;
	//rstate.rsValue = D3DFILL_WIREFRAME;
	AddRenderState(rstate);

	rstate.rsRenderStateType = D3DRS_CULLMODE;
	rstate.rsValue = D3DCULL_NONE;
	AddRenderState(rstate);

	rstate.rsRenderStateType = D3DRS_LIGHTING;
	rstate.rsValue = FALSE;
	AddRenderState(rstate);

	TEXTURESTATE tstate;
	tstate.tsStage = 0;
	tstate.tsTextureStateType = D3DTSS_COLOROP;
	tstate.tsValue = D3DTOP_SELECTARG1;
	AddTextureSate(tstate);		//将纹理颜色混合的第一个参数的颜色值用于输出

	tstate.tsStage = 0;
	tstate.tsTextureStateType = D3DTSS_COLORARG1;
	tstate.tsValue = D3DTA_TEXTURE;
	AddTextureSate(tstate);		//纹理颜色混合的第一个参数的值就取纹理颜色值

	return 0;
}

