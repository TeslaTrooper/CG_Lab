#ifndef CONTROLLER
#define CONTROLLER

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Logic.h"

class Controller {
	static Logic* logic;

public:
	Controller();
	~Controller();

	Logic* getLogic();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
};

#endif CONTROLLER