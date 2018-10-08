#pragma once

// Inherited Includes
#include "Component.h"

struct HeightMapInfo
{
	std::wstring heightmapFilename;
	float heightScale;
	float heightOffset;
	UINT numRows;
	UINT numCols;
	float cellSpacing;
};

struct TerrainVertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

class CTerrain : public CComponent
{

public:

	CTerrain();
	virtual ~CTerrain();

	virtual void BeginPlay() override;
	virtual void Update(float _tick);

	void LoadHeightMap();

	void SmoothHeightMap();

	void CreateTerrain(HeightMapInfo& _info);

	void RenderTerrain();

private:

	bool InBounds(UINT i, UINT j);

	float Average(UINT i, UINT j);

	//std::vector<GLfloat> CalculateTerrainVAO();


private:

	HeightMapInfo m_hmInfo;

	UINT m_numVertices;
	UINT m_numFaces;

	std::vector<float> m_heightMap;

	GLuint m_vao;
};