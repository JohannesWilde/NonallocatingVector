#include <cstdlib>
#include <iostream>
#include <vector>

template<class T>
struct ConstrainedAllocator
{
    typedef T value_type;

    ConstrainedAllocator(T * const address, size_t const count)
        : address_(address)
        , count_(count)
    {
        // intentionally empty
    }

    ConstrainedAllocator(ConstrainedAllocator const &) = default;
    ConstrainedAllocator(ConstrainedAllocator &&) = default;

    template<class U>
    constexpr ConstrainedAllocator(ConstrainedAllocator<U> const & other) noexcept
        : address_((T *)(other.address_))
        , count_(other.count_ * sizeof(U) / sizeof(T))
    {
        // intentionally empty
    }

    size_t max_size() const
    {
        return count_;
    }

    [[nodiscard]] T * allocate(std::size_t n)
    {
        if (max_size() < n)
        {
            throw std::bad_array_new_length();
        }

        if (nullptr == address_)
        {
            throw std::bad_alloc();
        }

        return address_;
    }

    void deallocate(T* p, std::size_t n) noexcept
    {
        // intentionally empty
    }

    T * const address_;
    size_t const count_;
};

template<class T, class U>
bool operator==(ConstrainedAllocator<T> const &, ConstrainedAllocator<U> const &) { return true; }

template<class T, class U>
bool operator!=(ConstrainedAllocator<T> const &, ConstrainedAllocator<U> const &) { return false; }

int main()
{
    std::vector<int> owningVector(/*n*/ 100, /*val*/ 0);

    {
        int * const pointer = owningVector.data();
        size_t const count = owningVector.size();

        ConstrainedAllocator<int> const allocator{pointer, count};

        std::vector<int, ConstrainedAllocator<int>> v{count, allocator};
        v[0] = 1;

        v.resize(5);
        try
        {
            v.resize(count + 1);
        }
        catch (std::exception const & e)
        {
            std::cout << "resize(101): " << e.what() << std::endl;
        }
    }

    std::cout << "v[0] = " << owningVector[0] << std::endl;

    return 0;
}
