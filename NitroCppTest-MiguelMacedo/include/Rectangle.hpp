#pragma once

#include <cstdint>
#include <optional>

struct Rectangle
{
    Rectangle(int32_t _x, int32_t _y, int32_t _w, int32_t _h);

    void Print() const;

    [[nodiscard]] static std::optional<Rectangle> Intersect(
        const Rectangle& r1, const Rectangle& r2) noexcept;

    bool operator==(const Rectangle& other) const;

    int32_t x;
    int32_t y;
    int32_t w;
    int32_t h;
    int32_t id;

  private:
    static int s_nextId;
};