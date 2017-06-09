#include "Cylinder.h"

Cylinder::Cylinder(float r, float h) {
	size = glm::vec2(r, h);

	color = getRandomColor();

	float x = rand() % 1000;
	float z = rand() % 1000;

	x /= 100;
	z /= 100;
	if (x < 5) {
		x = -x;
	}
	else {
		x -= 5;
	}
	if (z < 5) {
		z = -z;
	}
	else {
		z -= 5;
	}

	position = glm::vec3(x, 0.1, z);

	modelMatrix = translate(modelMatrix, position);

	float angleX = rand() % 360;
	float angleY = rand() % 360;
	float angleZ = rand() % 360;

	modelMatrix = glm::rotate(modelMatrix, angleX, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, angleY, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, angleZ, glm::vec3(0, 0, 1));

	for (int i = 0; i < 360; i+=36) {
		glm::vec3 p;

		p.x = cos(i * (2*M_PI / 360)) * r;
		p.z = sin(i * (2*M_PI / 360)) * r;
		p.y = 0;

		vertices.push_back(p);
		vertices.push_back(glm::vec3(p.x, h, p.z));
	}

	for (int i = 0; i < 20; i++) {
		indices.push_back(i);
		indices.push_back((i+1) % 20);
		indices.push_back((i+2) % 20);
	}
	vertices.push_back(glm::vec3(0, 0, 0));

	int k = 0;
	for (int i = 0; i < 9; i++) {
		indices.push_back(20);
		indices.push_back(k);
		indices.push_back(k + 2);
		k += 2;
	}

	indices.push_back(20);
	indices.push_back(k);
	indices.push_back(0);

	vertices.push_back(glm::vec3(0, h, 0));

	int q = 1;
	for (int i = 0; i < 9; i++) {
		indices.push_back(21);
		indices.push_back(q);
		indices.push_back(q + 2);
		q += 2;
	}

	indices.push_back(21);
	indices.push_back(q);
	indices.push_back(1);
}

Cylinder::~Cylinder() {
	glDeleteVertexArrays(1, &VAO);
}

float Cylinder::toRadians(float degrees) {
	return ((2 * M_PI) / 360) * degrees;
}

glm::vec3 Cylinder::getPosition() const {
	return position;
}

glm::vec2 Cylinder::getSize() const {
	return size;
}

glm::vec3* Cylinder::getRandomColor() {
	float h = 25;
	float s = 255;
	float v = rand() % (170 - 70 + 1) + 70;
	float r, g, b;

	s /= 255;
	v /= 255;

	int i;
	float f, p, q, t;
	if (s == 0) {
		return new glm::vec3(v, v, v);
	}

	h /= 60;
	i = floor(h);
	f = h - i;
	p = v * (1 - s);
	q = v * (1 - s * f);
	t = v * (1 - s * (1 - f));

	switch (i) {
		case 0: r = v; g = t; b = p; break;
		case 1: r = q; g = v; b = p; break;
		case 2: r = p; g = v; b = t; break;
		case 3: r = p; g = q; b = v; break;
		case 4: r = t; g = p; b = v; break;
		default: r = v; g = p; b = q; break;
	}



	return new glm::vec3(r, g, b);
}

void Cylinder::draw(Shader* shader) const {
	glm::vec3 color = *this->color;
	shader->setVector3("modelColor", color);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}