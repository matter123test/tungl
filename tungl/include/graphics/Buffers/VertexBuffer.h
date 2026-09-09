#pragma once

#include "graphics/Buffers/Buffer.h"
#include <vector>

namespace tg {
	class VertexBuffer : public Buffer {
	public:
		template<typename T>
		inline VertexBuffer(const std::vector<T> &data) {
			glGenBuffers(1, &m_id);
			VertexBuffer::bind();
			glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
		}

		~VertexBuffer() override;

		// Inherited via Buffer
		void bind() const override;
		void unbind() const override;
	};
}