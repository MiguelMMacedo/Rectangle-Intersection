#pragma once

#include <set>
#include <vector>

#include "Rectangle.hpp"

struct RectangleIntersection
{
    RectangleIntersection(const std::set<int32_t>& _ids,
                          const Rectangle& _rectangle);

    void Print() const;

    [[nodiscard]] static std::vector<RectangleIntersection> FindIntersections(
        const std::vector<Rectangle>& rectangles) noexcept;

    bool operator==(const RectangleIntersection& other) const;

    std::set<int32_t> ids;
    Rectangle rectangle;
};