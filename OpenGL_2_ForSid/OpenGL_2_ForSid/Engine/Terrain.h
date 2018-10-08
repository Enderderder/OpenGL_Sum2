#pragma once

// Inherited Includes
#include "Component.h"

// Forward Declare
class CCamera;

struct HeightMapInfo
{
	std::wstring heightmapFilename;
	float heightScale = 1.0f;
	float heightOffset = 0.0f;
	UINT numRows;
	UINT numCols;
	float cellSpacing = 1.0f;
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

	/**
	 * Load the height map in using a RAW file
	 */
	void LoadHeightMap();

	/**
	* Smooth the height map using average function
	*/
	void SmoothHeightMap();

	/**
	 * Create the terrain shape using the loaded height map
	 */
	void CreateTerrain(HeightMapInfo& _info);

	/**
	 * Render function of the terrain
	 */
	void RenderTerrain(CCamera* _camera);

private:

	/**
	 * Check if the point is inside the height map
	 */
	bool InBounds(UINT i, UINT j);

	/**
	 * Compute the average element value of the point
	 */
	float Average(UINT i, UINT j);

private:

	HeightMapInfo m_hmInfo;

	UINT m_numVertices;
	UINT m_numFaces;

	std::vector<float> m_heightMap;

	GLuint m_vao;
	GLuint m_indiceCount;

	GLuint m_program;

};