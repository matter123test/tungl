#pragma once

#include <variant>
#include "Keyboard.h"

namespace tg {
	struct Event {
	public:
		template<typename EventType>
		Event(EventType type) : m_type(type) {}

		// --- Events ---
		struct KeyPressed {
			Key keycode;
		};

		struct KeyReleased {
			Key keycode;
		};

		struct WindowResized {
			int width;
			int height;
		};

		struct MouseMoved {
			double x;
			double y;
		};

#define EVENT_TYPES KeyPressed, KeyReleased, WindowResized, MouseMoved
		// --- Events ---

		template<class T, class... Ts>
		constexpr static bool is_one_of_v = (std::is_same_v<T, Ts> || ...);

		template<typename EventType>
		constexpr static bool isValidEventType() {
			return is_one_of_v<EventType, EVENT_TYPES>;
		}

	private:
		std::variant<EVENT_TYPES> m_type;

	public:
		template <typename EventType>
		bool is() const {
			static_assert(isValidEventType<EventType>(), "Invalid EventType");

			return std::holds_alternative<EventType>(m_type);
		}

		template<typename EventType>
		EventType* getIf() {
			static_assert(isValidEventType<EventType>(), "Invalid EventType");

			if (std::holds_alternative<EventType>(m_type)) {
				return &std::get<EventType>(m_type);
			}

			return nullptr;
		}
	};
}