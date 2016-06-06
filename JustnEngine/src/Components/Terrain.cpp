#include "Components\Terrain.h"
#include "Assets\AssetManager.h"
#include "Rendering\Vertex.h"

#include "Assets\Mesh.h"
#include "Assets\Texture.h"
#include "Assets\Shader.h"

#include "all_includes.h"

Terrain::Terrain() : MeshRenderer()
{
	m_pMesh = new Mesh();
	m_pMaterial = new Material();

	m_perlinTexture = new Texture();
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
			aoVertices[r * cols + c].position = vec4((float)c, 0, (float)r, 1);
			// create some arbitrary colour based off something
			// that might not be related to tiling a texture
			vec3 Colour = vec3(sinf((c / (float)(cols - 1)) * (r / (float)(rows - 1))));
			aoVertices[r * cols + c].colour = vec4(1,1,1, 1);
			//aoVertices[r * cols + c].normal = 
			aoVertices[r * cols + c].texCoord = vec2(c / (float)(cols - 1), r / (float)(rows - 1));
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

void Terrain::CreatePerlinMap()
{
	int dims = 64;
	float *perlin_data = new float[dims * dims];
	float scale = (1.0f / dims) * 3;
	int octaves = 6;
	for (int x = 0; x < 64; ++x)
	{
		for (int y = 0; y < 64; ++y)
		{
			float amplitude = 1.f;
			float persistence = 0.3f;
			perlin_data[y * dims + x] = 0;
			for (int o = 0; o < octaves; ++o)
			{
				float freq = powf(2, (float)o);
				float perlin_sample = glm::perlin(vec2((float)x, (float)y) * scale * freq) * 0.5f + 0.5f;
				perlin_data[y * dims + x] += perlin_sample * amplitude;
				amplitude *= persistence;
			}
		}
	}

	m_perlinTexture->CreateFloatTexture(perlin_data, 64, 64);
	m_perlinTexture->SetTextureSlot(Material::PerlinTexture);
	m_pMaterial->LoadTexture(m_perlinTexture, Material::PerlinTexture);
}

void Terrain::SetShaderUniforms()
{
	int slot = Material::PerlinTexture;
	m_pShader->SetUniform("perlinTexture", slot);
}
