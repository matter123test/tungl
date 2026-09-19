#include "graphics/Texture/Texture2D.h"
#include "graphics/glDebug.h"
#include <spdlog/spdlog.h>
#include <stb_image.h>

namespace tg {
	Texture2D::Texture2D(std::string_view path) : Texture(path) {
		Texture2D::generate();

		spdlog::info("Created 2D texture id: {} file: {} channels: {}", m_id, m_path, m_channels);
	}

	void Texture2D::bind() const
	{
		TG_CORE_ASSERT(m_id != 0);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}
	
	void Texture2D::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	void Texture2D::generate()
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
		
		if (!m_data) return;
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, m_data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(m_data);
		
		Texture2D::unbind();
	}
}