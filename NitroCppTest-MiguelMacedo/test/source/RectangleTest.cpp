#include "Rectangle.hpp"

#include <gtest/gtest.h>

TEST(Rectangle, RectanglesIntersect)
{
    const auto expected_r = Rectangle(120, 120, 30, 30);

    const auto r1 = Rectangle(100, 100, 50, 50);
    const auto r2 = Rectangle(120, 120, 50, 50);

    const auto r_intersect = Rectangle::Intersect(r1, r2);
    ASSERT_TRUE(r_intersect.has_value());
    ASSERT_EQ(*r_intersect, expected_r);
}

TEST(Rectangle, IdenticalRectanglesWithDifferentIdsAreEqualAndIntersect)
{
    const Rectangle r1 = Rectangle(0, 0, 10, 10);
    const Rectangle r2 = Rectangle(0, 0, 10, 10);

    ASSERT_EQ(r1, r2);

    const auto r_intersect = Rectangle::Intersect(r1, r2);
    ASSERT_TRUE(r_intersect.has_value());
    ASSERT_EQ(*r_intersect, r1);
    ASSERT_EQ(*r_intersect, r2);
}

TEST(Rectangle, NoInterceptions)
{
    const auto r1 = Rectangle(100, 100, 50, 50);
    const auto r2 = Rectangle(200, 200, 50, 50);

    const auto r_intersect = Rectangle::Intersect(r1, r2);
    ASSERT_TRUE(!r_intersect.has_value());
}

TEST(Rectangle, TouchButNoOverlapping)
{
    const auto r1 = Rectangle(100, 100, 50, 50);
    const auto r2 = Rectangle(150, 100, 50, 50);

    const auto r_intersect = Rectangle::Intersect(r1, r2);
    ASSERT_TRUE(!r_intersect.has_value());
}

TEST(Rectangle, RectanglesWithZeroWidth)
{
    const auto r1 = Rectangle(100, 100, 0, 50);
    const auto r2 = Rectangle(120, 120, 50, 50);

    const auto r_intersect = Rectangle::Intersect(r1, r2);
    ASSERT_TRUE(!r_intersect.has_value());
}

TEST(Rectangle, RectanglesWithZeroHeight)
{
    const auto r1 = Rectangle(100, 100, 50, 0);
    const auto r2 = Rectangle(120, 120, 50, 50);

    const auto r_intersect = Rectangle::Intersect(r1, r2);
    ASSERT_TRUE(!r_intersect.has_value());
}