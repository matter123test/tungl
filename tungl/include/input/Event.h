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
		// --- Events ---

		template<typename EventType>
		constexpr static bool isValidEventType() {
			return  std::same_as<EventType, KeyPressed>  ||
					std::same_as<EventType, KeyReleased> ||
					std::same_as<EventType, WindowResized>;
		}

	private:
		std::variant<KeyPressed, KeyReleased, WindowResized> m_type;

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