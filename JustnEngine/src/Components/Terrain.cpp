#include "Components\Terrain.h"
#include "Assets\AssetManager.h"
#include "Rendering\Vertex.h"
#include "Assets\Mesh.h"

Terrain::Terrain() : MeshRenderer()
{
	m_pMesh = new Mesh();
}

Terrain::~Terrain()
{
	delete m_pMesh;
}

void Terrain::GenerateGrid(unsigned int rows, unsigned int cols)
{
	Vertex* aoVertices = new Vertex[rows * cols];
	for (unsigned int r = 0; r < rows; ++r)
	{
		for (unsigned int c = 0; c < cols; ++c)
		{
			aoVertices[r * cols + c].Position = glm::vec4((float)c, 0, (float)r, 1);
			// create some arbitrary colour based off something
			// that might not be related to tiling a texture
			glm::vec3 Colour = glm::vec3(sinf((c / (float)(cols - 1)) * (r / (float)(rows - 1))));
			aoVertices[r * cols + c].Colour = glm::vec4(1,1,1, 1);
		}
	}

	unsigned int* auiIndices = new unsigned int[(rows - 1) * (cols - 1) * 6];
	unsigned int index = 0;
	for (unsigned int r = 0; r < (rows - 1); ++r)
	{
		for (unsigned int c = 0; c < (cols - 1); ++c)
		{
			// triangle 1
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);
			// triangle 2
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);
			auiIndices[index++] = r * cols + (c + 1);
		}
	}

	m_pMesh->BuildRenderDataFromLoaderNode(rows * cols, (rows - 1) * (cols - 1) * 6, aoVertices, auiIndices);

	// we’ll do more here soon!
	delete[] aoVertices;
	delete[] auiIndices;
}
