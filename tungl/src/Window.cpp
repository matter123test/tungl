#include "Window.h"
#include <spdlog/spdlog.h>

#ifdef _WIN32
#include <timeapi.h>

#define timeBeginPeriod() timeBeginPeriod(1)
#define timeEndPeriod() timeEndPeriod(1)

#else

#define timeBeginPeriod() ;
#define timeEndPeriod() ;

#endif // _WIN32

namespace tg {
	Window::Window(const std::string& title, int width, int height) :
		m_title(title), m_width(width), m_height(height)
	{
		timeBeginPeriod(1);

		if (!glfwInit()) {
			spdlog::error("Failed to initialize GLFW");
			return;
		}
		spdlog::info("Initialized GLFW");

		// Set opengl version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_handle = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
		
		// Set window as opengl context
		glfwMakeContextCurrent(m_handle);

		if (!m_handle) {
			spdlog::error("Failed to create GLFW window");
			return;
		}
		spdlog::info("Created GLFW window");

		m_inputHandler.init(m_handle);
		m_monitor = glfwGetPrimaryMonitor();

		// Window settings
		glfwSwapInterval(1);
	}

	Window::~Window()
	{
		if (m_handle) {
			glfwDestroyWindow(m_handle);
			spdlog::info("Destroyed GLFW window");
		}

		glfwTerminate();
		spdlog::info("Terminated GLFW");

		timeEndPeriod(1);
	}

	bool Window::isOpen()
	{
		return !glfwWindowShouldClose(m_handle);
	}

	void Window::close() {
		glfwSetWindowShouldClose(m_handle, true);
	}

	void Window::setPos(int x, int y)
	{
		glfwSetWindowPos(m_handle, x, y);
		spdlog::info("Set window pos X: {} Y: {}", x, y);
	}

	void Window::setCursorAtCenter()
	{
		glfwSetCursorPos(m_handle, 0, 0);
	}

	void Window::setCursorHidden(bool value)
	{
		if (value) {
			glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else {
			glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	void Window::center()
	{
		int monWidth, monHeight;
		glfwGetMonitorWorkarea(m_monitor, NULL, NULL, &monWidth, &monHeight);

		int centerX = monWidth / 2 - m_width / 2;
		int centerY = monHeight / 2 - m_height / 2;

		Window::setPos(
			centerX,
			centerY
		);
	}
}