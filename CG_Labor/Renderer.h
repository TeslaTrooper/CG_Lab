#ifndef RENDERER
#define RENDERER

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Shader.h"
#include "ShaderProgram.h"
#include "Cylinder.h"

using namespace std;

class Renderer {
	GLuint floorVAO;

	Shader* shader;

	void init(GLuint* shaderProgram);

	void drawFloor();

public:
	Renderer();
	~Renderer();

	Shader* getShader();
	void drawObject(Cylinder* cylinder);
	GLuint createNewVAO(vector<vec3> vertices, vector<GLuint> indices);
};

#endif RENDERER
