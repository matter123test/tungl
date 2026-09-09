#include "common/FileReader.h"
#include <spdlog/spdlog.h>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace tg {
	std::optional<std::string> FileReader::getAllText(const std::string& filePath)
	{
		if (!std::filesystem::exists(filePath)) {
			spdlog::error("File: \"{}\" does not exist!", filePath);
			return std::nullopt;
		}

		std::ifstream file(filePath);

		std::ostringstream sstr;
		sstr << file.rdbuf();

		spdlog::info("Loaded file: \"{}\"", filePath);

		return std::optional(sstr.str());
	}
}