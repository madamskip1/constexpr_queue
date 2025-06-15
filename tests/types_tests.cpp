#include <gtest/gtest.h>
#include <type_traits>

#include <constexpr_queue.hpp>

TEST(ConstexprQueueTypesTest, PrimitiveType)
{
    constexpr MaCe::queue<int, 5> queue;
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
    EXPECT_EQ(queue.capacity(), 5);
}

TEST(ConstexprQueueTypesTest, StandradLibraryType)
{
    constexpr MaCe::queue<std::string, 5> queue;
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
    EXPECT_EQ(queue.capacity(), 5);
}

TEST(ConstexprQueueTypesTest, UserDefinedType_DefaultConstructible_TrivialyDestructible)
{
    class UserDefinedType
    {
        int value;
    };

    EXPECT_TRUE(std::is_default_constructible_v<UserDefinedType>);
    EXPECT_TRUE(std::is_trivially_destructible_v<UserDefinedType>);

    constexpr MaCe::queue<UserDefinedType, 5> queue;
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
    EXPECT_EQ(queue.capacity(), 5);
}

TEST(ConstexprQueueTypesTest, UserDefinedType_NonDefaultConstructible_TrivialyDestructible)
{
    class UserDefinedType
    {
    public:
        UserDefinedType(int v) : value(v) {}
        int value;
    };

    EXPECT_FALSE(std::is_default_constructible_v<UserDefinedType>);
    EXPECT_TRUE(std::is_trivially_destructible_v<UserDefinedType>);

    constexpr MaCe::queue<UserDefinedType, 5> queue;
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
    EXPECT_EQ(queue.capacity(), 5);
}

TEST(ConstexprQueueTypesTest, UserDefinedType_DefaultConstructible_NonTrivialDestructible)
{
    class UserDefinedType
    {
    public:
        ~UserDefinedType() {}; // Non-trivial destructor
        int value;
    };

    EXPECT_TRUE(std::is_default_constructible_v<UserDefinedType>);
    EXPECT_FALSE(std::is_trivially_destructible_v<UserDefinedType>);

    // Will not compile atm as MaCe::queue requires trivial destructibility
    constexpr MaCe::queue<UserDefinedType, 5> queue;
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
    EXPECT_EQ(queue.capacity(), 5);
}

TEST(ConstexprQueueTypesTest, UserDefinedType_NonDefaultConstructible_NonTrivialDestructible)
{
    class UserDefinedType
    {
    public:
        UserDefinedType(int v) : value(v) {}
        ~UserDefinedType() {}; // Non-trivial destructor
        int value;
    };

    EXPECT_FALSE(std::is_default_constructible_v<UserDefinedType>);
    EXPECT_FALSE(std::is_trivially_destructible_v<UserDefinedType>);

    constexpr MaCe::queue<UserDefinedType, 5> queue;
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
    EXPECT_EQ(queue.capacity(), 5);
}