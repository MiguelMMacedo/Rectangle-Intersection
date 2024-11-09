#include <algorithm>

#include "RectangleIntersection.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "utilities/TestingHelper.hpp"

// Useful for debugging since it pinpoints indices and values where actual and
// expected data are different
MATCHER_P(EqualsRectangleIntersections, expected, "")
{
    const auto& actual = arg;

    if (actual.size() != expected.size())
    {
        *result_listener << "\nVector size mismatch. Expected: "
                         << expected.size() << ", actual: " << actual.size();
        return false;
    }

    for (size_t i = 0; i < expected.size(); ++i)
    {
        if (!(actual[i] == expected[i]))
        {
            *result_listener << "\nMismatch at index " << i << "\n"
                             << "Expected: " << expected[i] << "\n"
                             << "Actual: " << actual[i];
            return false;
        }
    }
    return true;
}

void SortAndCheckIntersections(
    std::vector<RectangleIntersection> intersections,
    std::vector<RectangleIntersection> expected_intersections)
{
    // sort both vector so they share same order
    auto sort_predicate = [](const RectangleIntersection& i1, const RectangleIntersection& i2)
    { 
        return i1.ids < i2.ids; 
    };

    std::ranges::sort(intersections, sort_predicate);
    std::ranges::sort(expected_intersections, sort_predicate);

    ASSERT_THAT(intersections, EqualsRectangleIntersections(expected_intersections));
}

TEST(RectangleIntersection, CheckEqualsOperator)
{
    // identical rectangles with different IDs
    const auto r1 = Rectangle(100, 100, 50, 50);
    const auto r2 = Rectangle(100, 100, 50, 50);

    const auto r1_intersection = RectangleIntersection({1, 2}, r1);
    const auto r2_intersection = RectangleIntersection({1, 2}, r2);

    // check if ID of rectangles does not affect == operator
    ASSERT_EQ(r1_intersection, r2_intersection);
}

TEST(RectangleIntersection, SimpleIntersection)
{
    const auto r1 = Rectangle(100, 100, 50, 50);
    const auto r2 = Rectangle(120, 120, 50, 50);

    const auto expected_r = Rectangle(120, 120, 30, 30);
    const std::set<int32_t> expected_ids = {r1.id, r2.id};
    const auto expected_intersection = RectangleIntersection(expected_ids, expected_r);

    const auto intersections = RectangleIntersection::FindIntersections({r1, r2});
    SortAndCheckIntersections(intersections, {expected_intersection});
}

TEST(RectangleIntersection, SimpleThreeRectangleIntersection)
{
    const auto r1 = Rectangle(5, 2, 3, 3);
    const auto r2 = Rectangle(7, 4, 2, 3);
    const auto r3 = Rectangle(5, 6, 3, 2);

    const std::vector<RectangleIntersection> expected_intersections = {
        RectangleIntersection({r1.id, r2.id}, Rectangle(7, 4, 1, 1)),
        RectangleIntersection({r2.id, r3.id}, Rectangle(7, 6, 1, 1))};

    const auto intersections = RectangleIntersection::FindIntersections({r1, r2, r3});
    SortAndCheckIntersections(intersections, expected_intersections);
}

TEST(RectangleIntersection, MultipleOverlappingThreeRectangleIntersection)
{
    const auto r1 = Rectangle(2, 1, 4, 3);
    const auto r2 = Rectangle(4, 2, 4, 3);
    const auto r3 = Rectangle(3, 3, 2, 3);

    const std::vector<RectangleIntersection> expected_intersections = {
        RectangleIntersection({r1.id, r2.id}, Rectangle(4, 2, 2, 2)),
        RectangleIntersection({r1.id, r3.id}, Rectangle(3, 3, 2, 1)),
        RectangleIntersection({r2.id, r3.id}, Rectangle(4, 3, 1, 2)),
        RectangleIntersection({r1.id, r2.id, r3.id}, Rectangle(4, 3, 1, 1)),
    };

    const auto intersections = RectangleIntersection::FindIntersections({r1, r2, r3});
    SortAndCheckIntersections(intersections, expected_intersections);
}

TEST(RectangleIntersection, FourRectangleIntersection)
{
    const auto r1 = Rectangle(2, 3, 7, 3);
    const auto r2 = Rectangle(4, 4, 8, 3);
    const auto r3 = Rectangle(6, 1, 2, 7);
    const auto r4 = Rectangle(4, 2, 2, 3);

    const std::vector<RectangleIntersection> expected_intersections = {
        RectangleIntersection({r1.id, r2.id}, Rectangle(4, 4, 5, 2)),
        RectangleIntersection({r1.id, r3.id}, Rectangle(6, 3, 2, 3)),
        RectangleIntersection({r2.id, r3.id}, Rectangle(6, 4, 2, 3)),
        RectangleIntersection({r1.id, r2.id, r3.id}, Rectangle(6, 4, 2, 2)),
        RectangleIntersection({r1.id, r4.id}, Rectangle(4, 3, 2, 2)),
        RectangleIntersection({r2.id, r4.id}, Rectangle(4, 4, 2, 1)),
        RectangleIntersection({r1.id, r2.id, r4.id}, Rectangle(4, 4, 2, 1))
    };

    const auto intersections = RectangleIntersection::FindIntersections({r1, r2, r3, r4});
    SortAndCheckIntersections(intersections, expected_intersections);
}
