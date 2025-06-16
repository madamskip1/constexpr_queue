#include <algorithm>
#include <cstddef>
#include <utility>
#include <variant>
#include <cassert>

namespace MaCe // MAdamski-Constexpr
{
template <typename T, std::size_t Capacity>
class queue
{
public:
    constexpr queue() = default;

    template <typename... Args>
        requires(sizeof...(Args) > 1 || !std::is_same_v<std::decay_t<std::tuple_element_t<0, std::tuple<Args...>>>, queue>)
    constexpr queue(Args &&...args)
    {
        static_assert(sizeof...(Args) <= Capacity, "Too many arguments");
        (emplace(std::forward<Args>(args)), ...);
    }

    // Element access

    constexpr const T &front() const
    {
        assert(!empty());

        return std::get<T>(data_[head_]);
    }

    constexpr const T &back() const
    {
        assert(!empty());
        return std::get<T>(data_[(tail_ + Capacity - 1) % Capacity]);
    }

    // Capacity

    constexpr bool empty() const
    {
        return size_ == 0;
    }

    constexpr std::size_t size() const
    {
        return size_;
    }

    // Modifiers

    constexpr void push(const T &value)
    {
        assert(size_ < Capacity);

        data_[tail_] = value;
        tail_ = (tail_ + 1) % Capacity;
        ++size_;
    }

    constexpr void emplace(T &&value)
    {
        assert(size_ < Capacity);

        data_[tail_] = std::forward<T>(value);
        tail_ = (++tail_) % Capacity;
        ++size_;
    }

    constexpr T pop()
    {
        assert(!empty());

        T value = std::get<T>(data_[head_]);
        data_[head_] = std::monostate{};
        head_ = (head_ + 1) % Capacity;
        --size_;
        return value;
    }

    constexpr void swap(queue &other)
    {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }

    // Non-member functions

    constexpr bool operator==(const queue &other) const
    {
        if (size_ != other.size())
        {
            return false;
        }

        auto head = head_;
        auto otherHead = other.head_;

        for (auto i = std::size_t{0}; i < size_; ++i)
        {
            if (data_[head] != other.data_[otherHead])
            {
                return false;
            }
            head = (head + 1) % Capacity;
            otherHead = (otherHead + 1) % other.capacity();
        }

        return true;
    }

    constexpr bool operator!=(const queue &other) const
    {
        return !(*this == other);
    }

    constexpr bool operator<(const queue &other) const
    {
        auto head = head_;
        auto otherHead = other.head_;

        for (auto i = std::size_t{0}; i < std::min(size_, other.size_); ++i)
        {
            if (data_[head] < other.data_[otherHead])
            {
                return true;
            }
            if (data_[head] > other.data_[otherHead])
            {
                return false;
            }

            head = (head + 1) % Capacity;
            otherHead = (otherHead + 1) % other.capacity();
        }

        return false;
    }

    constexpr bool operator<=(const queue &other) const
    {
        return *this < other || *this == other;
    }

    constexpr bool operator>(const queue &other) const
    {
        return !(*this <= other);
    }

    constexpr bool operator>=(const queue &other) const
    {
        return !(*this < other);
    }

    // Additional non-standard methods

    constexpr std::size_t capacity() const
    {
        return Capacity;
    }

    constexpr void clear()
    {
        auto head = head_;
        for (auto i = std::size_t{0}; i < size_; ++i)
        {
            data_[head] = std::monostate{};

            head = (head + 1) % Capacity;
        }
        head_ = 0;
        tail_ = 0;
        size_ = 0;
    }

private:
    std::variant<std::monostate, T> data_[Capacity];
    std::size_t head_{0};
    std::size_t tail_{0};
    std::size_t size_{0};
};
}