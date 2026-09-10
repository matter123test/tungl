#pragma once

namespace tg {
	enum class Key {
		None = 0,
		W,
		A,
		S,
		D,
		I,
		Escape,
		O
	};

	Key KeyFromGlfwKey(int glfwKey);
}