#pragma once
#include "Components\Camera.h"


class Light : public Camera
{
public:
	Light();
	~Light();

	void Update();
	void UpdateLightProjectionViewTransform();
	glm::mat4 GetLightView();

private:

};