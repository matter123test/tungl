#pragma once

#include "Window.h"
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <functional>

namespace sandbox {
	struct DebugInfo {
		double frametimeMs;
		int fps;

		glm::vec3 cameraPos;
		glm::vec3 cameraFront;

		mutable bool isWireframe;
		mutable float cameraSpeed = 10.0f;

		std::function<void(float)> changeCameraSpeed;
	};

	class DebugUI {
	public:
		DebugUI(GLFWwindow* window_handler);
		~DebugUI();

		void processKeyEvents(tg::Window* window);
		void draw(const DebugInfo& info) const;

	private:
		bool m_showDebugInfo = true;
	};
}