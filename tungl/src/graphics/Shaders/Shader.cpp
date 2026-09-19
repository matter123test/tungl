#include <spdlog/spdlog.h>

#include "graphics/Shaders/Shader.h"
#include "common/FileReader.h"
#include "graphics/glDebug.h"

namespace tg {
	Shader::Shader(const std::string& vertexShaderFilePath, const std::string fragmentShaderFilePath)
	{
		tg::printHeader("Shader Creation");

		auto vertexShaderSource = FileReader::getAllText(vertexShaderFilePath);
		auto fragmentShaderSource = FileReader::getAllText(fragmentShaderFilePath);

		if (!vertexShaderSource.has_value() || !fragmentShaderSource.has_value()) {
			spdlog::error("Failed to initialize shader");
			return;
		}

		GLuint vertexShaderId = compileShader(vertexShaderSource.value(), ShaderType::Vertex);
		GLuint fragmentShaderId = compileShader(fragmentShaderSource.value(), ShaderType::Fragment);

		m_programId = glCreateProgram();
		glAttachShader(m_programId, vertexShaderId);
		glAttachShader(m_programId, fragmentShaderId);

		glLinkProgram(m_programId);

		int success = false;
		std::array<char, 512> infoLog{};

		(glGetProgramiv(m_programId, GL_LINK_STATUS, &success));

		if (!success) {
			glGetProgramInfoLog(m_programId, infoLog.size(), nullptr, infoLog.data());

			spdlog::error("Failed to link shader program");
			spdlog::error("Log: {}", infoLog.data());
		}
		else {
			spdlog::info("Linked the shader program");
		}

		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);

		spdlog::info("Created shader id: {}", m_programId);
		
		tg::printFooter("Shader Creation");
	}

	Shader::~Shader()
	{
		if (m_programId != 0) {
			glDeleteProgram(m_programId);
			spdlog::info("Destroyed shader id: {}", m_programId);
		}
	}

	void Shader::use() const
	{
		glUseProgram(m_programId);
	}

	void Shader::setInt(const std::string& name, int value) const
	{
		GLint location = getUniformLocation(name);
		glUniform1iv(location, 1, &value);
	}

	void Shader::setMat4(const std::string& name, const glm::mat4& value) const
	{
		GLint location = getUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::setVec3(const std::string& name, const glm::vec3& value) const
	{
		GLint location = getUniformLocation(name);
		glUniform3fv(location, 1, glm::value_ptr(value));
	}

	void Shader::setVec4(const std::string& name, const glm::vec3& value) const
	{
		GLint location = getUniformLocation(name);
		glUniform4fv(location, 1, glm::value_ptr(value));
	}

	void Shader::setVec4(const std::string& name, float r, float g, float b, float a) const
	{
		GLint location = getUniformLocation(name);
		glUniform4f(location, r, g, b, a);
	}

	void Shader::setBool(const std::string& name, bool value) const
	{
		GLint location = getUniformLocation(name);
		glUniform1i(location, value);
	}

	GLuint Shader::compileShader(const std::string& source, ShaderType type)
	{
		const char* data = source.data();

		GLuint shaderId = glCreateShader(static_cast<GLenum>(type));
		glShaderSource(shaderId, 1, &data, NULL);
		glCompileShader(shaderId);

		int success = false;
		std::array<char, 512> infoLog{};

		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

		std::string name = ShaderTypeName(type);

		if (!success) {
			glGetShaderInfoLog(shaderId, infoLog.size(), NULL, infoLog.data());

			spdlog::error("Failed to compile SHADER::{}", name);
			spdlog::error("Log: {}", infoLog.data());
		}

		spdlog::info("Compiled SHADER::{}", name);

		return shaderId;
	}

	GLint Shader::getUniformLocation(const std::string& name) const
	{
		auto search = m_uniformCache.find(name);

		if (search != m_uniformCache.end()) {
			return search->second;
		}
		else {
			GLint location = glGetUniformLocation(m_programId, name.c_str());
			m_uniformCache[name] = location;
			
			TG_CORE_DEBUG_ONLY(
				if (location < 0) {
					spdlog::warn("Ignored uniform {} (returned: {})", name, location);
				}
			)

			return location;
		}

		return 0;
	}

	std::string ShaderTypeName(ShaderType type) {
		switch (type) {
		case ShaderType::Vertex: return "VERTEX";
		case ShaderType::Fragment: return "FRAGMENT";

		default: return "INVALID_SHADER_TYPE";
		}
	}
}