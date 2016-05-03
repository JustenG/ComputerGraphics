#pragma once
#include "Components\Camera.h"


class Light : public Camera
{
public:
	static bool IsSingular() { return true; };

	Light();
	~Light();

	void Update(Transform transform);
	void UpdateLightProjectionViewTransform();
	glm::mat4 GetLightView();

private:

};