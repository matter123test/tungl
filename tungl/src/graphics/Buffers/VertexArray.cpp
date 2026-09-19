#pragma once

#include "graphics/Buffers/VertexArray.h"
#include "graphics/glDebug.h"

namespace tg {
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_id);
		VertexArray::bind();
	}

	VertexArray::~VertexArray()
	{
		if (m_id != 0) {
			glDeleteVertexArrays(1, &m_id);
		}
	}

	void VertexArray::bind() const
	{
		TG_CORE_ASSERT(m_id != 0); // Invalid vertex array id
		glBindVertexArray(m_id);
	}
	
	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}
}