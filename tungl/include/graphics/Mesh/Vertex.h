#pragma once

#include <glm/glm.hpp>

namespace tg {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texture_uv;

		Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& uv)
			: position(position), normal(normal), texture_uv(uv) { }
	};
}