#include "GameObject.h"

DGameObject::DGameObject() 
	:m_parent(nullptr)
{
	m_d3dDivce = DDEInitialize::GetDevice();
	if (m_d3dDivce != nullptr)
		m_d3dDivce->AddRef();
	m_coms.push_back(new DTransform(this));
}

DGameObject::DGameObject(D3DXVECTOR3 & pos, D3DXVECTOR3 & rotation, D3DXVECTOR3 & scale, DGameObject* parent)
	:m_parent(parent)
{
	m_coms.push_back(new DTransform(pos, rotation, scale, this));
	if (m_d3dDivce != nullptr)
		m_d3dDivce->Release();
}

DGameObject::~DGameObject()
{
	int comCount = m_coms.size();
	for (int index = 0; index < comCount; index++)
		delete m_coms[index];
	m_coms.clear();
}

VOID DGameObject::Run()
{
	int comCount = m_coms.size();
	for (int index = 0; index < comCount; index++)
	{
		m_coms[index]->Run();
	}
}


DBaseCom* DGameObject::AddComponent(COMTYPE comType)
{
	DBaseCom* baseCom = nullptr;
	switch (comType)
	{
	case Unkown:
		break;
	case DERenderTransform:
		baseCom = new DTransform(this);
		break;
	case DERenderMesh:
		baseCom = new DMeshRender(this);
		break;
	default:
		break;
	}
	if (baseCom != nullptr)
		m_coms.push_back(baseCom);
	return baseCom;
}

DBaseCom * DGameObject::GetComponent(COMTYPE comType)
{
	int comCount = m_coms.size();
	for (int comIndex = 0; comIndex < comCount; comIndex++)
	{
		if (m_coms[comIndex]->GetComponentType() == comType)
			return m_coms[comIndex];
	}
	return nullptr;
}
