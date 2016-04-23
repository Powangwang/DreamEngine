#pragma once
#include "../../_Component/CommComponent.h"
#include <vector>

class DGameObject
{
public :
	DGameObject();
	DGameObject(D3DXVECTOR3& pos, D3DXVECTOR3& rotation, D3DXVECTOR3& scale, DGameObject* parent = nullptr);
	~DGameObject();
public :
	virtual VOID Run() ;
	virtual VOID Apply() {}
	DTransform* GetTransform() { return (DTransform*)m_coms[0]; }
	DGameObject* GetParent() { return m_parent; }
	VOID SetEnabled(BOOL isEnable) { if (m_isEnabled == -1) return; m_isEnabled = isEnable; }
	BOOL GetEnabled() { return m_isEnabled; }

public :
	DBaseCom* AddComponent(COMTYPE comType);
	DBaseCom* GetComponent(COMTYPE comType);
protected:
	//DTransform transform;
	vector<DBaseCom*> m_coms;
	DGameObject* m_parent;
	LPDIRECT3DDEVICE9 m_d3dDivce;
	BOOL m_isEnabled;
};

