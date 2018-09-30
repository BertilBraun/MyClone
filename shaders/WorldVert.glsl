#version 330

layout (location = 0) in vec4  VertPosition;
layout (location = 1) in vec2  VertTexture;
layout (location = 2) in vec3  VertNormal;
layout (location = 3) in vec2  VertLight;

out vec2  FragTexture;
out float FragLight;
out float visibility;

uniform mat4 ProjMatrix;
uniform mat4 ViewMatrix;
uniform vec3 lightPos;
uniform float distance;

void main() {

	vec4 PosRelativeToCam = ViewMatrix * VertPosition;
	
	gl_Position = ProjMatrix * PosRelativeToCam;
	
	float diff = max(dot(normalize(VertNormal), normalize(lightPos)), 0.3);

	FragTexture		= VertTexture;
	FragLight		= (max(VertLight.x / 15, 0.3) + VertLight.y / 15) * diff;
	FragLight		= 1 * diff;
	visibility		= clamp(exp(-pow((length(PosRelativeToCam.xyz) * distance), 5)), 0, 1);
}
