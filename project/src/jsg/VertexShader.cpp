#include <jsg/VertexShader.h>
namespace jsg
{
	const char* jsg_vertex_shader =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 project;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = project * view * model * vec4(aPos, 1.0);\n"
		"}\0";

	VertexShader::VertexShader()
		:modelMatrix(glm::mat4(1.0f)),
		viewMatrix(glm::mat4(1.0f)),
		projectMatrix(glm::mat4(1.0f)),
		useDefault(true)
	{
		useDefaultShader();
	}

	void VertexShader::useDefaultShader()
	{
		shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(shader, 1, &jsg_vertex_shader, NULL);
	}

}

