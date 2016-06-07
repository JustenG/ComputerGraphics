#version 410
in vec4 vPosition;
in vec4 vColour;
in vec2 vTexCoords;
in vec4 vShadowCoord;

out vec4 FragColor;

uniform float maxTerrainHeight;

uniform sampler2D waterTex;
uniform sampler2D grassTex;
uniform sampler2D rockTex;

uniform sampler2D shadowMap;

void main()
{
	vec4 water 	= texture(waterTex, vTexCoords * 8);
	vec4 grass 	= texture(grassTex, vTexCoords * 8);
	vec4 rock 	= texture(rockTex, vTexCoords * 4);
	
	float range = vPosition.y / maxTerrainHeight;
	vec4 productTex = water;
	productTex = mix(productTex,grass, smoothstep(0.4, 0.5,range));
	productTex = mix(productTex,rock, smoothstep(0.7, 0.8,range));
	
	vec3 diffuse = vec3(vColour.xyz) * productTex.xyz;
	
	float shadowValue = texture(shadowMap, vShadowCoord.xy).r;
	float shadowBias = vShadowCoord.z - 0.001f;
	
	
	if (shadowValue <  shadowBias) 
	{
		//diffuse = vec3(0,0,0);
		diffuse *= 0.05f;
	}
	
	vec4 result = vec4(diffuse,1);
	
	FragColor = result;// result;
}