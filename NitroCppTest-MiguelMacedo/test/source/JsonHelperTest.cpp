#include "JsonHelper.hpp"

#include <gtest/gtest.h>

TEST(JsonHelper, EmptyJson)
{
    const auto filepath = "../../../test/examples/test1.json";
    const auto opt = JsonHelper::ParseFilePath(filepath);

    ASSERT_EQ(opt, std::nullopt);
}

TEST(JsonHelper, InvalidPath)
{
    const auto filepath = "/invalid/path";
    const auto opt = JsonHelper::ParseFilePath(filepath);

    ASSERT_EQ(opt, std::nullopt);
}

TEST(JsonHelper, NotInt)
{
    const auto filepath = "../../../test/examples/test3.json";
    const auto opt = JsonHelper::ParseFilePath(filepath);

    ASSERT_EQ(opt, std::nullopt);
}

TEST(JsonHelper, MissingParam)
{
    const auto filepath = "../../../test/examples/test4.json";
    const auto opt = JsonHelper::ParseFilePath(filepath);

    ASSERT_EQ(opt, std::nullopt);
}

TEST(JsonHelper, ValidJson)
{
    const std::vector<Rectangle> expectedRects = {
        Rectangle(100, 100, 250, 80),
        Rectangle(120, 200, 250, 150),
        Rectangle(140, 160, 250, 100),
        Rectangle(160, 140, 350, 190)};

    const auto filepath = "../../../test/examples/test2.json";
    const auto opt = JsonHelper::ParseFilePath(filepath);

    ASSERT_TRUE(opt.has_value());
    ASSERT_EQ(*opt, expectedRects);
}
