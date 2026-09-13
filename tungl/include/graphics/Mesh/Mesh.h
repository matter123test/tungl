#pragma once

#include "graphics/Buffers/Buffers.h"
#include "Vertex.h"
#include <vector>
#include <memory>

namespace tg {
	class Mesh {
	public:
		Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices);
		~Mesh();

		void bind() const;
		void unbind() const;

	private:
		std::vector<Vertex> m_vertices;
		std::vector<GLuint> m_indices;

		std::unique_ptr<VertexArray> m_vao;
		std::unique_ptr<VertexBuffer> m_vbo;
		std::unique_ptr<IndexBuffer> m_ibo;
	};
}