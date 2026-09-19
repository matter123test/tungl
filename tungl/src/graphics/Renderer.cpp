#include "graphics/Renderer.h"
#include "graphics/glDebug.h"
#include <glad/glad.h>
#include <spdlog/spdlog.h>

namespace tg {
	Renderer::Renderer(Window* window) : m_window(window)
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			spdlog::error("Failed to load GLAD");
			return;
		}

#ifdef _DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(GLDebugMessageCallback, NULL);
#endif // _DEBUG
		
		glEnable(GL_DEPTH_TEST);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Gray
		//glClearColor(1.0f, 1.0f, 1.0, 1.0f); // White


		spdlog::info("Created renderer");

		// Set viewport
		resizeViewport();
	}

	Renderer::~Renderer()
	{
		spdlog::info("Destroyed renderer");
	}

	void Renderer::clear() {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::swapBuffers()
	{
		glfwSwapBuffers(m_window->getHandle());
	}

	void Renderer::resizeViewport()
	{
		m_width = m_window->getWidth();
		m_height = m_window->getHeight();

		glViewport(0, 0, m_width, m_height);
	}
}