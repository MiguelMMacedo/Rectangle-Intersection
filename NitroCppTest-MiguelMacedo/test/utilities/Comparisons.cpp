#include "Rectangle.hpp"
#include "RectangleIntersection.hpp"

/*
 * Define the == operator only for testing purposes.
 * This operator is not required in source files, but it enables easy comparison
   of Rectangle and RectangleIntersection objects in test cases.
*/
bool Rectangle::operator==(const Rectangle& other) const
{
    return x == other.x && y == other.y && w == other.w && h == other.h;
}
bool RectangleIntersection::operator==(const RectangleIntersection&) const = default;