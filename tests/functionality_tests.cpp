#include <gtest/gtest.h>

#include <MaCe/constexpr_queue.hpp>

TEST(ConstexprQueueFunctionalityTest, Push)
{
    MaCe::queue<int, 5> queue;
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
    MaCe::queue<int, 5> queue;
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
    MaCe::queue<int, 5> queue;
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
    MaCe::queue<int, 5> queue1;
    queue1.push(1);
    queue1.push(2);

    MaCe::queue<int, 5> queue2;
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

TEST(ConstexprQueueFunctionalityTest, Swap_DifferentHeadTail)
{
    MaCe::queue<int, 3> q1;
    q1.push(1);
    q1.push(2);
    q1.pop();
    q1.push(3);
    q1.push(4);

    MaCe::queue<int, 3> q2;
    q2.push(5);
    q2.push(6);

    q1.swap(q2);

    EXPECT_EQ(q1.size(), 2);
    EXPECT_EQ(q1.front(), 5);
    EXPECT_EQ(q1.back(), 6);

    EXPECT_EQ(q2.size(), 3);
    EXPECT_EQ(q2.front(), 2);
    EXPECT_EQ(q2.back(), 4);
}

TEST(ConstexprQueueFunctionalityTest, OperatorEquality)
{
    MaCe::queue<int, 5> queue1;
    queue1.push(1);
    queue1.push(2);

    MaCe::queue<int, 5> queue2;
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
    MaCe::queue<int, 5> queue1;
    queue1.push(1);
    queue1.push(2);

    MaCe::queue<int, 5> queue2;
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
    MaCe::queue<int, 5> queue1;
    queue1.push(1);
    queue1.push(2);

    MaCe::queue<int, 5> queue2;
    queue2.push(1);
    queue2.push(3);

    EXPECT_FALSE(queue1 > queue2);
    EXPECT_FALSE(queue1 >= queue2);

    queue1.pop();
    EXPECT_TRUE(queue1 > queue2);
    EXPECT_TRUE(queue1 >= queue2);
}

TEST(ConstexprQueueFunctionalityTest, Operators_WithDifferHeadTail)
{
    MaCe::queue<int, 3> queue1;
    queue1.push(1);
    queue1.push(2);
    queue1.pop();
    queue1.push(3);
    queue1.push(4);

    MaCe::queue<int, 3> queue2;
    queue2.push(4);
    queue2.push(5);

    EXPECT_FALSE(queue1 == queue2);
    EXPECT_TRUE(queue1 != queue2);
    EXPECT_TRUE(queue1 < queue2);
    EXPECT_TRUE(queue1 <= queue2);
    EXPECT_FALSE(queue1 > queue2);
    EXPECT_FALSE(queue1 >= queue2);
}

TEST(ConstexprQueueFunctionalityTest, FullQueue)
{
    MaCe::queue<int, 3> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.back(), 3);

    EXPECT_DEATH({ queue.push(4); }, ".*");
}

TEST(ConstexprQueueFunctionalityTest, WrapAround)
{
    MaCe::queue<int, 3> queue;
    queue.push(1);
    queue.push(2);
    queue.pop();
    queue.push(3);
    queue.push(4);

    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 2);
    EXPECT_EQ(queue.back(), 4);
}

TEST(ConstexprQueueFunctionalityTest, FullQueue_WrapAround)
{
    MaCe::queue<int, 3> queue;
    queue.push(1);
    queue.push(2);
    queue.pop();
    queue.push(3);
    queue.push(4);

    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 2);
    EXPECT_EQ(queue.back(), 4);

    EXPECT_DEATH({ queue.push(5); }, ".*");
}

TEST(ConstexprQueueFunctionalityTest, Pop_EmptyQueue)
{
    MaCe::queue<int, 5> queue;

    EXPECT_TRUE(queue.empty());
    EXPECT_DEATH({ queue.pop(); }, ".*");
}

TEST(ConstexprQueueFunctionalityTest, ClearQueue)
{
    MaCe::queue<int, 5> queue;
    queue.push(1);
    queue.push(2);
    queue.clear();

    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
    EXPECT_DEATH({ queue.front(); }, ".*");
    EXPECT_DEATH({ queue.back(); }, ".*");
}

TEST(ConstexprQueueFunctionalityTest, ClearAfter_WrapAround)
{
    MaCe::queue<int, 3> queue;
    queue.push(1);
    queue.push(2);
    queue.pop();
    queue.push(3);
    queue.push(4); // should wrap
    queue.clear();

    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
    EXPECT_DEATH({ queue.front(); }, ".*");
}

TEST(ConstexprQueueFunctionalityTest, Operators_FullQueue)
{
    MaCe::queue<int, 3> queue1;
    queue1.push(1);
    queue1.push(2);
    queue1.push(3);

    MaCe::queue<int, 3> queue2;
    queue2.push(4);
    queue2.push(5);
    queue2.push(6);

    EXPECT_FALSE(queue1 == queue2);
    EXPECT_TRUE(queue1 != queue2);
    EXPECT_TRUE(queue1 < queue2);
    EXPECT_TRUE(queue1 <= queue2);
    EXPECT_FALSE(queue1 > queue2);
    EXPECT_FALSE(queue1 >= queue2);
}

TEST(ConstexprQueueFunctionalityTest, CopyConstructorAndAssignment)
{
    MaCe::queue<int, 5> original;
    original.push(10);
    original.push(20);

    MaCe::queue<int, 5> copy = original;
    EXPECT_EQ(copy, original);

    MaCe::queue<int, 5> assigned;
    assigned = original;
    EXPECT_EQ(assigned, original);
}

TEST(ConstexprQueueFunctionalityTest, MoveConstructorAndAssignment)
{
    MaCe::queue<int, 5> original;
    original.push(10);
    original.push(20);

    MaCe::queue<int, 5> moved = std::move(original);
    EXPECT_EQ(moved.size(), 2);
    EXPECT_EQ(moved.front(), 10);
    EXPECT_EQ(moved.back(), 20);

    MaCe::queue<int, 5> another;
    another = std::move(moved);
    EXPECT_EQ(another.size(), 2);
    EXPECT_EQ(another.front(), 10);
    EXPECT_EQ(another.back(), 20);
}

TEST(ConstexprQueueFunctionalityTest, CompileTimeUsage)
{
    constexpr auto build_queue = []
    {
        MaCe::queue<int, 3> queue;
        auto queu2 = queue;
        queu2.push(1);
        queu2.push(2);
        return queu2;
    };

    constexpr auto queue = build_queue();
    static_assert(queue.size() == 2, "Queue should contain two elements");
    static_assert(queue.front() == 1, "Front should be 1");
    static_assert(queue.back() == 2, "Back should be 2");
}

TEST(ConstexprQueueFunctionalityTest, ListInitialization_Full)
{
    MaCe::queue<int, 5> queue{1, 2, 3};
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.back(), 3);
}

TEST(ConstexprQueueFunctionalityTest, ListInitialization_Empty)
{
    MaCe::queue<int, 5> queue{};
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
}

TEST(ConstexprQueueFunctionalityTest, ListInitialization_PartialFill)
{
    MaCe::queue<int, 5> queue{1, 2};
    EXPECT_EQ(queue.size(), 2);
    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.back(), 2);
}