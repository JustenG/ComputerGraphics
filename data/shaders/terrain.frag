#version 410
in vec4 vPosition;
in vec4 vColour;
in vec4 vShadowCoord;

out vec4 FragColor;

uniform sampler2D shadowMap;

void main()
{
	
	vec3 diffuse = vec3(vColour.xyz);
	
	float shadowValue = texture(shadowMap, vShadowCoord.xy).r;
	float shadowBias = vShadowCoord.z - 0.01f;
	
	
	if (shadowValue <  shadowBias) 
	{
		diffuse = vec3(0,0,0);
	}
	
	vec4 result = vec4(diffuse,1);
	
	FragColor = result;// result;
}