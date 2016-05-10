#include "GameObject.h"

DGameObject::DGameObject(GAMEOBJTYPE goType)
	:m_gameObjType(goType), m_parent(nullptr), m_isEnabled(TRUE)
{
	m_coms.push_back(new DTransform(this, m_coms.size()));
}

DGameObject::DGameObject(D3DXVECTOR3 & pos, D3DXVECTOR3 & rotation, D3DXVECTOR3 & scale, GAMEOBJTYPE goType)
{
	DGameObject(pos, rotation, scale, nullptr, GAMEOBJTYPE::GameObj);
}

DGameObject::DGameObject(D3DXVECTOR3 & pos, D3DXVECTOR3 & rotation, D3DXVECTOR3 & scale, DGameObject * parent)
{
	DGameObject(pos, rotation, scale, parent, GAMEOBJTYPE::GameObj);
}

DGameObject::DGameObject(D3DXVECTOR3 & pos, D3DXVECTOR3 & rotation, D3DXVECTOR3 & scale, DGameObject* parent, GAMEOBJTYPE goType)
	:m_gameObjType(goType), m_parent(parent), m_isEnabled(TRUE)
{
	m_coms.push_back(new DTransform(pos, rotation, scale, this, m_coms.size()));
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
	if (m_isEnabled == FALSE)
		return;

	int comCount = m_coms.size();
	for (int index = 0; index < comCount; index++)
	{
		DBaseCom* tmpCom = m_coms[index];
		if(tmpCom!= nullptr && tmpCom->GetEnabled())
			tmpCom->Run();
	}
}


DBaseCom* DGameObject::AddComponent(COMTYPE comType)
{
	DBaseCom* baseCom = nullptr;
	int comIndex = m_coms.size();
	switch (comType)
	{
	case DERenderUnkown:
		break;
	case DERenderTransform:
		baseCom = new DTransform(this, comIndex);
		break;
	case DERenderMesh:
		baseCom = new DMeshRender(this, comIndex);
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
