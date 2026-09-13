#pragma once

#include "Camera.h"

namespace tg {
	class Camera3D : public Camera {
	public:
		Camera3D(Window* window, const glm::vec3& position, const glm::vec3& target);
		~Camera3D() override = default;
		
		// Inherited via Camera
		void processEvents(double deltaTime) override;
		void updateProjection() override;
		void updateView() override;
		
		// Getters
		glm::vec3 getFront() const { return m_front; }

	private:
		const glm::vec3 m_upDir = { 0.0f, 1.0f, 0.0f };
		const float m_speed = 100.0f;
		const float m_sensitivity = 0.1f;
		float m_fov = 45.0f;

		glm::vec3 m_target;
		glm::vec3 m_direction;

		glm::vec3 m_right;
		glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_up;

		float m_oldMouseX = 0;
		float m_oldMouseY = 0;

		float m_yaw = -90.0f;
		float m_pitch = 0;
	};
}