#include <cstddef>
#include <utility>
#include <variant>
#include <cassert>

template <typename T, std::size_t Capacity>
class constexpr_queue
{
public:
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
        return size() == 0;
    }

    constexpr std::size_t size() const
    {
        return size_;
    }

    // Modifiers

    constexpr void push(const T &value)
    {
        assert(size() < Capacity);

        data_[tail_] = value;
        tail_ = (tail_ + 1) % Capacity;
        ++size_;
    }

    constexpr void emplace(T &&value)
    {
        assert(size() < Capacity);

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

    constexpr void swap(constexpr_queue &other)
    {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }

    // Non-member functions

    constexpr bool operator==(const constexpr_queue &other) const
    {
        if (size() != other.size())
        {
            return false;
        }

        auto i = head_;
        auto j = other.head_;
        while (i != tail_)
        {
            if (data_[i] != other.data_[j])
            {
                return false;
            }
            i = ++i % Capacity;
            j = ++j % other.capacity();
        }
        return true;
    }

    constexpr bool operator!=(const constexpr_queue &other) const
    {
        return !(*this == other);
    }

    constexpr bool operator<(const constexpr_queue &other) const
    {
        auto i = head_;
        auto j = other.head_;
        while (i != tail_ && j != other.tail_)
        {
            if (data_[i] < other.data_[j])
            {
                return true;
            }
            else if (data_[i] > other.data_[j])
            {
                return false;
            }
            i = ++i % Capacity;
            j = ++j % other.capacity();
        }
        return size() < other.size();
    }

    constexpr bool operator<=(const constexpr_queue &other) const
    {
        return *this < other || *this == other;
    }

    constexpr bool operator>(const constexpr_queue &other) const
    {
        return !(*this <= other);
    }

    constexpr bool operator>=(const constexpr_queue &other) const
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