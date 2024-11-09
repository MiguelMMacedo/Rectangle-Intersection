#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

#include "JsonHelper.hpp"

using json = nlohmann::json;

namespace JsonHelper
{

std::optional<std::vector<Rectangle>> ParseFilePath(const std::filesystem::path& filePath) noexcept
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return std::nullopt;
    }

    json jsonData;
    try
    {
        jsonData = json::parse(file);
    }
    catch (const std::exception& e)
    {
        std::cerr << "JSON parse error\n";
        return std::nullopt;
    }

    if (!(jsonData.contains("rects") && jsonData["rects"].is_array()))
    {
        std::cerr << "JSON parse error\n";
        return std::nullopt;
    }

    if (jsonData["rects"].size() >= 10)
    {
        std::cerr << "Maximum number of rectangles is 10\n";
        return std::nullopt;
    }

    if (jsonData["rects"].size() == 0)
    {
        std::cerr << "No rectangles in file\n";
        return std::nullopt;
    }

    std::vector<Rectangle> rectangles;
    for (const auto& rect : jsonData["rects"])
    {
        if (!(rect.contains("x") && rect["x"].is_number())
            || !(rect.contains("y") && rect["y"].is_number())
            || !(rect.contains("w") && rect["w"].is_number())
            || !(rect.contains("h") && rect["h"].is_number()))
        {
            std::cerr << "JSON parse error\n";
            return std::nullopt;
        }

        rectangles.emplace_back(rect["x"], rect["y"], rect["w"], rect["h"]);
    }

    return rectangles;
}

}