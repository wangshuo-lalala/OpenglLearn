#include <jsg/Viewer.h>
#include <spdlog/spdlog.h>

namespace jsg {

	Viewer::Viewer()
		:window(NULL),
		color(glm::dvec4(1.0, 1.0, 1.0, 1.0))
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(800, 600, "", NULL, NULL);
		glfwMakeContextCurrent(window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			spdlog::error("glad load failed!");
		}
	}

	Viewer::~Viewer()
	{
		glfwTerminate();
	}

	void Viewer::setTitle(const std::string& title)
	{
		glfwSetWindowTitle(window, title.c_str());
	}

	void Viewer::resize(double width, double height)
	{
		glfwSetWindowSize(window, width, height);
	}

	void Viewer::setClearColor(glm::dvec4 color)
	{
		this->color = color;
	}

	void Viewer::run()
	{
		while (!glfwWindowShouldClose(window))
		{
			glClearColor(color.r, color.g, color.b, color.a);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}


}