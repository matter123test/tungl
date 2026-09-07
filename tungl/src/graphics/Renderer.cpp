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
		
		spdlog::info("Created renderer");
	}

	Renderer::~Renderer()
	{
		spdlog::info("Destroyed renderer");
	}

	void Renderer::swapBuffers()
	{
		glfwSwapBuffers(m_window->getHandle());
	}
}