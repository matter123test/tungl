#include "graphics/Buffers/VertexBuffer.h"
#include "graphics/glDebug.h"

namespace tg {
	VertexBuffer::~VertexBuffer()
	{
		if (m_id != 0) {
			glDeleteBuffers(1, &m_id);
		}
	}

	void VertexBuffer::bind() const
	{
		TG_ASSERT(m_id == 0); // Invalid id
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}