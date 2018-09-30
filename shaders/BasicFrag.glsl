#version 330

in vec2  FragTexture;

out vec4 FragColor;

uniform sampler2D textureSampler;


void main() {

	FragColor = texture(textureSampler, FragTexture);

	if (FragColor.a < 0.1)
		discard;
}
  