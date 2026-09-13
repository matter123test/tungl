#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include "input/EventHandler.h"

namespace tg {
	class Window {
	public:
		Window(const std::string &title, int width, int height);
		~Window();

		bool isOpen();
		void close();
		EventHandler& input() { return m_inputHandler; }
		void center();

		// Getters
		GLFWwindow* getHandle() { return m_handle; }
		int getWidth() const { return m_width; }
		int getHeight() const { return m_height; }

		// Setters
		void setPos(int x, int y);
		void setSize(int width, int height) { m_width = width; m_height = height; }
		void setWidth(int value) { m_width = value; }
		void setHeight(int value) { m_height = value; }
		
		// This is required for first person cameras
		void setCursorAtCenter();
		void setCursorHidden(bool value);

	private:
		std::string m_title;
		int m_width;
		int m_height;

		GLFWwindow* m_handle = nullptr;
		GLFWmonitor* m_monitor = nullptr;

		EventHandler m_inputHandler;
	};
}