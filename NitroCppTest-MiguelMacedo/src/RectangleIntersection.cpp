#include <iostream>
#include <map>
#include <vector>

#include "RectangleIntersection.hpp"

RectangleIntersection::RectangleIntersection(const std::set<int32_t>& _ids,
                                             const Rectangle& _rectangle)
    : ids {_ids}
    , rectangle {_rectangle}
{
}

void RectangleIntersection::Print() const
{
    if (ids.size() < 2)
    {
        return;
    }

    std::cout << "\tBetween rectangle ";

    auto it = ids.begin();
    const auto last_it = ids.cend();

    for (auto i = it; i != last_it; i++)
    {
        if (std::distance(i, last_it) == 1)
        {
            std::cout << *i << " ";
        }
        else if (std::distance(i, last_it) == 2)
        {
            std::cout << *i << " and ";
        }
        else
        {
            std::cout << *i << ", ";
        }
    }

    std::cout << "at (" << rectangle.x << "," << rectangle.y
              << "), w=" << rectangle.w << ", h=" << rectangle.h << ".\n";
}

std::vector<RectangleIntersection> RectangleIntersection::FindIntersections(
    const std::vector<Rectangle>& rectangles) noexcept
{
    // Map to store all found intersections
    // Key: Set of rectangle IDs involved in the intersection
    // Value: The intersecting rectangle
    std::map<std::set<int32_t>, Rectangle> intersectionsMap;

    // Find pairwise intersections
    for (size_t i = 0; i < rectangles.size(); i++)
    {
        for (size_t j = i + 1; j < rectangles.size(); j++)
        {
            if (const auto intersect_rect =
                    Rectangle::Intersect(rectangles[i], rectangles[j]))
            {
                intersectionsMap.emplace(
                    std::set<int32_t>{rectangles[i].id, rectangles[j].id},
                    intersect_rect.value());
            }
        }
    }

    // Find intersections of 3 or more rectangles
    bool new_intersection_found;
    do
    {
        new_intersection_found = false;

        // Use separate map to correctly handle cases where new intersections are formed
        // from intersections discovered in the same iteration 
        std::map<std::set<int32_t>, Rectangle> new_intersections;

        // Iterate over all pairs of existing intersection
        for (const auto& [ids1, rect1] : intersectionsMap)
        {
            for (const auto& [ids2, rect2] : intersectionsMap)
            {
                // Skip if we're comparing an intersection with itself
                if (ids1 == ids2)
                {
                    continue;
                }

                // Check if these two intersections overlap
                if (const auto intersect_rect = Rectangle::Intersect(rect1, rect2))
                {
                    // Combine the IDs of both intersecting rectangles
                    std::set<int32_t> combined_ids;
                    combined_ids.insert(ids1.begin(), ids1.end());
                    combined_ids.insert(ids2.begin(), ids2.end());
                    
                    // Check if this is a new intersection
                    if (!intersectionsMap.contains(combined_ids) && !new_intersections.contains(combined_ids))
                    {
                        // Add the new intersection
                        new_intersections.emplace(combined_ids, *intersect_rect);
                        
                        // Set flag to true to check for new possible intersections
                        new_intersection_found = true;
                    }
                }
            }
        }

        // Merge new intersections to the main intersections map
        intersectionsMap.merge(new_intersections);

    } while (new_intersection_found);

    // Collect results
    std::vector<RectangleIntersection> intersected_rectangles;
    intersected_rectangles.reserve(intersectionsMap.size());

    for (const auto& [ids, intersection] : intersectionsMap)
    {
        intersected_rectangles.emplace_back(ids, intersection);
    }

    return intersected_rectangles;
}