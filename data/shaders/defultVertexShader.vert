#version 410
layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Normal;
layout(location = 2) in vec4 Colour;
layout(location = 3) in vec2 TexCoords;
layout(location = 4) in vec2 TexCoords2;
layout(location = 5) in vec3 Tangent;
layout(location = 6) in vec4 Binormal;
layout(location = 7) in vec4 Indices;
layout(location = 8) in vec4 Weights;

out vec4 vPosition;          
out vec4 vColour;            
out vec2 vTexCoords;
out vec4 vNormal;
out vec3 vTangent;
out vec3 vBitTangent;
out vec4 vShadowCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 projectionView;
uniform mat4 projectionViewModel;

uniform mat4 lightProjectionView;

const int MAX_BONES = 128;
uniform mat4 bones[MAX_BONES];

void main()
{
	vPosition = Position;
	vColour = Colour;
	vTexCoords = TexCoords;
	vNormal = Normal;
	vTangent = Tangent.xyz;
	vBitTangent = cross(Normal.xyz, Tangent.xyz);
	
	ivec4 index = ivec4(Indices);
	
	vec4 P = bones[index.x] * Position * Weights.x;
	P += bones[index.y] * Position * Weights.y;
	P += bones[index.z] * Position * Weights.z;
	P += bones[index.w] * Position * Weights.w;
	
	vShadowCoord = lightProjectionView * Position;
	
	gl_Position = projectionView * model * Position;
}