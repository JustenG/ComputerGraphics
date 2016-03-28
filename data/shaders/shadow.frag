#version 410

in vec4 vNormal;
in vec4 vShadowCoord;

out vec4 FragColour;

uniform vec3 lightDirection;

uniform sampler2D shadowMapSampler;

void main() {
	
	float d = max(0, dot(normalize(vNormal.xyz), lightDirection));

	if (texture(shadowMapSampler, vShadowCoord.xy).r  <  vShadowCoord.z - 0.01f) {
		d = 0;
	}

	FragColour = vec4(d, d, d, 1);
}
