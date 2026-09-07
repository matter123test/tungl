#include "input/InputHandler.h"

namespace tg {
	void InputHandler::init(GLFWwindow* handle) {
		glfwSetWindowUserPointer(handle, this);
		glfwSetKeyCallback(handle, InputHandler::keyCallback);
	}

	void InputHandler::process()
	{
		glfwPollEvents();
	}

	void InputHandler::update() {
		m_previousKeys = m_currentKeys;
	}

	std::optional<Event> InputHandler::pollEvent()
	{
		if (m_events.empty()) return std::nullopt;

		Event event = m_events.front();
		m_events.pop_back();

		return std::make_optional(event);
	}

	void InputHandler::keyCallback(GLFWwindow* handle, int keyCode, int scancode, int action, int mods) {
		auto inputHandler = static_cast<InputHandler*>(glfwGetWindowUserPointer(handle));

		if (!inputHandler) return;

		Key key = KeyFromGlfwKey(keyCode);

		if (action == GLFW_PRESS) {
			inputHandler->m_events.push_back(
				Event(Event::KeyPressed(key))
			);

			inputHandler->m_currentKeys.insert_or_assign(key, true);
		}

		if (action == GLFW_RELEASE) {
			inputHandler->m_events.push_back(
				Event(Event::KeyReleased(key))
			);

			inputHandler->m_currentKeys.insert_or_assign(key, false);
		}
	}

	bool InputHandler::isKeyDown(Key key) {
		auto search = m_currentKeys.find(key);

		if (search != m_currentKeys.end()) {
			return search->second;
		}

		return false;
	}

	bool InputHandler::isKeyPressed(Key key) {
		auto searchCurrent = m_currentKeys.find(key);
		if (searchCurrent == m_currentKeys.end()) return false;

		auto searchPrevious = m_previousKeys.find(key);
		if (searchPrevious == m_previousKeys.end()) return false;

		if (searchPrevious->second && !searchCurrent->second) {
			return true;
		}

		return false;
	}

	bool InputHandler::isKeyReleased(Key key) {
		auto search = m_currentKeys.find(key);

		if (search != m_currentKeys.end()) {
			return !search->second;
		}

		return true;
	}
}