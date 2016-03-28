#version 410
in vec4 vPosition;
in vec4 vColour;
in vec4 vShadowCoord;

out vec4 FragColor;

uniform sampler2D shadowMap;

void main()
{
	
	vec3 diffuse = vec3(vColour.xyz);
	if (texture(shadowMap, vShadowCoord.xy).r  <  vShadowCoord.z - 0.01f) 
	{
		diffuse = vec3(0,0,0);
	}
	
	vec4 result = vec4(diffuse,1);
	FragColor =  result;
}