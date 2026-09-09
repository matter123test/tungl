#pragma once

#include <glad/glad.h>

namespace tg {
	class Buffer {
	public:
		Buffer() = default;
		virtual ~Buffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

	protected:
		GLuint m_id = 0;
	};
}