#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace jsg
{
	class ShaderBase
	{
	public:
		ShaderBase();

		virtual ~ShaderBase();
	public:
		
		virtual void compile();

		virtual const std::string& type() = 0;
	protected:
		GLuint shader;
	};
}

#endif