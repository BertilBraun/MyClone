#version 330

layout (location = 0) in vec4 VertPosition;

out vec3 FragTexture;

uniform mat4 ProjMatrix;
uniform mat4 ViewMatrix;

void main() {

	gl_Position = ProjMatrix * ViewMatrix * VertPosition;
		
	FragTexture	= VertPosition.xyz;
}
