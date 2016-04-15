#pragma once
#include "../_Component/RenderModule/CommRenderHead.h"
#include <vector>

class DGameObject
{
public :
	DGameObject();
	DGameObject(D3DXVECTOR3& pos, D3DXVECTOR3& rotation, D3DXVECTOR3& scale, DGameObject* parent = nullptr);
	~DGameObject();
public :
	virtual VOID Run() ;
	DTransform* GetTransform() { return (DTransform*)m_coms[0]; }
	DGameObject* GetParent() { return m_parent; }
public :
	DBaseCom* AddComponent(COMTYPE comType);
	DBaseCom* GetComponent(COMTYPE comType);
protected:
	//DTransform transform;
	vector<DBaseCom*> m_coms;
	DGameObject* m_parent;
};

