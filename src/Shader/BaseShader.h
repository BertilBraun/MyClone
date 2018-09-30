#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"

#include "defines.h"

#include <string>
#include <map>

class BaseShader {
public:
	BaseShader(const std::string& vert, const std::string& frag);
	~BaseShader();

	void Start() { GLCall(glUseProgram(ProgramID)); }
	void Stop() { glUseProgram(0); }
	GLuint GetID() { return ProgramID; }

private:
	GLuint loadShader(const std::string& path, GLenum type);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	
protected:
	void BindAttribute(GLint attrib, const std::string& varName);
	void GetUniform(const std::string& name);

	void SetUniform(const std::string& name, bool value);
	void SetUniform(const std::string& name, int value);
	void SetUniform(const std::string& name, float value);
	void SetUniform(const std::string& name, glm::vec2 value);
	void SetUniform(const std::string& name, glm::vec3 value);
	void SetUniform(const std::string& name, glm::mat4 value);

private:
	GLuint ProgramID;
	GLuint VertexShaderID;
	GLuint FragmentShaderID;
	std::map<std::string, GLuint> uniforms;
};

