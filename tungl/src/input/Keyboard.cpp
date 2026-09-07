#include "input/Keyboard.h"
#include <GLFW/glfw3.h>

namespace tg {
	Key KeyFromGlfwKey(int glfwKey)
	{
		switch (glfwKey) {
			case GLFW_KEY_W: return Key::W;
			case GLFW_KEY_A: return Key::A;
			case GLFW_KEY_S: return Key::S;
			case GLFW_KEY_D: return Key::D;
			case GLFW_KEY_ESCAPE: return Key::Escape;

			default: return Key::None;
		}
	}
}