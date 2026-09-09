#include "graphics/Buffers/IndexBuffer.h"
#include "graphics/glDebug.h"

namespace tg {
	IndexBuffer::IndexBuffer(const std::vector<GLuint>& indices)
	{
		glGenBuffers(1, &m_id);
		IndexBuffer::bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	}
	
	IndexBuffer::~IndexBuffer()
	{
		if (m_id != 0) {
			glDeleteBuffers(1, &m_id);
		}
	}

	void IndexBuffer::bind() const
	{
		TG_ASSERT(m_id == 0) // Invalid id
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}

	void IndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}