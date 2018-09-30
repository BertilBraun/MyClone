#version 330

layout (location = 0) in vec4  VertPosition;
layout (location = 1) in vec2  VertTexture;

out vec2  FragTexture;

uniform mat4 ProjMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

void main() {

	gl_Position		= ProjMatrix * ViewMatrix * ModelMatrix * VertPosition;	
	FragTexture		= VertTexture;
}
