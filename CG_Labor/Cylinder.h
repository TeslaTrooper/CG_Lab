#ifndef CYLINDER
#define CYLINDER

#define _USE_MATH_DEFINES

#include <gl\glew.h>
#include <glm\glm.hpp>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "Shader.h"

using namespace std;

class Cylinder {
	GLuint VAO;

	glm::vec3 position;
	glm::vec2 size;
	glm::vec3* color;
	glm::mat4 modelMatrix;

	vector<glm::vec3> vertices;
	vector<GLuint> indices;

	float toRadians(float degrees);
	glm::vec3* getRandomColor();

public:
	Cylinder(float r, float h);
	~Cylinder();

	glm::vec3 getPosition() const;
	glm::vec2 getSize() const;
	vector<glm::vec3> getVertices() const {
		return vertices;
	};
	vector<GLuint> getIndices() const {
		return indices;
	};
	void setVAO(GLuint vao) { VAO = vao; };

	void draw(Shader* shader) const;
	glm::mat4 getModelMatrix() const {
		return modelMatrix;
	}
};

#endif CYLINDER