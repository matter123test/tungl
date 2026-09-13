#include "game/Camera/Camera2D.h"
#include <glm/gtc/matrix_transform.hpp>

namespace tg {
	Camera2D::Camera2D(Window* window, glm::vec2 position) : Camera(window, glm::vec3(position.x, position.y, 0.0f))
	{
		updateProjection();
		updateView();
	}

	void Camera2D::processEvents(double deltaTime)
	{
	}

	void Camera2D::updateProjection()
	{
		m_projection = glm::ortho(
			static_cast<float>(0),
			static_cast<float>(m_window->getWidth()),
			static_cast<float>(m_window->getHeight()),
			static_cast<float>(0)
		);
	}
	
	void Camera2D::updateView()
	{
		m_view = glm::translate(glm::mat4(1.0f), m_position);
	}
}