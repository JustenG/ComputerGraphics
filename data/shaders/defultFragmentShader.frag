#version 410
in vec4 vPosition;
in vec4 vColour;
in vec2 vTexCoords;
in vec4 vNormal;
out vec4 FragColor;

uniform sampler2D DiffuseTexture;
uniform sampler2D AmbientTexture;
uniform sampler2D GlowTexture;
uniform sampler2D SpecularTexture;
uniform sampler2D GlossTexture;
uniform sampler2D NormalTexture;
uniform sampler2D AlphaTexture;
uniform sampler2D DisplacementTexture;

uniform vec3 lightDir;
uniform vec3 lightColour;
uniform vec3 cameraPos;
uniform int specPow;

void main()
{
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColour;
	
	vec3 norm = normalize(vNormal.xyz);
	float diff = max(0, dot(norm , lightDir ) );
	vec3 diffuse = diff * lightColour;
	
	float specularStrength = 1.f;
	vec3 viewDir = normalize( cameraPos - vPosition.xyz );
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = max(0.0f, dot(viewDir,normalize(reflectDir)));
	spec = pow(spec, specPow);
	vec3 specular = specularStrength * spec * lightColour;
	
	vec4 result = vec4(ambient + diffuse + specular,1) * texture(DiffuseTexture, vTexCoords);
	FragColor =  result;
}