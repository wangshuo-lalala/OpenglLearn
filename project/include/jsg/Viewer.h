#ifndef VIEWER_H
#define VIEWER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>
#include <memory>
namespace jsg {
	class Node;
	class Viewer
	{
	public:
		Viewer();
		~Viewer();

	public:
		void setTitle(const std::string& title);

		void resize(double width, double height);

		void setClearColor(glm::dvec4 color);

		void run();

		void frame();

		void handleEvents();

		void handleUpdates();

		void rederLoop();
		
		void setRootNode(Node* root);
	private:

	private:
		GLFWwindow* window;
		glm::dvec4 color;
		std::shared_ptr<Node> rootNode;
	};
}
#endif
