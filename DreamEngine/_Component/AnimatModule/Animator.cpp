#include "Animator.h"
#include "AllocateHierarchy.h"
#include "FrameModule/DEInitialize.h"
#include "GameObject.h"

DAnimator::DAnimator(DGameObject* gameObj, DWORD indexInParent)
	:DBaseCom(L"", COMTYPE::DEAnimator, gameObj, indexInParent),
	m_hierarchyForX(nullptr), m_pFrameRoot(nullptr), m_pAnimController(nullptr),
	m_prevTime(0), m_isRunFirst(TRUE)
{

}

DAnimator::~DAnimator()
{
	if (m_hierarchyForX != nullptr)
		delete m_hierarchyForX;

	if (m_pAnimController != nullptr)
		m_pAnimController ->Release();

	if (m_pFrameRoot != nullptr)
		delete m_pFrameRoot;
}

BOOL DAnimator::LoadAnimatorFromXFile(LPCWSTR Filename, DWORD MeshOptions)
{
	wstring filePath;
	DString::GetFilePath(Filename, &filePath);
	m_hierarchyForX = new DAllocateHierarchyForXFile(filePath.data());
	D3DXLoadMeshHierarchyFromX(Filename, MeshOptions, DDEInitialize::gRootDevice,
		m_hierarchyForX, NULL, &m_pFrameRoot, &m_pAnimController);
	SetupBoneMatrixPointers(m_pFrameRoot, m_pFrameRoot);
	return TRUE;
}

VOID DAnimator::Run()
{
	if (m_isRunFirst)
	{
		m_isRunFirst = FALSE;
		m_prevTime = ::GetTickCount();
	}

	DWORD currTime = ::GetTickCount();
	DOUBLE deltaTime = (currTime - m_prevTime) / 1000.0;
	m_prevTime = currTime;
	D3DXMATRIX matFinal;
	m_gameObj->GetTransform()->GetTransformMatrix(&matFinal);

	m_pAnimController->AdvanceTime(deltaTime, NULL);  //设置骨骼动画的时间
	UpdateFrameMatrices(m_pFrameRoot, &matFinal);   //更新框架中的变换矩阵
	DrawFrame(m_pFrameRoot);
	
}

VOID DAnimator::DrawFrame(LPD3DXFRAME pFrame)
{
	if (pFrame == NULL) return;
	LPD3DXMESHCONTAINER pMeshContainer;
	pMeshContainer = pFrame->pMeshContainer;                    // 取得网格容器
	while (pMeshContainer != NULL)
	{
		DrawMeshContainer(pMeshContainer, pFrame);  // 绘制非空蒙皮网格
		pMeshContainer = pMeshContainer->pNextMeshContainer;    // 遍历所有网格容器
	}

	DrawFrame(pFrame->pFrameSibling);               // 绘制兄弟框架
	DrawFrame(pFrame->pFrameFirstChild);            // 绘制子框架
}

VOID DAnimator::DrawMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase)
{
	D3DXMESHCONTAINERFORXFILE* pMeshContainer = (D3DXMESHCONTAINERFORXFILE*)pMeshContainerBase;
	D3DXFRAMEFORXFILE* pFrame = (D3DXFRAMEFORXFILE*)pFrameBase;
	UINT iMaterial;
	UINT NumBlend;
	UINT iAttrib;
	DWORD AttribIdPrev;
	LPD3DXBONECOMBINATION pBoneComb;

	UINT iMatrixIndex;
	D3DXMATRIXA16 matTemp;
	D3DCAPS9 d3dCaps;
	LPDIRECT3DDEVICE9 rootDevice = DDEInitialize::gRootDevice;
	if (rootDevice == nullptr)
		return;

	rootDevice->GetDeviceCaps(&d3dCaps);

	// first check for skinning
	if (pMeshContainer->pSkinInfo != NULL)
	{
		AttribIdPrev = UNUSED32;
		pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());

		// Draw using default vtx processing of the device (typically HW)
		for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
		{
			NumBlend = 0;
			for (DWORD i = 0; i < pMeshContainer->NumInfl; ++i)
			{
				if (pBoneComb[iAttrib].BoneId[i] != UINT_MAX)
				{
					NumBlend = i;
				}
			}

			if (d3dCaps.MaxVertexBlendMatrices >= NumBlend + 1)
			{
				// first calculate the world matrices for the current set of blend weights and get the accurate count of the number of blends
				for (DWORD i = 0; i < pMeshContainer->NumInfl; ++i)
				{
					iMatrixIndex = pBoneComb[iAttrib].BoneId[i];
					if (iMatrixIndex != UINT_MAX)
					{
						D3DXMatrixMultiply(&matTemp, &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
							pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]);
						rootDevice->SetTransform(D3DTS_WORLDMATRIX(i), &matTemp);
					}
				}

				rootDevice->SetRenderState(D3DRS_VERTEXBLEND, NumBlend);

				// lookup the material used for this subset of faces
				if ((AttribIdPrev != pBoneComb[iAttrib].AttribId) || (AttribIdPrev == UNUSED32))
				{
					rootDevice->SetMaterial(&pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D);
					rootDevice->SetTexture(0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId]);
					AttribIdPrev = pBoneComb[iAttrib].AttribId;
				}

				// draw the subset now that the correct material and matrices are loaded
				pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
			}
		}
		rootDevice->SetRenderState(D3DRS_VERTEXBLEND, 0);
	}
	else  // standard mesh, just draw it after setting material properties
	{
		rootDevice->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);

		for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
		{
			rootDevice->SetMaterial(&pMeshContainer->pMaterials[iMaterial].MatD3D);
			rootDevice->SetTexture(0, pMeshContainer->ppTextures[iMaterial]);
			pMeshContainer->MeshData.pMesh->DrawSubset(iMaterial);
		}
	}
}

HRESULT DAnimator::SetupBoneMatrixPointers(LPD3DXFRAME pFrameBase, LPD3DXFRAME pFrameRoot)
{
	if (pFrameBase->pMeshContainer != NULL)
	{
		D3DXFRAMEFORXFILE* pFrame = NULL;
		D3DXMESHCONTAINERFORXFILE* pMeshContainer = (D3DXMESHCONTAINERFORXFILE*)pFrameBase->pMeshContainer;

		// if there is a skinmesh, then setup the bone matrices
		if (pMeshContainer->pSkinInfo != NULL)
		{
			UINT cBones = pMeshContainer->pSkinInfo->GetNumBones();
			pMeshContainer->ppBoneMatrixPtrs = new D3DXMATRIX*[cBones];
			for (UINT iBone = 0; iBone < cBones; iBone++)
			{
				pFrame = (D3DXFRAMEFORXFILE*)D3DXFrameFind(pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(iBone));
				if (pFrame == NULL) return E_FAIL;

				pMeshContainer->ppBoneMatrixPtrs[iBone] = &pFrame->CombinedTransformationMatrix;
			}
		}
	}

	if (pFrameBase->pFrameSibling != NULL)
	{
		if (FAILED(SetupBoneMatrixPointers(pFrameBase->pFrameSibling, pFrameRoot)))
			return E_FAIL;
	}

	if (pFrameBase->pFrameFirstChild != NULL)
	{
		if (FAILED(SetupBoneMatrixPointers(pFrameBase->pFrameFirstChild, pFrameRoot)))
			return E_FAIL;
	}

	return S_OK;
}

VOID DAnimator::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	if (pFrameBase == NULL || pParentMatrix == NULL) return;
	D3DXFRAMEFORXFILE* pFrame = (D3DXFRAMEFORXFILE*)pFrameBase;

	// 将当前骨骼的相对于父骨骼的偏移矩阵作累积运算
	D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);

	UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);                              // 更新兄弟骨骼
	UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);   // 更新子骨骼
}
