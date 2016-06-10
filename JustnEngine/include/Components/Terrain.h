#pragma once
#include "Components\MeshRenderer.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Utilities\Data.h"

class Texture;

class Terrain : public MeshRenderer
{
public:
	Terrain();
	~Terrain();

	// function to create a grid
	void GenerateGrid();
	void CreatePerlinMap();
	int* GetHeightMap() { return perlin_data_int; };

	int GetSize() { return m_size; };

private:

	void SetShaderUniforms() override;

	Texture* m_perlinTexture;
	float *perlin_data;
	int *perlin_data_int;

	int m_size;
	float m_scale;
	int m_octaves;
	float m_amplitude;
	float m_persistence;
	float m_frequency;

	bool m_sizeChanged;

//Data of Class
//-----------------------------------------
//-----------------------------------------
public:
	//Data Type
	using TerrainDataBinder = decltype(Make::CreateDataBinderType(
		m_size,
		m_scale,
		m_octaves,
		m_amplitude,
		m_persistence,
		m_frequency));

	BaseData* ToData() override;
	void FromData(BaseData* newData) override;
	bool Validate(BaseData* newData);
private:
	TerrainDataBinder* m_dataBinder;
	//-----------------------------------------
	//-----------------------------------------


};