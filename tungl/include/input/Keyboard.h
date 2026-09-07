#pragma once

namespace tg {
	enum class Key {
		None = 0,
		W,
		A,
		S,
		D,
		Escape
	};

	Key KeyFromGlfwKey(int glfwKey);
}