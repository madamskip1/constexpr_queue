#include <constexpr_queue.hpp>


namespace {
    consteval int test_consteval_queue_1()
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

    consteval bool test_consteval_queue_2()
    {
        constexpr_queue<int, 5> queue;
        queue.push(1);
        queue.push(2);

        queue.pop();

        queue.emplace(3);

        queue.clear();

        return queue.empty();
    }
}

int main()
{
    volatile constexpr auto x = test_consteval_queue_1();
    constexpr auto y = test_consteval_queue_2();
    return x;
}

/*
    Should produce something like:

    main:
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], 4
        mov     BYTE PTR [rbp-5], 1
        mov     eax, 4
        pop     rbp
        ret
*/