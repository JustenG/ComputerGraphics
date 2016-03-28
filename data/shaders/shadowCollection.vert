#version 410

uniform int numOfLights;
uniform mat4 lightProjectionViews[numOfLights];

out vec4 vShadowCoord;

void main()
{
	vShadowCoord = lightProjectionView * position;
}