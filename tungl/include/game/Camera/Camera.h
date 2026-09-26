#pragma once

#include <glm/glm.hpp>
#include "input/EventHandler.h"
#include "Window.h"

namespace tg {
	// Default camera values
	inline const float YAW = -90.0f;
	inline const float PITCH = 0.0f;
	inline const float SPEED = 2.5f;
	inline const float SENSITIVITY = 0.1f;
	inline const float ZOOM = 45.0f;

	class Camera
	{
	public:
		glm::vec3 m_Position;
		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;

		glm::mat4 m_Projection;
		glm::mat4 m_View;

		// Angles
		float m_Yaw;
		float m_Pitch;

		// Options
		float m_MovementSpeed;
		float m_MouseSensitivity;
		float m_Zoom;

		Camera(
			glm::vec3 position = glm::vec3(0.0f),
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
			float yaw = YAW,
			float pitch = PITCH
		);
		~Camera() = default;

		void processMouseMovedEvent(const Event::MouseMoved& event);
		void processKeyPressedEvent(const EventHandler &handler, double deltaTime);
		
		void updateProjection(const Window &window);

		// Look at a 3d position
		void lookAt(const glm::vec3 &position);

	private:
		float m_oldMouseX = 0.0f;
		float m_oldMouseY = 0.0f;

		// Call this after modifying camera vectors
		void updateVectors();
	};
}