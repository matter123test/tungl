#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
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

		bool isKeyDown(Key key) const;
		bool isKeyPressed(Key key) const;
		bool isKeyReleased(Key key) const;

		double getMouseX() const { return m_mousePosition.x; }
		double getMouseY() const { return m_mousePosition.y; }
		glm::vec2 getMousePosition() const { return m_mousePosition; }

	private:
		GLFWwindow* m_handle;

		std::deque<Event> m_events;

		inline void addEvent(const Event& event) { m_events.push_front(event); }
		inline void setKey(const Key& key, bool value) { m_currentKeys.insert_or_assign(key, value); }

		std::unordered_map<Key, bool> m_previousKeys{};
		std::unordered_map<Key, bool> m_currentKeys{};

		glm::vec<2, double, glm::defaultp> m_mousePosition;

		// Callbacks
		static void keyCallback(GLFWwindow* handle, int keyCode, int scancode, int action, int mods);
		static void framebufferSizeCallback(GLFWwindow* handle, int width, int height);
		static void cursorPosCallback(GLFWwindow* handle, double xpos, double ypos);
	};
}