#pragma once

#include "graphics/Texture/Texture.h"

namespace tg {
	class Texture2D : public Texture {
	public:
		Texture2D(std::string_view path);
		~Texture2D() = default;

		// Inherited via Texture
		void bind() const override;
		void unbind() const override;

	private:
		void generate() override;
	};
}