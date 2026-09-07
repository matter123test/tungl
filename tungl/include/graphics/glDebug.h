#pragma once

#include <glad/glad.h>

namespace tg {
	// Callback function for printing debug statements
	void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length,
		const GLchar* msg, const void* data);
}
