#version 410
layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Colour;
layout(location = 2) in vec4 Normal;
layout(location = 3) in vec2 TexCoord;


out vec4 vPosition;          
out vec4 vColour;            
out vec2 vTexCoords;
out vec4 vShadowCoord;

uniform sampler2D perlinTexture;

uniform mat4 model;
uniform mat4 projectionView;

uniform mat4 lightProjectionView;

void main()
{
	vPosition = Position;
	vColour = Colour;
	vTexCoords = TexCoord;
	
	vPosition.y += texture(perlinTexture, vTexCoords).r;

	vShadowCoord = lightProjectionView * model * vPosition;
	
	gl_Position = projectionView * model * vPosition;
}