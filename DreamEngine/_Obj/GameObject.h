#pragma once
#include "CommComponent.h"
#include <vector>

enum GAMEOBJTYPE
{
	GameObj,
	GameObjCamera,
	GameObjLight,
	GameObjTerrain,
	GameObjSky
};

class DGameObject
{
public :
	DGameObject(GAMEOBJTYPE goType = GAMEOBJTYPE::GameObj);
	DGameObject(D3DXVECTOR3& pos, D3DXVECTOR3& rotation, D3DXVECTOR3& scale, GAMEOBJTYPE goType = GAMEOBJTYPE::GameObj);

	DGameObject(D3DXVECTOR3& pos, D3DXVECTOR3& rotation, D3DXVECTOR3& scale, DGameObject* parent = nullptr);

	DGameObject(D3DXVECTOR3& pos, D3DXVECTOR3& rotation, D3DXVECTOR3& scale, DGameObject* parent, GAMEOBJTYPE goType);
	~DGameObject();
public :
	virtual VOID Run() ;
	DTransform* GetTransform() { return (DTransform*)m_coms[0]; }
	DGameObject* GetParent() { return m_parent; }
	VOID SetEnabled(BOOL isEnable) { if (m_isEnabled == -1) return; m_isEnabled = isEnable; }
	BOOL GetEnabled() { return m_isEnabled; }
	GAMEOBJTYPE GetType() { return m_gameObjType; }

public :
	DBaseCom* AddComponent(COMTYPE comType);
	DBaseCom* GetComponent(COMTYPE comType);

private:
	VOID InitGameObject(D3DXVECTOR3& pos, D3DXVECTOR3& rotation, D3DXVECTOR3& scale, DGameObject* parent, GAMEOBJTYPE goType);
	virtual VOID Apply() {}

protected:
	//DTransform transform;
	vector<DBaseCom*> m_coms;
	DGameObject* m_parent;
	BOOL m_isEnabled;
	GAMEOBJTYPE m_gameObjType;
};

