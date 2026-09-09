#include "graphics/Buffers/VertexBufferLayout.h"

namespace tg {
	VertexBufferLayout::VertexBufferLayout(const std::vector<VertexBufferLayoutElement>& elements)
	{
		for (const auto& element : elements) {
			linkAttribute(element);
		}
	}

	void VertexBufferLayout::linkAttribute(const VertexBufferLayoutElement& element)
	{
		glEnableVertexAttribArray(m_currentLocation);
		glVertexAttribPointer(m_currentLocation,
			VertexAttributeTypeComponents(element.type),
			VertexAttributeTypeGLenum(element.type),
			element.normalize,
			element.stride,
			(GLvoid*)m_offset
		);

		m_currentLocation++;
		m_offset += VertexAttributeTypeSize(element.type);
	}

	GLuint VertexAttributeTypeSize(VertexAttributeType type)
	{
		switch (type) {
		
		case VertexAttributeType::Int:  return 4 * 1;
		case VertexAttributeType::Int2: return 4 * 2;
		case VertexAttributeType::Int3: return 4 * 3;
		case VertexAttributeType::Int4: return 4 * 4;

		case VertexAttributeType::Float:  return 4 * 1;
		case VertexAttributeType::Float2: return 4 * 2;
		case VertexAttributeType::Float3: return 4 * 3;
		case VertexAttributeType::Float4: return 4 * 4;

		default: __debugbreak();
		}
	}
	GLuint VertexAttributeTypeComponents(VertexAttributeType type)
	{
		switch (type) {

		case VertexAttributeType::Int:  return 1;
		case VertexAttributeType::Int2: return 2;
		case VertexAttributeType::Int3: return 3;
		case VertexAttributeType::Int4: return 4;

		case VertexAttributeType::Float:  return 1;
		case VertexAttributeType::Float2: return 2;
		case VertexAttributeType::Float3: return 3;
		case VertexAttributeType::Float4: return 4;

		default: __debugbreak();
		}
	}
	GLenum VertexAttributeTypeGLenum(VertexAttributeType type)
	{
		switch (type) {

		case VertexAttributeType::Int:  return GL_INT;
		case VertexAttributeType::Int2: return GL_INT;
		case VertexAttributeType::Int3: return GL_INT;
		case VertexAttributeType::Int4: return GL_INT;

		case VertexAttributeType::Float:  return GL_FLOAT;
		case VertexAttributeType::Float2: return GL_FLOAT;
		case VertexAttributeType::Float3: return GL_FLOAT;
		case VertexAttributeType::Float4: return GL_FLOAT;

		default: __debugbreak();
		}
	}
}