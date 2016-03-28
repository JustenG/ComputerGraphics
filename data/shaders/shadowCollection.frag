#version 410

in vec4 vShadowCoord;

out vec4 FragColour;

uniform sampler2D shadowMapSampler;

void main() {
	
	float d = texture(shadowMapSampler, vShadowCoord.xy).r;

	FragColour = vec4(d, d, d, 1);
}
