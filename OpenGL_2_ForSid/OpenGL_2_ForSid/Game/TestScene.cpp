
// This Include
#include "TestScene.h"

// Inlcude the game classes
#include "GameClasses.h"
#include "Engine/Camera.h"
#include "Engine/AssetMgr.h"
#include "Engine/MeshComponent.h"
#include "Engine/CubeMap.h"
#include "Engine/Terrain.h"

static CAssetMgr* p_Assets = CAssetMgr::GetInstance();

void CTestScene::ConfigurateScene()
{
	__super::ConfigurateScene();

	/** Scene Configuration */
	m_bScissorTest = false;


	/** Create Cubemap Object */
	m_cubeMap = CAssetMgr::GetInstance()->GetCubeMap("DefaultCubeMap");


	/** Create Camera Object */

	CCamera* mainCamera = new CCamera();
	this->m_mainCamera = mainCamera;
	
	/** Create game objects in the scenes */

	std::shared_ptr<CGameObject> terrain = std::make_shared<CGameObject>();
	std::shared_ptr<CTerrain> terrainRenderer = terrain->CreateComponent<CTerrain>();
	HeightMapInfo heightMap;
	heightMap.heightmapFilename = util::stringToWstring("Resources/HeightMaps/HeightMap3.data");
	heightMap.numRows = 200;
	heightMap.numCols = 200;
	terrainRenderer->CreateTerrain(heightMap);
	//std::shared_ptr<CTerrain> terrainRenderer = terrain->GetComponent<CMeshComponent>();
	//terrainRenderer->SetProgram(p_Assets->GetProgramID("BlinnPhongProgram"));
	//terrainRenderer->SetTexture(p_Assets->GetTexture("Box"));
	this->m_vGameObj.push_back(terrain);
}

