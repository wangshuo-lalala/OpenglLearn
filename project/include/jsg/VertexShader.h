#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H
#include <jsg/Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace jsg
{
	class VertexShader : public ShaderBase
	{
	public:
		VertexShader();
		~VertexShader();

		void setFilePath(const std::string& filepath);

		void useDefaultShader();

		void setModelMatrix(glm::mat4 matrix);

		void setViewMatrix(glm::mat4 matrix);

		void setProjectMatrix(glm::mat4 matrix);

		template<class T>
		void setUniform(const std::string& key, T value);


	private:
		bool useDefault;
		glm::mat4 modelMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 projectMatrix;
	};
}
#endif
