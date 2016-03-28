#pragma once
#include "Components\MeshRenderer.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Terrain : public MeshRenderer
{
public:
	Terrain();
	~Terrain();

	// function to create a grid
	void GenerateGrid(unsigned int rows, unsigned int cols);

private:
};