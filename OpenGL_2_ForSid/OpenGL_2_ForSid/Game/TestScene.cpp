
// This Include
#include "TestScene.h"

// Inlcude the game classes
#include "GameClasses.h"
#include "Engine/Camera.h"
#include "Engine/AssetMgr.h"
#include "Engine/MeshComponent.h"

static CAssetMgr* p_Assets = CAssetMgr::GetInstance();


void CTestScene::ConfigurateScene()
{
	__super::ConfigurateScene();

	/** Scene Configuration */
	m_bScissorTest = true;


	/** Create Cubemap Object */
	


	/** Create Camera Object */

	CCamera* mainCamera = new CCamera();
	this->m_mainCamera = mainCamera;
	
	/** Create game objects in the scenes */

	std::shared_ptr<CCube> newCube = std::make_shared<CCube>();
	std::shared_ptr<CMeshComponent> meshRenderer = newCube->GetComponent<CMeshComponent>();
	meshRenderer->SetProgram(p_Assets->GetProgramID("BlinnPhongProgram"));
	meshRenderer->SetTexture(p_Assets->GetTexture("Box"));
	this->m_vGameObj.push_back(newCube);
}