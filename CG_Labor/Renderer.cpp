#include "Renderer.h"

Renderer::Renderer() {
	GLuint shaderProgram;

	this->init(&shaderProgram);
	this->shader = new Shader(shaderProgram);
	shader->use();
}

Renderer::~Renderer() {
}

Shader* Renderer::getShader() {
	return this->shader;
}

void Renderer::drawFloor() {
	GLfloat vertices[] = {
		-5,  0, -5.f,
		5.f, 0, -5.f,
		5.f, 0, 5.f,
		-5.f,  0, 5.f,
	};
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	vector<vec3> v;
	vector<GLuint> i;

	for (int i = 0; i < 12; i+=3) {
		v.push_back(vec3(vertices[i], vertices[i+1], vertices[i+2]));
	}
	for (int j = 0; j < 6; j++) {
		i.push_back(indices[j]);
	}

	floorVAO = createNewVAO(v, i);
}

void Renderer::drawObject(Cylinder* cylinder) {
	mat4 view, projection, model;
	projection = perspective(45.0f, (GLfloat)600 / (GLfloat)600, 0.1f, 100.0f);
	shader->setUniformMatrix4("model", mat4());

	GLfloat radius = 3.0f;
	GLfloat camX = sin(glfwGetTime()) * radius;
	GLfloat camZ = cos(glfwGetTime()) * radius;
	view = glm::lookAt(glm::vec3(camX, 2, camZ), glm::vec3(0.0, 0, 0.0), glm::vec3(0.0, 1.0, 0.0));

	shader->setUniformMatrix4("view", view);
	shader->setVector3("modelColor", vec3(1.0f, 1.0f, 1.0f));

	glBindVertexArray(floorVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	shader->setUniformMatrix4("model", cylinder->getModelMatrix());
	cylinder->draw(shader);
}

GLuint Renderer::createNewVAO(vector<vec3> vertices, vector<GLuint> indices) {
	GLuint VAO, EBO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return VAO;
}

void Renderer::init(GLuint* shaderProgram) {
	ShaderProgram shaderProgramService = ShaderProgram();
	*shaderProgram = shaderProgramService.createShaderProgram();

	drawFloor();
}