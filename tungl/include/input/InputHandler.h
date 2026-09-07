#pragma once

#include <GLFW/glfw3.h>
#include <optional>
#include <unordered_map>
#include <deque>
#include "Event.h"

namespace tg {
	class InputHandler {
	public:
		void init(GLFWwindow* handle);

		// Process glfw events
		void process();
		// Swap key frames
		void update();

		// Get events until the queue is empty
		std::optional<Event> pollEvent();

		bool isKeyDown(Key key);
		bool isKeyPressed(Key key);
		bool isKeyReleased(Key key);

	private:
		std::deque<Event> m_events;

		std::unordered_map<Key, bool> m_previousKeys{};
		std::unordered_map<Key, bool> m_currentKeys{};
	
		// Callbacks
		static void keyCallback(GLFWwindow* handle, int keyCode, int scancode, int action, int mods);
	};
}