#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <GL/glew.h>
#include <iostream>

class ShaderProgram {
	const GLchar* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"uniform mat4 model;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"void main()\n"
		"{\n"
		"gl_Position = projection * view * model * vec4(position.x, position.y, position.z, 1.0);\n"
		"}\0";
	const GLchar* fragmentShaderSource = "#version 330 core\n"
		"out vec4 color;\n"
		"uniform vec3 modelColor;\n"
		"void main()\n"
		"{\n"
		"color = vec4(modelColor, 1.0f);\n"
		"}\n\0";

	void compileShader(GLuint shader, const GLchar* shaderSource);

	GLuint createShader(GLenum shaderType, const GLchar* shaderSource);

public:
	ShaderProgram();
	~ShaderProgram();

	GLuint createShaderProgram();

};

#endif SHADER_PROGRAM