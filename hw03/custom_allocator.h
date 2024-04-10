#pragma once

#include <memory>
#include <array>

template<typename T, size_t N>
class custom_allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = typename std::pointer_traits<pointer>::difference_type;

    template<typename U>
    struct rebind {
        using other = custom_allocator<U, N>;
    };

    custom_allocator() = default;
    custom_allocator(const custom_allocator<T, N>&) noexcept {}

    ~custom_allocator() {
        if (buffer_) {
            std::free(buffer_);
        }
    }

    bool operator == (const custom_allocator<T, N>&) { return false; }
    bool operator != (const custom_allocator<T, N>&) { return true; }

    pointer allocate(size_t n) {
        if (n == 0) {
            return nullptr;
        }
        if (!buffer_) {
            buffer_ = reinterpret_cast<T*>(std::malloc(N * sizeof(T)));
            if (!buffer_) {
                std::cerr << "custom_allocator failed to allocate memory!\n";
                throw std::bad_alloc();
            }
        }
        if (size_ + n > N) {
            std::cerr << "custom_allocator ran out available memory! capacity: " << 
                         N << " current size: " << size_ << " requested size: " << n << "\n";
            throw std::bad_alloc();
        }
        pointer cur_ptr = find_free_memory(n);
        if (!cur_ptr) {
            std::cerr << "custom_allocator failed to find available memory! capacity: " << 
                         N << " current size: " << size_ << " requested size: " << n << "\n";
            throw std::bad_alloc();
        }
        set_used(cur_ptr, n, true);
        size_ += n;
        return cur_ptr;
    }

    void deallocate(pointer ptr, size_t n) {
        if (ptr < buffer_) {
            std::cerr << "custom_allocator failed to deallocate invalid pointer! pointer: " <<  ptr << "\n";
            throw std::bad_alloc();
        }
        size_t ind = static_cast<size_t>((ptr - buffer_) / sizeof(T));
        set_used(ind, n, false);
        size_ -= std::min(size_, n);
    }

    template<typename U, typename ...Args>
    void construct(U *ptr, Args &&...args) {
        new(ptr) U(std::forward<Args>(args)...);
    }

    void destroy(pointer ptr) {
        ptr->~T();
    }

private:
    pointer find_free_memory(size_t n) {
        size_t i_cur = 0;
        size_t n_cur = 0;
        for (size_t i = 0; i < N; ++i) {
            if (used_[i]) {
                i_cur = i + 1;
                n_cur = 0;
                continue;
            }
            else {
                ++n_cur;
            }
            if (n_cur == n) {
                return &buffer_[i_cur];
            }
        }
        return nullptr;
    }

    void set_used(size_t i_cur, size_t n, bool is_used=true) {
        size_t i_end = i_cur + n; 
        if (i_end > N) {
            std::cerr << "custom_allocator trying to occupy memory out of range! capacity: " << 
                         N << " starting index: " << i_cur << " requested size: " << n << "\n";
            throw std::out_of_range("custom_allocator trying to occupy memory out of range!");
        }
        for (; i_cur < i_end; ++i_cur) {
            used_[i_cur] = is_used;
        }
    }

    void set_used(pointer ptr, size_t n, bool is_used=true) {
        if (ptr < buffer_) {
            std::cerr << "custom_allocator failed to allocate for invalid pointer! pointer: " <<  ptr << "\n";
            throw std::bad_alloc();
        }
        set_used(ptr - buffer_, n, is_used);
    }

private:
    T* buffer_{nullptr};
    bool used_[N] = {};
    size_t size_{0};
};
