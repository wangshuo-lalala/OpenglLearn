#ifndef SHADERINTERFACE_H
#define SHADERINTERFACE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace jsg
{
	class ShaderInterface
	{
		ShaderInterface() :
			program(-1)
		{

		}
		virtual ~ShaderInterface()
		{

		}
	public:
		virtual void use()
		{
			glUseProgram(program);
		}


	protected:
		GLuint program;
	};
}

#endif
