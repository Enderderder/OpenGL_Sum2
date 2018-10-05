#ifndef SCENE_H
#define SCENE_H

// Global Include
#include "Utility.h"

// Forward Declaration
class CGameObject;
class CCamera;
class CCubeMap;
class CTextLabel;

class CScene
{
public:
	CScene();
	~CScene();

	virtual void InitailizeScene();
	void BeginPlay();
	void UpdateScene();
	void RenderScene();
	void ResetScene();

	//void CheckCollision();

	void Instantiate(CGameObject* _gameobj);
	void Instantiate(CGameObject* _gameobj, glm::vec3 _pos);
	void Instantiate(CGameObject* _gameobj, glm::vec3 _pos, glm::vec3 _scale, glm::vec3 _rotation);
	void DestroyObject(CGameObject* _gameobj);

	std::vector<CGameObject*> GetObjectVec() const;


public:

	std::string sceneName;

	/** Configuration */

	bool m_bScissorTest;

protected:
	
	CCamera* m_MainCamera;

	CCubeMap * m_cCubeMap;

	std::vector<CGameObject*> m_vGameObj;

private:



};

#endif // !SCENE_H