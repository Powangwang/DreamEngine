#pragma once
 #include<d3d9.h>
#include<d3dx9.h>
enum Space
{
	Local,
	World
};
class DTransform
{
public:
	DTransform();
	DTransform(D3DXVECTOR3* pos, D3DXVECTOR3* rotation, D3DXVECTOR3* scale);
	~DTransform();

public:
	BOOL Translate(D3DXVECTOR3* translation, Space space);
	BOOL Rotation(D3DXVECTOR3* eulerAngles, Space space);

private:
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_rotation;
	D3DXVECTOR3 m_scale;
	D3DXMATRIX m_transMatrix;
};
