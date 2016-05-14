#include "BaseCom.h"
#include "../_CommUtil/DEInitialize.h"

DBaseCom::DBaseCom(wstring comName, COMTYPE type, DGameObject* gameObj, DWORD indexInParent)
	:m_comName(comName), m_comType(type), m_gameObj(gameObj), m_indexInParent(indexInParent),
	m_isEnabled(TRUE)
{
}

DBaseCom::~DBaseCom()
{
}


COMTYPE DBaseCom::GetComponentType()
{
	return m_comType;
}
