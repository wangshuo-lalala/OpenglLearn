#ifndef __SHADER_H__
#define __SHADER_H__
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

std::string cshader_vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos, 1.0);\n"
"}\0";

std::string cshader_fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

class CShader
{
public:
	CShader()
		:m_success(true),
		m_vertexPath(""),
		m_fragmentPath(""),
		m_vertexSource(cshader_vertexShaderSource),
		m_fragmentSource(cshader_fragmentShaderSource),
		m_vertextShader(0),
		m_fragShader(0),
		m_shaderProgram(0)
	{

	}
	~CShader()
	{
		if (m_shaderProgram != 0)
		{
			glDeleteProgram(m_shaderProgram);
		}
	}

	void setVertxPath(const std::string& filePath)
	{
		m_vertexPath = filePath;
		std::ifstream is;
		is.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			is.open(m_vertexPath);
			std::stringstream ss;
			ss << is.rdbuf();
			is.close();
			m_vertexSource = ss.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
		}
	}

	void setFragmentPath(const std::string& filePath)
	{
		m_fragmentPath = filePath;
		
		std::ifstream is;
		is.exceptions(std::ifstream::badbit | std::ifstream::failbit);
		try
		{
			is.open(m_fragmentPath);
			std::stringstream ss;
			ss << is.rdbuf();
			is.close();
			m_fragmentSource = ss.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
		}

	}

	void setVertexSource(const std::string& source)
	{
		m_vertexSource = source;
	}

	void setFragmentSource(const std::string& source)
	{
		m_fragmentSource = source;
	}

	// 编译链接
	void compileAndLink()
	{
		m_vertextShader = glCreateShader(GL_VERTEX_SHADER);
		const char* vs = m_vertexSource.c_str();
		glShaderSource(m_vertextShader, 1, &vs, NULL);
		glCompileShader(m_vertextShader);
		// 错误检查
		int success;
		char infoLog[512];
		glGetShaderiv(m_vertextShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			m_success = false;
			glGetShaderInfoLog(m_vertextShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		m_fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* ss = m_fragmentSource.c_str();
		glShaderSource(m_fragShader, 1, &ss, NULL);
		glCompileShader(m_fragShader);
		glGetShaderiv(m_fragShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			m_success = false;
			glGetShaderInfoLog(m_fragShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// 链接
		m_shaderProgram = glCreateProgram();
		glAttachShader(m_shaderProgram, m_vertextShader);
		glAttachShader(m_shaderProgram, m_fragShader);
		glLinkProgram(m_shaderProgram);
		// check for linking errors
		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
		if (!success) 
		{
			m_success = false;
			glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(m_vertextShader);
		glDeleteShader(m_fragShader);

	}

	// 使用
	void use()
	{
		if (m_success)
		{
			glUseProgram(m_shaderProgram);
		}
	}

	void setUniform(const std::string& name, bool value) const
	{
		int location = glGetUniformLocation(m_shaderProgram, name.c_str());
		glUniform1i(location, static_cast<int>(value));
	}
	void setUniform(const std::string& name, int value) const
	{
		int location = glGetUniformLocation(m_shaderProgram, name.c_str());
		glUniform1i(location, value);
	}
	void setUniform(const std::string& name, float value) const
	{
		int location = glGetUniformLocation(m_shaderProgram, name.c_str());
		glUniform1f(location, value);
	}
	
private:
	bool m_success; // shader是否有效

	std::string m_vertexPath;
	std::string m_fragmentPath;
	std::string m_vertexSource;
	std::string m_fragmentSource;

	unsigned int m_vertextShader;
	unsigned int m_fragShader;
	unsigned int m_shaderProgram;
};



#endif