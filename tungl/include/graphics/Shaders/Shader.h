#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>

namespace tg {
	enum class ShaderType : GLenum {
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
	};

	std::string ShaderTypeName(ShaderType type);

	class Shader {
	public:
		Shader(const std::string& vertexShaderFilePath, const std::string fragmentShaderFilePath);
		~Shader();

		void use() const;

		GLuint getId() const { return m_programId; }

		void setInt(const std::string& name, int value) const;
		void setMat4(const std::string& name, const glm::mat4& value) const;
		void setVec3(const std::string& name, const glm::vec3& value) const;

		void setVec4(const std::string& name, const glm::vec3& value) const;
		void setVec4(const std::string& name, float r, float g, float b, float a) const;

		void setBool(const std::string& name, bool value) const;
		/*
		TODO:
		setMat3
		setVec2
		setVec3
		setVec4
		*/

	private:
		GLuint m_programId = 0;

		GLuint compileShader(const std::string& shaderSource, ShaderType type);

		mutable std::unordered_map<std::string, GLint> m_uniformCache;
		GLint getUniformLocation(const std::string& name) const;
	};
}