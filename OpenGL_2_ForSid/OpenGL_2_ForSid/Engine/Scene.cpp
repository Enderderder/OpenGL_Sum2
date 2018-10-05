// This Include
#include "Scene.h"

// Engine Include
#include "GameObject.h"
#include "SpriteRenderComponent.h"
#include "MeshComponent.h"

#include "Debug.h"
//#include "Player.h"
//#include "PowerUps.h"
//#include "AssetMgr.h"
//#include "MeshMgr.h"
//#include "ModelMgr.h"
//#include "SceneMgr.h"
//#include "Input.h"
//#include "Camera.h"
//#include "CAIMgr.h"
//#include "CubeMap.h"
//#include "TextLabel.h"

CScene::CScene()
{

	m_MainCamera = nullptr;
	m_cCubeMap = nullptr;
}

// CScene::CScene(ESCENES _eSceneNum)
// {}

CScene::~CScene()
{
	std::cout << "Cleaning Scene... \n";
	// Clean up the memory allocated variables inside the class
	// ========================================================
	delete m_MainCamera;
	m_cCubeMap = nullptr;

	for (auto obj : m_vGameObj)
	{
		delete obj;
	}
	m_vGameObj.clear();

	// ========================================================
	std::cout << "Cleaning Done... \n";
}

void CScene::InitailizeScene() { m_vGameObj.resize(0); }

void CScene::BeginPlay()
{
	for (auto obj : m_vGameObj)
	{
		obj->InitializeObject();
	}
}

void CScene::RenderScene()
{
	if (m_bScissorTest)
	{
		glEnable(GL_SCISSOR_TEST);
		glScissor(0, 100, 1366, 668);
	}

	glPolygonMode(GL_FRONT, GL_LINE);

	//m_cCubeMap->Render(m_MainCamera);

	if (!m_vGameObj.empty())
	{
		for (CGameObject* gameObject : m_vGameObj)
		{
			CSpriteRenderComponent* spriteRenderer
				= gameObject->GetComponent<CSpriteRenderComponent>();
			if (spriteRenderer)
			{
				spriteRenderer->Render(m_MainCamera);
				continue;
			}

			CMeshComponent* meshRenderer = gameObject->GetComponent<CMeshComponent>();
			if (meshRenderer)
			{
				meshRenderer->RenderMesh(m_MainCamera);
				continue;
			}
		}
	}

	glDisable(GL_SCISSOR_TEST);
	glPolygonMode(GL_FRONT, GL_FILL);
}

void CScene::ResetScene()
{
	for (auto obj : m_vGameObj)
	{
		delete obj;
	}
	m_vGameObj.clear();
}

void CScene::UpdateScene()
{
	//m_MainCamera->UpdateCamera();

	// Delete the object that should be deleted fron last frame
	for (auto obj : m_vGameObj)
	{
		if (obj->ShouldDestroyed()) { DestroyObject(obj); }
	}

	// Get each Object in the Scene and do their own Update Function
	size_t currVecSize = m_vGameObj.size();
	for (size_t index = 0; index < currVecSize; ++index)
	{
		m_vGameObj[index]->Update();
		currVecSize = m_vGameObj.size(); // Revalidate the number of item inside the vector
	}

	//CheckCollision();
}

/* Legacy code */
// void CScene::CheckCollision()
// {
// 	size_t currVecSize = m_vGameObj.size();
// 	for (size_t index = 0; index < currVecSize; ++index)
// 	{
// 		if (m_vGameObj[index]->HasCollider()) // Check if object itself has a collider
// 		{
// 			// Get the collistion detail of the object
// 			float selfCollider = m_vGameObj[index]->GetCollisionRad();
// 			glm::vec3 selfPos = m_vGameObj[index]->GetTransform();
// 
// 			// Check with all the rest of the other objects
// 			for (size_t i = index + 1; i < currVecSize; ++i)
// 			{
// 				if (m_vGameObj[i]->HasCollider())
// 				{
// 					// Get the other objects' collision detail
// 					float otherCollider = m_vGameObj[i]->GetCollisionRad();
// 					glm::vec3 otherPos = m_vGameObj[i]->GetTransform();
// 
// 					float distance = glm::distance(selfPos, otherPos);
// 					if (distance <= (selfCollider + otherCollider))
// 					{
// 						m_vGameObj[index]->OnCollision(m_vGameObj[i]);
// 						m_vGameObj[i]->OnCollision(m_vGameObj[index]);
// 					}
// 				}
// 			}
// 		}
// 		
// 
// 
// 		currVecSize = m_vGameObj.size(); // Revalidate the number of item inside the vector
// 	}
// }

void CScene::Instantiate(CGameObject * _gameobj)
{
	m_vGameObj.push_back(_gameobj);
}

void CScene::Instantiate(CGameObject * _gameobj, glm::vec3 _pos)
{
	_gameobj->m_transform.position = _pos;
	m_vGameObj.push_back(_gameobj);
}

void CScene::Instantiate(CGameObject * _gameobj, 
	glm::vec3 _pos, 
	glm::vec3 _rotation, 
	glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f))
{
	_gameobj->m_transform.position = _pos;
	_gameobj->m_transform.rotation = _rotation;
	_gameobj->m_transform.scale = _scale;
	m_vGameObj.push_back(_gameobj);
}

void CScene::DestroyObject(CGameObject* _gameobj)
{
	for (auto iter = m_vGameObj.begin(); iter != m_vGameObj.end(); ++iter)
	{
		if ((*iter) == _gameobj)
		{
			delete (*iter);
			m_vGameObj.erase(iter);
			break;
		}
	}
}

std::vector<CGameObject*> CScene::GetObjectVec() const
{
	return m_vGameObj;
}
