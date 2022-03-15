#include <jsg/Shader.h>
#include <spdlog/spdlog.h>
namespace jsg
{
	ShaderBase::ShaderBase()
	{

	}

	ShaderBase::~ShaderBase()
	{

	}

	void ShaderBase::compile()
	{
		glCompileShader(shader);

		// 错误检查
		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			spdlog::error("{} complie error!\n {}", type(), infoLog);
		}
	}

}

