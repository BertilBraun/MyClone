#version 330

in vec3 FragTexture;

out vec4 FragColor;

uniform samplerCube textureSampler;

const vec4 SkyColor = vec4(0.529, 0.808, 0.922, 1.0);

const float lowerLimit = 0.0;
const float upperLimit = 35.0;

void main() {
	
	FragColor = mix(SkyColor, texture(textureSampler, FragTexture), clamp((FragTexture.y - lowerLimit) / (upperLimit - lowerLimit), 0.0, 1.0));
}
  