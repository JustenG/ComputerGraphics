#pragma once
#include "Components\Camera.h"


class Light : public Camera
{
public:
	Light();
	~Light();

	void Update(Transform transform);
	void UpdateLightProjectionViewTransform();

private:

};