# Constexpr Queue 

A small, header-only, `constexpr`-capable circular queue for use in compile-time. Designed for C++20 and up, with with a **std‑like interface**.

## Features

- `constexpr` push, pop, front, back, size, etc.
- Static capacity set at compile-time
- Single-file header-only library
- Zero dynamic allocation
- Optional comparison operators


## Why `std::variant`?

To store elements in a raw array (e.g., `T data_[Capacity]`), the type `T` must be **default-constructible** and **trivially destructible**, especially in `constexpr` contexts. However, `MaCe::constexpr_queue` aims to support types that **are not default-constructible and/or have non-trivial destructors**.

By using `std::variant`, we can:

- Avoid default-constructing T when initializing the array
- Explicitly manage the lifecycle of T values (emplace, pop, clear)
- Still remain within constexpr-friendly and type-safe boundaries
- Support non-default-constructible and non-trivially-destructible types

Instead of variants, we can do a union-based implementation probably. It may be more efficient, especially in terms of memory usage. Future version of Lib might use union for better performance, who knows?

## Requirements

- C++20 or higher — required because some operations on `std::variant` and `std::get` were not `constexpr` in C++17 and became `constexpr`-friendly in C++20
- No external dependencies

## Usage

### FetchContent

```cmake
include(FetchContent)

FetchContent_Declare(
  Constexpr_Queue
  GIT_REPOSITORY https://github.com/madamskip1/constexpr_queue.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(Constexpr_Queue)

target_link_libraries(your_target PRIVATE MaCe::Constexpr_Queue)
```

### C++

```cpp
consteval auto example_queue()
{
    MaCe::queue<int, 5> queue;
    queue.push(1);
    queue.push(2);

    queue.pop();

    queue.emplace(3);

    MaCe::queue<int, 5> other_queue;
    other_queue.push(4);

    queue.swap(other_queue);
    
    return queue;
}
```
