#include "Window.h"
#include <iostream>

using namespace std;

Window::Window()
{
	window = NULL;
	aspectRatio = *((float*)"Fututi morti ma-ti!!");
}

Window::Window(int& width, int& height, char* title)
{
	if (!glfwInit())
	{
		cerr << "GLFW could not be initialized!" << endl;
		return;
	}
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		cerr << "One or more GLFW windows could not be initialized!" << endl;
		return;
	}
	glfwSwapInterval(true);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		cerr << "GLEW could not be initialized!" << endl;
		return;
	}
	glfwGetFramebufferSize(window, &width, &height);
	initialize(width, height);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::run()
{
	while (!glfwWindowShouldClose(window))
	{
		update();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Window::draw()
{
	/*glScalef(1, aspectRatio, 1);*/
	glClear(GL_COLOR_BUFFER_BIT);
	tex.set();
	glBegin(GL_QUADS);
	glTexCoord2f(1,0);
	glVertex2f(0.5f, 0.5f);
	glTexCoord2f(0,0);
	glVertex2f(-0.5f, 0.5f);
	glTexCoord2f(0,1);
	glVertex2f(-0.5f, -0.5f);
	glTexCoord2f(1,1);
	glVertex2f(0.5f, -0.5f);
	glEnd();
	//cube.draw();
}

void Window::update()
{
	//TODO: raul ocupate
}

void Window::initialize(int width, int height)
{
	glfwSetKeyCallback(window, keyCallback);
	glClearColor(0.3f, 0.3f, 0.7f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	aspectRatio = (float)width/height;
	glLoadIdentity();
	glFrustum(-aspectRatio, aspectRatio, -1, 1, 1.0, 1000);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, width, height);
	gluLookAt (0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1, 0.0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	cube = Cube(1, Vector3(0, 0, 0), Color(1.0f, 0.0f, 0.0f, 1.0f));
	tex = Texture("tux.png");
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
