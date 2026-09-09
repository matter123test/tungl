#pragma once

#include "Buffer.h"
#include <vector>
#include <glad/glad.h>

namespace tg {
	class IndexBuffer : public Buffer {
	public:
		IndexBuffer(const std::vector<GLuint> &indices);
		~IndexBuffer() override;

		// Inherited via Buffer
		void bind() const override;
		void unbind() const override;
	};
}