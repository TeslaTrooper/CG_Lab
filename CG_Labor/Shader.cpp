#include "Shader.h"

Shader::Shader(GLuint shaderProgram) {
	this->shaderProgram = shaderProgram;
}

Shader::~Shader() {}

void Shader::setUniformMatrix4(const GLchar* uniform, mat4& value) {
	GLint location = glGetUniformLocation(this->shaderProgram, uniform);
	if (location < 0) {
		std::cout << "Uniform does not exist!";
		return;
	}

	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(value));
}

void Shader::setInteger(const GLchar* uniform, GLint value) {
	glUniform1i(glGetUniformLocation(this->shaderProgram, uniform), value);
}

void Shader::setVector2(const GLchar* uniform, vec2 value) {
	glUniform2f(glGetUniformLocation(this->shaderProgram, uniform), value.x, value.y);
}

void Shader::setUniformMatrix3(const GLchar* uniform, mat3 value) {
	glUniformMatrix3fv(glGetUniformLocation(this->shaderProgram, uniform), 1, GL_FALSE, value_ptr(value));
}

void Shader::setVector3(const GLchar* uniform, vec3& value) {
	glUniform3f(glGetUniformLocation(this->shaderProgram, uniform), value.x, value.y, value.z);
}

void Shader::use() {
	glUseProgram(this->shaderProgram);
}