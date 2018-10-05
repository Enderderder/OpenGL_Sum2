#pragma once

// Global Include
#include "Utility.h"

// Forward Declare
class CMesh;
class CCamera;

class CCubeMap
{
public:
	CCubeMap();
	~CCubeMap();

	void RenderCubeMap(CCamera* _camera);

private:
	
	CMesh* m_cubemapMesh;
	GLuint m_texture;

};

