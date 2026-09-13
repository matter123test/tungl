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
		
		using EventType = std::variant<
			KeyPressed, 
			KeyReleased, 
			WindowResized, 
			MouseMoved
		>;
		// --- Events ---


		template<typename T, typename Variant>
		struct is_variant_alternative;

		template<typename T, typename... Types>
		struct is_variant_alternative<T, std::variant<Types...>> :
			std::bool_constant<(std::is_same_v<T, Types> || ...)> {};

		template<typename T, typename Variant>
		static constexpr bool is_variant_alternative_v = is_variant_alternative<T, Variant>::value;

		template<typename T>
		constexpr static bool isValidEventType() {
			return is_variant_alternative_v<T, EventType>;
		}

	private:
		EventType m_type;

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