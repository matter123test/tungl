#pragma once

#include "../Buffers/Buffer.h"
#include <string_view>

namespace tg {
	class Texture : public Buffer {
	public:
		Texture(std::string_view path);
		~Texture();

	protected:
		std::string_view m_path;
		
		int m_width = 0;
		int m_height = 0;
		int m_channels = 0;

		uint8_t* m_data = nullptr;

		virtual void generate() = 0;	
	};
}