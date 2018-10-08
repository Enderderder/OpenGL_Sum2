
// This Include
#include "Terrain.h"

CTerrain::CTerrain()
{}

CTerrain::~CTerrain()
{}

void CTerrain::BeginPlay()
{
	__super::BeginPlay();
	
}

void CTerrain::Update(float _tick)
{
	__super::Update(_tick);
	
}

void CTerrain::LoadHeightMap()
{
	// A height for each vertex
	std::vector<unsigned char> in(m_hmInfo.numRows * m_hmInfo.numCols);

	// Open the height map file
	std::ifstream inFile;
	inFile.open(m_hmInfo.heightmapFilename.c_str(), std::ios_base::binary);

	if (inFile)
	{
		// Read the RAW bytes
		inFile.read((char*)&in[0], (std::streamsize)in.size());

		// Done with file.
		inFile.close();
	}

	// Copy the array data into a float array, and scale and offset the heights.
	m_heightMap.resize(m_hmInfo.numRows * m_hmInfo.numCols, 0);
	for (UINT i = 0; i < m_hmInfo.numRows * m_hmInfo.numCols; ++i)
	{
		m_heightMap[i] = (float)in[i] * m_hmInfo.heightScale + m_hmInfo.heightOffset;
	}
}

void CTerrain::SmoothHeightMap()
{
	std::vector<float> dest(m_heightMap.size());

	for (UINT i = 0; i < m_hmInfo.numRows; ++i)
	{
		for (UINT j = 0; j < m_hmInfo.numCols; ++j)
		{
			dest[i * m_hmInfo.numCols + j] = Average(i, j);
		}
	}

	// Replace the old heightmap with the filtered one.
	m_heightMap = dest;
}

void CTerrain::CreateTerrain(HeightMapInfo& _info)
{
	// Pass in the information of the heightmap
	m_hmInfo = _info;

	m_numVertices = m_hmInfo.numRows * m_hmInfo.numCols;
	m_numFaces = (m_hmInfo.numRows - 1) * (m_hmInfo.numCols - 1) * 2;

	LoadHeightMap();
	SmoothHeightMap();


	/************************************************************************/

	// Initialize a vector of position vector with the size
	std::vector<glm::vec3> vertices(m_numVertices, glm::vec3());

	for (int row = 0; row < m_hmInfo.numRows; ++row)
	{
		float z = row * m_hmInfo.cellSpacing;

		for (int col = 0; col < m_hmInfo.numCols; ++col)
		{
			float x = col + m_hmInfo.cellSpacing;

			float y = m_heightMap[(row * m_hmInfo.numCols) + col];

			// load each data into the vertices
			vertices[(row * m_hmInfo.numCols) + col] = glm::vec3(x, y, z);
		}
	}

	std::vector<GLuint> indices(m_numFaces * 3);

	// Iterate over each quad and compute indices.
	int k = 0;
	for (UINT row = 0; row < m_hmInfo.numRows - 1; ++row)
	{
		for (UINT col = 0; col < m_hmInfo.numCols - 1; ++col)
		{
			indices[k] = row * m_hmInfo.numCols + col;
			indices[k + 1] = row * m_hmInfo.numCols + col + 1;
			indices[k + 2] = (row + 1) * m_hmInfo.numCols + col;

			indices[k + 3] = (row + 1) * m_hmInfo.numCols + col;
			indices[k + 4] = row * m_hmInfo.numCols + col + 1;
			indices[k + 5] = (row + 1) * m_hmInfo.numCols + col + 1;

			k += 6; // next quad
		}
	}

	GLuint VBO, EBO;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);





}

void CTerrain::RenderTerrain()
{

}

bool CTerrain::InBounds(UINT i, UINT j)
{
	// True if ij are valid indices; false otherwise.
	return
		i >= 0 && i < m_hmInfo.numRows &&
		j >= 0 && j < m_hmInfo.numCols;
}

float CTerrain::Average(UINT i, UINT j)
{
	// Function computes the average height of the ij element.
	// It averages itself with its eight neighbor pixels.  Note
	// that if a pixel is missing neighbor, we just don't include it
	// in the average--that is, edge pixels don't have a neighbor pixel.
	//
	// ----------
	// | 1| 2| 3|
	// ----------
	// |4 |ij| 6|
	// ----------
	// | 7| 8| 9|
	// ----------

	float avg = 0.0f;
	float num = 0.0f;

	for (UINT m = i - 1; m <= i + 1; ++m)
	{
		for (UINT n = j - 1; n <= j + 1; ++n)
		{
			if (InBounds(m, n))
			{
				avg += m_heightMap[m * m_hmInfo.numCols + n];
				num += 1.0f;
			}
		}
	}

	return avg / num;
}

// std::vector<GLfloat> CTerrain::CalculateTerrainVAO()
// {
// 	std::vector<glm::vec3> vertices(m_numVertices * 6);
// 
// 	for 
// 
// 
// }
