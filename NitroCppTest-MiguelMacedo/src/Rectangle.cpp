#include <iostream>

#include "Rectangle.hpp"

// init counter of IDs
int32_t Rectangle::s_nextId = 1;

Rectangle::Rectangle(const int32_t _x,
                     const int32_t _y,
                     const int32_t _w,
                     const int32_t _h)
    : x{_x}
    , y{_y}
    , w{_w}
    , h{_h}
    , id{s_nextId++}
{
}

void Rectangle::Print() const
{
    std::cout << '\t' << id << ": Rectangle at (" << x << "," << y << "), w=" << w << ", h=" << h << ".\n";
}

std::optional<Rectangle> Rectangle::Intersect(const Rectangle& r1, const Rectangle& r2) noexcept
{
    const int32_t x1_overlap = std::max(r1.x, r2.x);
    const int32_t x2_overlap = std::min(r1.x + r1.w, r2.x + r2.w);

    const int32_t y1_overlap = std::max(r1.y, r2.y);
    const int32_t y2_overlap = std::min(r1.y + r1.h, r2.y + r2.h);

    if (x1_overlap < x2_overlap && y1_overlap < y2_overlap)
    {
        return Rectangle(x1_overlap,
                         y1_overlap,
                         x2_overlap - x1_overlap,
                         y2_overlap - y1_overlap);
    }

    return {};
}