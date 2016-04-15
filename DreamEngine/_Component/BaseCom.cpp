#include "BaseCom.h"
#include "../_CommAction/DEInitialize.h"

DBaseCom::DBaseCom(wstring comName, COMTYPE type, DGameObject* gameObj)
	:m_comName(comName), m_comType(type), m_gameObj(gameObj)
{
	m_d3dDivce = DDEInitialize::GetDevice();
	if (m_d3dDivce != NULL)
		m_d3dDivce->AddRef();
}

DBaseCom::~DBaseCom()
{
	if (m_d3dDivce != NULL)
		m_d3dDivce->Release();
}

COMTYPE DBaseCom::GetComponentType()
{
	return m_comType;
}
