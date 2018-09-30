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
uniform float timer;
uniform float distance;

vec4 getWorldPos()
{
    vec3 inVertPosition = VertPosition.xyz;
    inVertPosition.x += sin((timer + inVertPosition.z + inVertPosition.y) * 1.2f) / 15.0f;
    inVertPosition.z -= cos((timer + inVertPosition.x + inVertPosition.y) * 1.2f) / 15.0f;
    return vec4(inVertPosition, 1);
}


void main() {

	vec4 PosRelativeToCam = ViewMatrix * getWorldPos();
	
	gl_Position = ProjMatrix * PosRelativeToCam;
	
	float diff = max(dot(normalize(VertNormal), normalize(lightPos)), 0.3);

	FragTexture		= VertTexture;
	FragLight		= (max(VertLight.x / 15, 0.3) + VertLight.y / 15) * diff;
	FragLight		= 1 * diff;
	visibility		= clamp(exp(-pow((length(PosRelativeToCam.xyz) * distance), 5)), 0, 1);
}
