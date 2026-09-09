#pragma once

#include "graphics/Buffers/Buffers.h"
#include "Vertex.h"
#include <vector>

namespace tg {
	class Mesh {
	public:
		Mesh(const std::vector<Vertex> &vertices);
		~Mesh();

	private:
		std::vector<Vertex> m_vertices;

		// TODO: implement
	};
}