#include <constexpr_queue.hpp>


namespace {
    consteval int test_consteval_queue_front()
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
}

int main()
{
    volatile constexpr auto x = test_consteval_queue_front();
    return x;
}

/*
    Should produce something like:

    main:
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], 4
        mov     eax, 4
        pop     rbp
        ret
*/