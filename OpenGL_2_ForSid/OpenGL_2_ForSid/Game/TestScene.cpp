
// This Include
#include "TestScene.h"

// Inlcude the game classes
#include "GameClasses.h"
#include "Engine/Camera.h"
#include "Engine/AssetMgr.h"
#include "Engine/MeshComponent.h"

static CAssetMgr* p_Assets = CAssetMgr::GetInstance();


void CTestScene::InitailizeScene()
{
	__super::InitailizeScene();

	/** Scene Configuration */
	m_bScissorTest = true;


	/** Create Cubemap Object */
	


	/** Create Camera Object */

	CCamera* CameraObject = new CCamera();
	CameraObject->m_name = "Main Camera";
	CameraObject->m_transform.position = glm::vec3(0.0f, 0.0f, 30.0f);
	CameraObject->m_bIsControlling = true;

	this->m_vGameObj.push_back(CameraObject);

	this->m_MainCamera = CameraObject;
	
	/** Create game objects in the scenes */

	CCube* newCube = new CCube();
	CMeshComponent* meshRenderer = newCube->GetComponent<CMeshComponent>();
	meshRenderer->SetProgram(p_Assets->GetProgramID("BlinnPhongProgram"));
	meshRenderer->SetTexture(p_Assets->GetTexture("Box"));
	this->m_vGameObj.push_back(newCube);

}