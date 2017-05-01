#ifndef WINDOW_H
#define WINDOW_H

#include "glhs.h"
#include "Cube.h"

class Window {
public:
	Window();
	Window(int& width, int& height, char* title);
	virtual ~Window();
	void run();
private:
	void initialize(int width, int height);
	void draw();
	void update();
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	GLFWwindow* window;
	Cube cube;
	float aspectRatio;
};

#endif // WINDOW_H
