#version 330

in vec2  FragTexture;
in float FragLight;
in float visibility;

out vec4 FragColor;

uniform sampler2D textureSampler;

const vec4 SkyColor = vec4(0.529, 0.808, 0.922, 1.0);

void main() {
	
	vec4 ObjColor = texture(textureSampler, FragTexture);

	ObjColor.xyz *= FragLight;

	if (ObjColor.a < 0.1)
		discard;
	
	FragColor = mix(SkyColor, ObjColor, visibility);
}
  