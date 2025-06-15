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
        assert(head != tail);

        return std::get<T>(data_[head]);
    }

    constexpr const T &back() const
    {
        assert(head != tail);

        return std::get<T>(data_[tail - 1]);
    }

    // Capacity

    constexpr bool empty() const
    {
        return head == tail;
    }

    constexpr std::size_t size() const
    {
        if (head <= tail)
        {
            return tail - head;
        }
        else
        {
            return Capacity - head + tail;
        }
    }

    // Modifiers

    constexpr void push(const T &value)
    {
        assert(size() < Capacity);

        data_[tail] = value;
        tail = (tail + 1);
    }

    constexpr void emplace(T &&value)
    {
        assert(size() < Capacity);

        data_[tail] = std::forward<T>(value);
        tail = (++tail) % Capacity;
    }

    constexpr T pop()
    {
        assert(!empty());

        T value = std::get<T>(data_[head]);
        data_[head] = std::monostate{};
        head = (head + 1) % Capacity;
        return value;
    }

    constexpr void swap(constexpr_queue &other)
    {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(data_, other.data_);
    }

    // Non-member functions

    constexpr bool operator==(const constexpr_queue &other) const
    {
        if (size() != other.size())
        {
            return false;
        }

        auto i = head;
        auto j = other.head;
        while (i != tail)
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
        auto i = head;
        auto j = other.head;
        while (i != tail && j != other.tail)
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
        head = 0;
        tail = 0;
    }

private:
    std::variant<std::monostate, T> data_[Capacity];
    std::size_t head{0};
    std::size_t tail{0};
};