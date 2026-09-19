#pragma once

#include "graphics/Buffers/Buffers.h"
#include "Vertex.h"
#include <vector>
#include <memory>

namespace tg {
	class Mesh : Buffer {
	public:
		Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices);
		~Mesh();

		virtual void bind() const override;
		virtual void unbind() const override;

		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;

		Mesh(Mesh&&) noexcept = default;
		Mesh& operator=(Mesh&&) noexcept = default;

		inline int getIndicesCount() const { return m_indices.size(); }

	private:
		std::vector<Vertex> m_vertices;
		std::vector<GLuint> m_indices;

		std::unique_ptr<VertexArray> m_vao;
		std::unique_ptr<VertexBuffer> m_vbo;
		std::unique_ptr<IndexBuffer> m_ibo;
	};
}