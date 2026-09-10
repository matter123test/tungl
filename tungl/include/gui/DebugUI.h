#pragma once

#include "Window.h"
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

namespace tg {
	struct DebugInfo {
		double frametimeMs;
		int fps;

		glm::vec3 cameraPos;
		glm::vec3 cameraFront;
	};

	class DebugUI {
	public:
		DebugUI(GLFWwindow *window_handler);
		~DebugUI();

		void processKeyEvents(Window* window);
		void draw(const DebugInfo&stats) const;
	
	private:
		bool m_showDebugInfo = true;
	};
}