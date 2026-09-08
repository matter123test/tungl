#pragma once

#include <GLFW/glfw3.h>
#include "Window.h"

namespace tg {
	class Renderer {
	public:
		Renderer(Window* window);
		~Renderer();

		void swapBuffers();

		// Resize the viewport to match the window dimensions
		void resizeViewport();

	private:
		// Viewport size
		int m_width;
		int m_height;

		Window* m_window;
	};
}