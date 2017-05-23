#ifndef SHADER
#define SHADER

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace glm;

class Shader {

	GLuint shaderProgram;

public:

	Shader(GLuint shaderProgram);
	~Shader();

	void setUniformMatrix4(const GLchar* uniform, mat4& value);

	void setInteger(const GLchar* uniform, GLint value);

	void setVector2(const GLchar* uniform, vec2 value);

	void setUniformMatrix3(const GLchar* uniform, mat3 value);

	void setVector3(const GLchar* uniform, vec3& value);

	void use();
};

#endif SHADER