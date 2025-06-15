#include <gtest/gtest.h>

#include <constexpr_queue.hpp>

TEST(ConstexprQueueFunctionalityTest, Push)
{
    constexpr_queue<int, 5> queue;
    queue.push(55);
    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), 55);
    EXPECT_EQ(queue.back(), 55);

    queue.push(66);
    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 2);
    EXPECT_EQ(queue.front(), 55);
    EXPECT_EQ(queue.back(), 66);
}

TEST(ConstexprQueueFunctionalityTest, Pop)
{
    constexpr_queue<int, 5> queue;
    queue.push(55);
    queue.push(66);

    int popped_value = queue.pop();
    EXPECT_EQ(popped_value, 55);
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), 66);
    EXPECT_EQ(queue.back(), 66);

    popped_value = queue.pop();
    EXPECT_EQ(popped_value, 66);
    EXPECT_TRUE(queue.empty());
}

TEST(ConstexprQueueFunctionalityTest, Emplace)
{
    constexpr_queue<int, 5> queue;
    queue.emplace(77);
    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), 77);
    EXPECT_EQ(queue.back(), 77);

    queue.emplace(88);
    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 2);
    EXPECT_EQ(queue.front(), 77);
    EXPECT_EQ(queue.back(), 88);
}

TEST(ConstexprQueueFunctionalityTest, Swap)
{
    constexpr_queue<int, 5> queue1;
    queue1.push(1);
    queue1.push(2);

    constexpr_queue<int, 5> queue2;
    queue2.push(3);
    queue2.push(4);

    queue1.swap(queue2);

    EXPECT_EQ(queue1.size(), 2);
    EXPECT_EQ(queue1.front(), 3);
    EXPECT_EQ(queue1.back(), 4);

    EXPECT_EQ(queue2.size(), 2);
    EXPECT_EQ(queue2.front(), 1);
    EXPECT_EQ(queue2.back(), 2);
}

TEST(ConstexprQueueFunctionalityTest, OperatorEquality)
{
    constexpr_queue<int, 5> queue1;
    queue1.push(1);
    queue1.push(2);

    constexpr_queue<int, 5> queue2;
    queue2.push(1);
    queue2.push(2);

    EXPECT_TRUE(queue1 == queue2);
    EXPECT_FALSE(queue1 != queue2);

    queue2.push(3);
    EXPECT_FALSE(queue1 == queue2);
    EXPECT_TRUE(queue1 != queue2);
}
TEST(ConstexprQueueFunctionalityTest, OperatorLessThan)
{
    constexpr_queue<int, 5> queue1;
    queue1.push(1);
    queue1.push(2);

    constexpr_queue<int, 5> queue2;
    queue2.push(1);
    queue2.push(3);

    EXPECT_TRUE(queue1 < queue2);
    EXPECT_TRUE(queue1 <= queue2);

    queue2.pop();
    EXPECT_TRUE(queue1 < queue2);
    EXPECT_TRUE(queue1 <= queue2);
}

TEST(ConstexprQueueFunctionalityTest, OperatorGreaterThan)
{
    constexpr_queue<int, 5> queue1;
    queue1.push(1);
    queue1.push(2);

    constexpr_queue<int, 5> queue2;
    queue2.push(1);
    queue2.push(3);

    EXPECT_FALSE(queue1 > queue2);
    EXPECT_FALSE(queue1 >= queue2);

    queue1.pop();
    EXPECT_TRUE(queue1 > queue2);
    EXPECT_TRUE(queue1 >= queue2);
}

TEST(ConstexprQueueFunctionalityTest, FullQueue)
{
    constexpr_queue<int, 3> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.back(), 3);

    EXPECT_DEATH({ queue.push(4); }, ".*");
}

TEST(ConstexprQueueFunctionalityTest, FullQueue_HeadNotFirst)
{
    constexpr_queue<int, 3> queue;
    queue.push(1);
    queue.push(2);
    queue.pop(); // Remove 1
    queue.push(3);
    queue.push(4);

    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 2);
    EXPECT_EQ(queue.back(), 4);

    EXPECT_DEATH({ queue.push(5); }, ".*");
}

TEST(ConstexprQueueFunctionalityTest, PopEmptyQueue)
{
    constexpr_queue<int, 5> queue;

    EXPECT_TRUE(queue.empty());
    EXPECT_DEATH({ queue.pop(); }, ".*");
}

TEST(ConstexprQueueFunctionalityTest, ClearQueue)
{
    constexpr_queue<int, 5> queue;
    queue.push(1);
    queue.push(2);
    queue.clear();

    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
    EXPECT_DEATH({ queue.front(); }, ".*");
    EXPECT_DEATH({ queue.back(); }, ".*");
}