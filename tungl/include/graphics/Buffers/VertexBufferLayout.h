#pragma once

#include <glad/glad.h>
#include <vector>

namespace tg {
	enum class VertexAttributeType {
		Int, Int2, Int3, Int4,
		Float, Float2, Float3, Float4
	};

	GLuint VertexAttributeTypeSize(VertexAttributeType type);
	GLuint VertexAttributeTypeComponents(VertexAttributeType type);
	GLenum VertexAttributeTypeGLenum(VertexAttributeType type);

	struct VertexBufferLayoutElement {
		VertexAttributeType type;
		GLsizei stride;
		bool normalize;

		VertexBufferLayoutElement(VertexAttributeType type, GLsizei stride, bool normalize = false) :
			type(type), stride(stride), normalize(normalize)
		{}
	};

	class VertexBufferLayout {
	public:
		VertexBufferLayout(const std::vector<VertexBufferLayoutElement> &elements);
		~VertexBufferLayout() = default;

		void linkAttribute(const VertexBufferLayoutElement& element);

	private:
		GLsizei m_offset = 0;
		GLuint m_currentLocation = 0;
	};
}