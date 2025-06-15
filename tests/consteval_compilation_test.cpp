#include <constexpr_queue.hpp>


namespace {
    consteval int test_consteval_queue_push_pop_operators()
    {
        constexpr_queue<int, 5> queue;
        queue.push(1);
        queue.push(2);

        queue.pop();

        queue.emplace(3);

        constexpr_queue<int, 5> other_queue;
        other_queue.push(4);

        queue.swap(other_queue);

        bool is_equal = (queue == other_queue);
        bool is_not_equal = (queue != other_queue);
        bool is_less = (queue < other_queue);
        bool is_less_equal = (queue <= other_queue);
        bool is_greater = (queue > other_queue);
        bool is_greater_equal = (queue >= other_queue);

        return queue.front();
    }

    consteval bool test_consteval_queue_clear()
    {
        constexpr_queue<int, 5> queue;
        queue.push(1);
        queue.push(2);

        queue.pop();

        queue.emplace(3);

        queue.clear();

        return queue.empty();
    }

    consteval bool test_consteval_queue_copy()
    {
        constexpr_queue<int, 5> original;
        original.push(10);
        original.push(20);

        constexpr_queue<int, 5> copy = original;

        constexpr_queue<int, 5> assigned;
        assigned = original;

        return assigned == original && copy == original;
    }

    consteval bool test_consteval_queue_move()
    {
        constexpr_queue<int, 5> original;
        original.push(10);
        original.push(20);

        constexpr_queue<int, 5> moved = std::move(original);

        constexpr_queue<int, 5> another;
        another = std::move(moved);

        return original.empty();
    }
}

int main()
{
    volatile constexpr auto x = test_consteval_queue_push_pop_operators();
    volatile constexpr auto y = test_consteval_queue_clear();
    volatile constexpr auto z = test_consteval_queue_copy();
    volatile constexpr auto w = test_consteval_queue_move();
    return x;
}

/*
    Should produce something like:

    main:
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], 4    -> x
        mov     BYTE PTR [rbp-5], 1     -> y
        mov     BYTE PTR [rbp-6], 1     -> z
        mov     BYTE PTR [rbp-7], 0     -> w
        mov     eax, DWORD PTR [rbp-4]
        pop     rbp
        ret
*/