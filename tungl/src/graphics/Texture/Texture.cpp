#include "graphics/Texture/Texture.h"
#include <spdlog/spdlog.h>
#include <filesystem>
#include <stb_image.h>

namespace tg {
	Texture::Texture(std::string_view path) : m_path(path) {
		if (!std::filesystem::exists(path)) {
			spdlog::error("File: {} does not exist", path);
			return;
		}

		stbi_set_flip_vertically_on_load(true);
		// This should be freed after the initialization of the derived class
		m_data = stbi_load(path.data(), &m_width, &m_height, &m_channels, 0);
	
		if (!m_data) {
			spdlog::error("Failed to load image data");
			return;
		}

		glGenTextures(1, &m_id);
	}

	Texture::~Texture() {
		glDeleteTextures(1, &m_id);
		spdlog::info("Destroyed texture id: {} file: {}", m_id, m_path);
	}
}