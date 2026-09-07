#pragma once

#include <GLFW/glfw3.h>
#include "Window.h"

namespace tg {
	class Renderer {
	public:
		Renderer(Window* window);
		~Renderer();

		void swapBuffers();

	private:
		Window* m_window;

	};
}