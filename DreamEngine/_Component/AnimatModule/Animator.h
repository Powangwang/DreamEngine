#pragma once
#include "BaseCom.h"

class DAllocateHierarchyForXFile;
class DAnimator : public DBaseCom
{
public:
	DAnimator(DGameObject* gameObj, DWORD indexInParent);
	~DAnimator();
	BOOL LoadAnimatorFromXFile(LPCWSTR Filename, DWORD MeshOptions = 0);
	VOID Run();

private:
	VOID DrawFrame(LPD3DXFRAME pFrame);
	VOID DrawMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase);
	HRESULT SetupBoneMatrixPointers(LPD3DXFRAME pFrameBase, LPD3DXFRAME pFrameRoot);
	VOID UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
private:
	DAllocateHierarchyForXFile* m_hierarchyForX;
	LPD3DXFRAME m_pFrameRoot;
	LPD3DXANIMATIONCONTROLLER   m_pAnimController;
	DWORD m_prevTime;
	BOOL m_isRunFirst;
};
