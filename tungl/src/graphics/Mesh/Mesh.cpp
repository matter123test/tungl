#include "graphics/Mesh/Mesh.h"
#include "graphics/glDebug.h"

namespace tg {
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices) :
		m_vertices(vertices), m_indices(indices)
	{
		printHeader("Mesh Creation");

		m_vao = std::make_unique<VertexArray>();
		m_vbo = std::make_unique<VertexBuffer>(vertices);
		m_ibo = std::make_unique<IndexBuffer>(indices);

		spdlog::info("Created mesh: sum({})", m_vao->getId() + m_vbo->getId() + m_ibo->getId());
		spdlog::info("VAO: {}", m_vao->getId());
		spdlog::info("VBO: {}", m_vbo->getId());
		spdlog::info("IBO: {}", m_ibo->getId());

		GLsizei stride = sizeof(Vertex);
		VertexBufferLayout layout({
			{ VertexAttributeType::Float3, stride },
			{ VertexAttributeType::Float3, stride },
			{ VertexAttributeType::Float2, stride },
		});

		// TODO: add a unique mesh id

		printFooter("Mesh Creation");
	}

	Mesh::~Mesh()
	{
		m_vao.reset();
		m_vbo.reset();
		m_ibo.reset();

		spdlog::info("Destroyed mesh");
	}

	void Mesh::bind() const {
		m_vao->bind();
	}

	void Mesh::unbind() const {
		m_vao->bind();
		m_vbo->bind();
		m_ibo->bind();
	}
}