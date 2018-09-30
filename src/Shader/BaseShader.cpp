#include "BaseShader.h"
#include <fstream>
#include <iostream>

BaseShader::BaseShader(const std::string& vert, const std::string& frag) {
	VertexShaderID = loadShader("shaders/" + vert + "Vert.glsl", GL_VERTEX_SHADER);
	FragmentShaderID = loadShader("shaders/" + frag + "Frag.glsl", GL_FRAGMENT_SHADER);
	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);
	CheckShaderError(ProgramID, GL_LINK_STATUS, true, "Linking failed");
	glValidateProgram(ProgramID);
	CheckShaderError(ProgramID, GL_VALIDATE_STATUS, true, "Program Invalid!");
}

BaseShader::~BaseShader() {
	Stop();
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	glDeleteProgram(ProgramID);
}

GLuint BaseShader::loadShader(const std::string& path, GLenum type) {

	std::string source, line;
	std::ifstream ifi;

	ifi.open(path.c_str());

	if (ifi.is_open())
		while (ifi.good()) {
			getline(ifi, line);
			source.append(line + "\n");
		}
	else
		std::cout << "Unable to load shader: " << path << std::endl;


	const GLchar* p[1] = { source.c_str() };
	GLint lengths[1] = { source.length() };

	GLuint ID = glCreateShader(type);
	glShaderSource(ID, 1, p, lengths);
	glCompileShader(ID);
	CheckShaderError(ID, GL_COMPILE_STATUS, false, path + "Compiling failed");
	return ID;
}


void BaseShader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE) {
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

void BaseShader::BindAttribute(GLint attrib, const std::string& varName) {
	glBindAttribLocation(ProgramID, attrib, varName.c_str());
}

void BaseShader::GetUniform(const std::string& name) {
	GLuint ID = glGetUniformLocation(ProgramID, name.c_str());
	uniforms.insert(std::make_pair(name, ID));
}

void BaseShader::SetUniform(const std::string& name, bool value) {
	GLCall(glUniform1f(uniforms[name], (float)value));
}

void BaseShader::SetUniform(const std::string& name, int value) {
	glUniform1i(uniforms[name], value);
}

void BaseShader::SetUniform(const std::string& name, float value) {
	GLCall(glUniform1f(uniforms[name], value));
}

void BaseShader::SetUniform(const std::string& name, glm::vec3 value) {
	GLCall(glUniform3f(uniforms[name], value.x, value.y, value.z));
}

void BaseShader::SetUniform(const std::string& name, glm::vec2 value) {
	GLCall(glUniform2f(uniforms[name], value.x, value.y));
}

void BaseShader::SetUniform(const std::string& name, glm::mat4 value) {
	GLCall(glUniformMatrix4fv(uniforms[name], 1, false, &value[0][0]));
}
