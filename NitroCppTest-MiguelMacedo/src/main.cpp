#include <filesystem>
#include <iostream>

#include "JsonHelper.hpp"
#include "RectangleIntersection.hpp"

void PrintUsage(const char* programName)
{
    std::cout << "Usage: " << programName << " [options] <input_file>\n"
              << "Options:\n"
              << "\t-h, --help       Show this help message and exit\n"
              << "\t<input_file>     The path to the input file\n";
}

int main(int argc, char* argv[])
{
    if (argc > 1 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help"))
    {
        PrintUsage(argv[0]);
        return 0;
    }

    if (argc < 2)
    {
        PrintUsage(argv[0]);
        return 0;
    }

    std::filesystem::path filename;
    try
    {
        filename = argv[1];
        if (!std::filesystem::exists(filename))
        {
            std::cerr << "File " << filename << " does not exist" << std::endl;
            return 1;
        }
    }
    catch(...)
    {
        std::cerr << "An error occurred while processing the file path\n";
    }

    const auto opt_rectangles = JsonHelper::ParseFilePath(filename);
    if (opt_rectangles.has_value())
    {
        std::cout << "Input:\n";
        for (const auto rectangle : *opt_rectangles)
        {
            rectangle.Print();
        }

        const auto intersected_rectangles = RectangleIntersection::FindIntersections(*opt_rectangles);

        std::cout << "\nIntersections\n";
        for (const auto& intersected_rectangle : intersected_rectangles)
        {
            intersected_rectangle.Print();
        }

        return 0;
    }

    return 1;
}