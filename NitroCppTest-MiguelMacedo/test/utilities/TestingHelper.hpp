#pragma once

#include <iostream>

#include "Rectangle.hpp"
#include "RectangleIntersection.hpp"

// Overload << for Rectangle and RectangleIntersection for formatted, readable
// debugging output.

inline std::ostream& operator<<(std::ostream& os, const Rectangle& r)
{
    os << "[ID: " << r.id << ", x: " << r.x << ", y: " << r.y
       << ", width: " << r.w << ", height: " << r.h << "]";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const RectangleIntersection& ri)
{
    os << "[IDs: {";
    for (const auto& id : ri.ids)
    {
        os << id << " ";
    }
    os << "} Rectangle: " << ri.rectangle << "]";
    return os;
}