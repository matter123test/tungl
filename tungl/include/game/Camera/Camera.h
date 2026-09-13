#pragma once

#include <glm/glm.hpp>
#include "Window.h"

namespace tg {
	class Camera {
	public:
		Camera(Window* window, const glm::vec3& position) : m_window(window), m_position(position) {}
		virtual ~Camera() = default;

		virtual void processEvents(double deltaTime) = 0;
		
		// If the window size is changed
		virtual void updateProjection() = 0;
		virtual void updateView() = 0;

		// Getters
		glm::vec3 getPosition() const { return m_position; }
		glm::mat4 getProjection() const { return m_projection; }
		glm::mat4 getView() const { return m_view; }

	protected:
		glm::mat4 m_projection = glm::mat4(1.0f);
		glm::mat4 m_view = glm::mat4(1.0f);

		glm::vec3 m_position = glm::vec3(0.0f);

		Window* m_window;
	};
}