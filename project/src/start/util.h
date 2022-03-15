#ifndef __UTIL_H__
#define __UTIL_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

class CGlfwWindow
{
public:
	CGlfwWindow()
	{
		m_pWindow = glfwCreateWindow(800, 600, "", NULL, NULL);
	}
	~CGlfwWindow()
	{

	}
	void setTitle(const std::string& name)
	{
		glfwSetWindowTitle(m_pWindow, name.c_str());
	}

	void resize(int w, int h)
	{
		glfwSetWindowSize(m_pWindow, w, h);
	}

	bool shoolClose()
	{
		return glfwWindowShouldClose(m_pWindow);
	}

	GLFWwindow* getWindow() const
	{
		return m_pWindow;
	}

	GLFWwindow* m_pWindow;
};

class CGlfw
{
public:
	CGlfw()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
	~CGlfw()
	{
		glfwTerminate();
	}

	void setCurrentWindow(GLFWwindow* window)
	{
		glfwMakeContextCurrent(window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
		}
	}
};
#endif
