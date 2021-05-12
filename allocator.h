#pragma once
#include <cstddef>
#include <exception>
#include <stdexcept>
#include <memory>

namespace otus {

template<class T, size_t Capacity>
class Allocator {
public:
    using value_type = T;

    explicit Allocator() : size_{0}, allocated_memory_(static_cast<T*>(malloc(Capacity * sizeof(T)))) {
    }

    template <class U>
    explicit Allocator(const Allocator<U, Capacity>&) : Allocator() {
    }

    Allocator(Allocator&& other) noexcept : size_{other.size_}, allocated_memory_{other.allocated_memory_} {
        other.size_ = 0;
        other.allocated_memory_ = nullptr;
    }

    Allocator& operator=(const Allocator&) = delete;
    Allocator& operator=(Allocator&&) = delete;

    ~Allocator() {
        free(allocated_memory_);
    }

    T* allocate(const size_t count) {
        if (size_ + count > Capacity) {
            throw std::runtime_error("trying to allocate too many elements");
        }
        T* ptr = allocated_memory_ + size_;
        size_ += count;
        return ptr;
    }

    void deallocate(T* /* ptr */, size_t /* count */) {
        // do nothing, deallocate is done in a destructor
    }

    template<typename U>
    struct rebind {
        typedef Allocator<U, Capacity> other;
    };

private:
    size_t size_ = 0;
    T* allocated_memory_ = nullptr;

    template <class U, size_t C>
    friend class Allocator;
};

}  // namespace otus