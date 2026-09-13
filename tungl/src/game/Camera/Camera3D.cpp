#include "game/Camera/Camera3D.h"
#include <glm/gtc/matrix_transform.hpp>

namespace tg {
	Camera3D::Camera3D(Window* window, const glm::vec3& position, const glm::vec3& target) :
		Camera(window, position), 
		m_target(target), m_direction(glm::normalize(position - target)), 
		m_right(glm::cross(m_upDir, m_direction)), m_up(glm::cross(m_direction, m_right))
	{
		updateProjection();
		updateView();
	}

	void Camera3D::processEvents(double deltaTime)
	{
		float mouseX = m_window->input().getMouseX();
		float mouseY = m_window->input().getMouseY();

		float xoffset = mouseX - m_oldMouseX;
		float yoffset = m_oldMouseY - mouseY;

		m_oldMouseX = mouseX;
		m_oldMouseY = mouseY;

		xoffset *= m_sensitivity;
		yoffset *= m_sensitivity;

		m_yaw += xoffset;
		m_pitch += yoffset;

		// Clamp pitch
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		direction.y = sin(glm::radians(m_pitch));
		direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

		m_front = glm::normalize(direction);

		if (m_window->input().isKeyDown(Key::W))
			m_position += m_speed * m_front * static_cast<float>(deltaTime);

		if (m_window->input().isKeyDown(Key::S))
		 	m_position -= m_speed * m_front * static_cast<float>(deltaTime);

		if (m_window->input().isKeyDown(Key::A))
			m_position -= glm::normalize(glm::cross(m_front, m_up)) * m_speed * static_cast<float>(deltaTime);

		if (m_window->input().isKeyDown(Key::D))
			m_position += glm::normalize(glm::cross(m_front, m_up)) * m_speed * static_cast<float>(deltaTime);

		updateView();
	}

	void Camera3D::updateProjection()
	{
		m_projection = glm::perspective(
			glm::radians(m_fov), // FOV 
			static_cast<float>(m_window->getWidth()) / static_cast<float>(m_window->getHeight()),
			0.1f, 1000.0f
		);
	}
	
	void Camera3D::updateView()
	{
		m_view = glm::lookAt(
			m_position,
			m_position + m_front,
			m_up
		);
	}
}