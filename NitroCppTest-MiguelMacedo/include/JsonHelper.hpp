#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

#include "Rectangle.hpp"

namespace JsonHelper
{

[[nodiscard]] std::optional<std::vector<Rectangle>> ParseFilePath(
    const std::filesystem::path& filePath) noexcept;

}