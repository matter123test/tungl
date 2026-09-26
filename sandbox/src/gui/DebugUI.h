#pragma once

#include "Window.h"
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <functional>

namespace sandbox {
	struct DebugCameraInfo {
		glm::vec3 position;
		glm::vec3 direction;
		mutable float yaw;
		mutable float pitch;
	
		mutable float speed = 10.0f;
		std::function<void(float)> changeSpeedFunction;
	};

	struct DebugInfo {
		double frametimeMs;
		int fps;

		DebugCameraInfo cameraInfo{};

		mutable bool isWireframe;
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