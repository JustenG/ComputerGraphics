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

	m_size			= 64;
	m_scale			= 3;
	m_octaves		= 6;
	m_amplitude		= 1;
	m_persistence	= 0.3f;
	m_frequency		= 1;

	m_sizeChanged = false;


	m_dataBinder = new TerrainDataBinder(
		m_size,
		m_scale,
		m_octaves,
		m_amplitude,
		m_persistence,
		m_frequency);
		

	vector<string> names;
	names.push_back("Size");;
	names.push_back("Scale");
	names.push_back("Octaves");
	names.push_back("Amplitude");
	names.push_back("Persistence");
	names.push_back("Frequency");
	m_dataBinder->SetNames(names);
}

Terrain::~Terrain()
{
	delete m_pMesh;
}

BaseData* Terrain::ToData()
{
	return m_dataBinder->Get();
}
void Terrain::FromData(BaseData* newData)
{
	if (Validate(newData))
	{
		m_dataBinder->Set(newData);

		if (m_sizeChanged)
		{
			m_sizeChanged = false;
			GenerateGrid();
		}
		CreatePerlinMap();
	}
	else;
	//Data not valid
}
bool Terrain::Validate(BaseData* newData)
{
	vector<BaseData*> children = newData->GetChildren();
	bool isDirty = false;

	if (!DataConverter::DataEqualsPrimitive(m_size, children[0]))
	{
		m_sizeChanged = true;
		isDirty = true;
	}
	if(!DataConverter::DataEqualsPrimitive(m_scale, children[1]) ||
		!DataConverter::DataEqualsPrimitive(m_octaves, children[2]) ||
		!DataConverter::DataEqualsPrimitive(m_amplitude, children[3]) ||
		!DataConverter::DataEqualsPrimitive(m_persistence, children[4]) ||
		!DataConverter::DataEqualsPrimitive(m_frequency, children[5]) )
	{
		isDirty = true;
	}

	return isDirty;
}

void Terrain::GenerateGrid()
{
	unsigned int rows, cols;
	rows = m_size;
	cols = m_size;

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
	int dims = m_size;

	float *perlin_data = new float[dims * dims];
	float scale = (1.0f / dims) * m_scale;
	int octaves = m_octaves;
	for (int x = 0; x < m_size; ++x)
	{
		for (int y = 0; y < m_size; ++y)
		{
			float amplitude = m_amplitude;
			float persistence = m_persistence;
			perlin_data[y * dims + x] = 0;
			for (int o = 0; o < octaves; ++o)
			{
				float freq = powf(2, (float)o) * m_frequency;
				float perlin_sample = glm::perlin(vec2((float)x, (float)y) * scale * freq) * 0.5f + 0.5f;
				perlin_data[y * dims + x] += perlin_sample * amplitude;
				amplitude *= persistence;
			}
		}
	}

	m_perlinTexture->CreateFloatTexture(perlin_data, m_size, m_size);
	m_perlinTexture->SetTextureSlot(Material::PerlinTexture);
	m_pMaterial->LoadTexture(m_perlinTexture, Material::PerlinTexture);
}

void Terrain::SetShaderUniforms()
{
	m_pShader->SetUniform("maxTerrainHeight", m_amplitude);


	int waterSlot	= 0;
	int grassSlot	= 1;
	int rockSlot	= 2;
	m_pShader->SetUniform("waterTex", waterSlot);
	m_pShader->SetUniform("grassTex", grassSlot);
	m_pShader->SetUniform("rockTex", rockSlot);


	int slot = Material::PerlinTexture;
	m_pShader->SetUniform("perlinTexture", slot);
}
