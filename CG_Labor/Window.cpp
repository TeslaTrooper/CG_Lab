#include "Window.h"

Logic* Window::logic = new Logic();

Window::Window() {
	initOpenGL();

	this->window = glfwCreateWindow(WIDTH, HEIGHT, "CG_Labor | OpenGL", nullptr, nullptr);
	glfwSetWindowPos(this->window, 500, 100);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);

	this->renderer = new Renderer();

	initViewport();
	initProjectionMatrix();
	initViewMatrix();

	/* initialize random seed: */
	srand(time(NULL));

	for (int i = 0; i < 50; i++) {
		Cylinder* newObj = logic->createNewCylinder();

		vector<glm::vec3> v = newObj->getVertices();

		GLuint vao = renderer->createNewVAO(newObj->getVertices(), newObj->getIndices());
		newObj->setVAO(vao);
	}
	logic->clearNewObjs();

	

	glfwSetKeyCallback(window, key_callback);
}

void Window::render() {
	GLfloat start = 0;
	GLfloat dt = 0;
	GLfloat lastLoop = 0;

	while (!this->isWindowClosing()) {
		start = (GLfloat)glfwGetTime();

		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer->getShader()->use();

		vector<Cylinder*> newObjs = logic->getNewObjs();
		for (int i = 0; i < newObjs.size(); i++) {
			GLuint vao = renderer->createNewVAO(newObjs.at(i)->getVertices(), newObjs.at(i)->getIndices());
			newObjs.at(i)->setVAO(vao);
		}

		logic->clearNewObjs();

		vector<Cylinder*> cylinders = logic->getObjects();
		for (int i = 0; i < cylinders.size(); i++) {
			initViewMatrix();
			initProjectionMatrix();
			renderer->drawObject(cylinders.at(i));
		}

		glfwSwapBuffers(window);

		dt = (GLfloat)glfwGetTime() - start;
	}

	glfwTerminate();
}

int Window::isWindowClosing() {
	return glfwWindowShouldClose(window);
}

void Window::initViewport() {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	this->actualWidth = width;
	this->actualHeight = height;

	glViewport(0, 0, width, height);
}

void Window::initProjectionMatrix() {
	mat4 projection = perspective(45.0f, (GLfloat)actualWidth / (GLfloat)actualHeight, 0.1f, 100.0f);

	renderer->getShader()->setUniformMatrix4("projection", projection);
}

void Window::initViewMatrix() {
	GLfloat radius = 50.0f;
	GLfloat camX = sin(glfwGetTime()) * radius;
	GLfloat camZ = cos(glfwGetTime()) * radius;
	mat4 view = translate(view, vec3(0.0f, 0.0f, -3.0f));

	renderer->getShader()->setUniformMatrix4("view", view);
}

void Window::initOpenGL() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

Window::~Window() {
	delete renderer;
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_SPACE: logic->createNewCylinder(); break;
		default: return;
		}
	}
};

void Window::passNewObjToRenderer() {

}

int main() {
	Window win;
	win.render();

	return 0;
}