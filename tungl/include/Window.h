#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include "input/InputHandler.h"

namespace tg {
	class Window {
	public:
		Window(const std::string &title, int width, int height);
		~Window();

		GLFWwindow* getHandle() { return m_handle; }

		bool isOpen();
		void close();

		InputHandler& input() { return m_inputHandler; }

		void setPos(int x, int y);
		void center();

	private:
		std::string m_title;
		int m_width;
		int m_height;

		GLFWwindow* m_handle = nullptr;
		GLFWmonitor* m_monitor = nullptr;

		InputHandler m_inputHandler;
	};
}