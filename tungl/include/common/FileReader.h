#pragma once

#include <utility>
#include <string>
#include <optional>

namespace tg {
	class FileReader {
	public:
		FileReader() = default;
		~FileReader() = default;

		static std::optional<std::string> getAllText(const std::string& filePath);
	};
}