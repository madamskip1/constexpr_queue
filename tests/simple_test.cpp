#include <gtest/gtest.h>

#include <constexpr_queue.hpp>

TEST(ConstexprQueueTest, Size_0_construction)
{
    constexpr constexpr_queue<int, 0> queue;
    EXPECT_EQ(queue.size(), 0);
    EXPECT_EQ(queue.capacity(), 0);
    EXPECT_TRUE(queue.empty());
}