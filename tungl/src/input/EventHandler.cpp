#include "input/EventHandler.h"
#include <spdlog/spdlog.h>

namespace tg {
	void EventHandler::init(GLFWwindow* handle) {
		glfwSetWindowUserPointer(handle, this);
		glfwSetKeyCallback(handle, EventHandler::keyCallback);
		glfwSetFramebufferSizeCallback(handle, EventHandler::framebufferSizeCallback);
		glfwSetCursorPosCallback(handle, EventHandler::cursorPosCallback);
	}

	void EventHandler::process()
	{
		glfwPollEvents();
	}

	void EventHandler::update() {
		m_previousKeys = m_currentKeys;
	}

	std::optional<Event> EventHandler::pollEvent()
	{
		if (m_events.empty()) return std::nullopt;

		Event event = m_events.front();
		m_events.pop_back();

		return std::make_optional(event);
	}

	void EventHandler::keyCallback(GLFWwindow* handle, int keyCode, int scancode, int action, int mods) {
		auto inputHandler = static_cast<EventHandler*>(glfwGetWindowUserPointer(handle));

		if (!inputHandler) return;

		Key key = KeyFromGlfwKey(keyCode);

		if (action == GLFW_PRESS) {
			inputHandler->addEvent(
				Event(Event::KeyPressed(key))
			);

			inputHandler->setKey(key, true);
		}

		if (action == GLFW_RELEASE) {
			inputHandler->addEvent(
				Event(Event::KeyReleased(key))
			);

			inputHandler->setKey(key, false);
		}
	}

	void EventHandler::framebufferSizeCallback(GLFWwindow* handle, int width, int height)
	{
		auto inputHandler = static_cast<EventHandler*>(glfwGetWindowUserPointer(handle));

		if (!inputHandler) return;

		if (width > 0 && height > 0) {
			inputHandler->addEvent(
				Event(Event::WindowResized(width, height))
			);

			spdlog::info("Window resize callback W: {} H: {}", width, height);
		}
	}

	void EventHandler::cursorPosCallback(GLFWwindow* handle, double xpos, double ypos)
	{
		auto inputHandler = static_cast<EventHandler*>(glfwGetWindowUserPointer(handle));

		if (!inputHandler) return;

		inputHandler->addEvent(Event(Event::MouseMoved(xpos, ypos)));
	}

	bool EventHandler::isKeyDown(Key key) {
		auto search = m_currentKeys.find(key);

		if (search != m_currentKeys.end()) {
			return search->second;
		}

		return false;
	}

	bool EventHandler::isKeyPressed(Key key) {
		auto searchCurrent = m_currentKeys.find(key);
		if (searchCurrent == m_currentKeys.end()) return false;

		auto searchPrevious = m_previousKeys.find(key);
		if (searchPrevious == m_previousKeys.end()) return false;

		if (searchPrevious->second && !searchCurrent->second) {
			return true;
		}

		return false;
	}

	bool EventHandler::isKeyReleased(Key key) {
		auto search = m_currentKeys.find(key);

		if (search != m_currentKeys.end()) {
			return !search->second;
		}

		return true;
	}
}