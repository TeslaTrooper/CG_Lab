#ifndef WINDOW
#define WINDOW

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Logic.h"

class Window {
	const int WIDTH = 600;
	const int HEIGHT = 600;

	int actualWidth, actualHeight;

	Renderer* renderer;
	GLFWwindow* window;
	GLuint shaderProgram, vbo, vao, ebo;
	static Logic* logic;
	

	void initViewport();
	void initProjectionMatrix();
	void initViewMatrix();
	void initOpenGL();
public:

	Window();
	~Window();

	int isWindowClosing();
	void render();
	void passNewObjToRenderer();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};

#endif WINDOW