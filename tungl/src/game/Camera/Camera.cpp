#include "game/Camera/Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace tg {
	Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : 
		m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM),
		m_Position(position), m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch)
	{
		updateVectors();
	}

	void Camera::processMouseMovedEvent(const Event::MouseMoved& event)
	{
		float xOffset = event.x - m_oldMouseX;
		float yOffset = m_oldMouseY - event.y;

		m_oldMouseX = event.x;
		m_oldMouseY = event.y;

		xOffset *= m_MouseSensitivity;
		yOffset *= m_MouseSensitivity;

		m_Yaw += xOffset;
		m_Pitch += yOffset;

		// Clamp pitch
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		updateVectors();
	}

	void Camera::processKeyPressedEvent(const EventHandler& handler, double deltaTime)
	{
		float velocity = m_MovementSpeed * deltaTime;
		if (handler.isKeyDown(Key::W))
			m_Position += m_Front * velocity;
		if (handler.isKeyDown(Key::S))
			m_Position -= m_Front * velocity;
		if (handler.isKeyDown(Key::A))
			m_Position -= m_Right * velocity;
		if (handler.isKeyDown(Key::D))
			m_Position += m_Right * velocity;


		m_View = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void Camera::updateProjection(const Window& window)
	{
		m_Projection = glm::perspective(
			glm::radians(ZOOM), // FOV 
			static_cast<float>(window.getWidth()) / static_cast<float>(window.getHeight()),
			0.1f, 1000.0f
		);
	}

	void Camera::updateVectors()
	{
		// calculate the new Front vector
		glm::vec3 direction(
			cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)),
			sin(glm::radians(m_Pitch)),
			sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch))
		);

		m_Front = glm::normalize(direction);

		// also re-calculate the Right and Up vector
		// normalize the vectors, because their length gets 
		// closer to 0 the more you look up or down which results in slower movement.
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}
}