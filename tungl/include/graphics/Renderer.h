#pragma once

#include <GLFW/glfw3.h>
#include "Window.h"

namespace tg {
	class Renderer {
	public:
		Renderer(Window* window);
		~Renderer();

		void clear();
		void swapBuffers();

		// Resize the viewport to match the window dimensions
		void resizeViewport();

	private:
		// Viewport size
		int m_width = 0;
		int m_height = 0;

		Window* m_window = nullptr;
	};
}