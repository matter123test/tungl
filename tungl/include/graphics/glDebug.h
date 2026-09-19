#pragma once

#include <glad/glad.h>
#include <spdlog/spdlog.h>

#ifdef _DEBUG

#define TG_CORE_DEBUG_ONLY(x) x
#define TG_CORE_ASSERT(x) if (!(x)) __debugbreak();

#else

#define TG_CORE_DEBUG_ONLY(x) ;
#define TG_CORE_ASSERT(x) ;

#endif

namespace tg {
	// Callback function for printing debug statements
	void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length,
		const GLchar* msg, const void* data);

	inline void printHeader(const char* content) {
		spdlog::info("///-----{}-----{}", content, R"(\\\)");
	}

	inline void printFooter(const char* content) {
		spdlog::info("{}-----{}-----///", R"(\\\)", content);
	}
}
