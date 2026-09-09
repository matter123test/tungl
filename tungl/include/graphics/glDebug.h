#pragma once

#include <glad/glad.h>

#ifdef _DEBUG

#define DEBUG_ONLY(x) x

#define TG_ASSERT(x) if (x) __debugbreak();

#else

#define DEBUG_ONLY(x) ;
#define TG_ASSERT(x) ;

#endif

namespace tg {
	// Callback function for printing debug statements
	void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length,
		const GLchar* msg, const void* data);
}
