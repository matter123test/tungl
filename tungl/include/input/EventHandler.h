#pragma once

#include <GLFW/glfw3.h>
#include <optional>
#include <unordered_map>
#include <deque>
#include <vector>
#include <functional>
#include "Event.h"

namespace tg {
	class EventHandler {
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

		inline void addEvent(const Event& event) { m_events.push_front(event); }
		inline void setKey(const Key& key, bool value) { m_currentKeys.insert_or_assign(key, value); }

		std::unordered_map<Key, bool> m_previousKeys{};
		std::unordered_map<Key, bool> m_currentKeys{};
	
		// Callbacks
		static void keyCallback(GLFWwindow* handle, int keyCode, int scancode, int action, int mods);
		static void framebufferSizeCallback(GLFWwindow* handle, int width, int height);
		static void cursorPosCallback(GLFWwindow* handle, double xpos, double ypos);
	};
}