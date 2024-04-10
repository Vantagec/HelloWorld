#pragma once

#include <memory>

template<typename T, typename Allocator = std::allocator<T> >
class custom_list {
public:
    struct node_t {
        explicit node_t(const T& value): value_(value), next_(nullptr) {}
        explicit node_t(T&& value): value_(std::move(value)), next_(nullptr) {}

        T value_;
        node_t* next_;
    };

    using allocator_t = typename Allocator::template rebind<node_t>::other;

    class iterator_t {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        explicit iterator_t(node_t* ptr): ptr_(ptr) {}

        reference operator*() const {
            return ptr_->value_;
        }
        pointer operator->() {
            return &ptr_->value_;
        }
        iterator_t& operator++() {
            ptr_ = ptr_->next_;
            return *this;
        }
        iterator_t operator++(int) {
            iterator_t tmp = *this;
            ptr_ = ptr_->next_;
            return tmp;
        }
        friend bool operator!=(const iterator_t& lhs, const iterator_t& rhs) { return lhs.ptr_ != rhs.ptr_; }
        friend bool operator==(const iterator_t& lhs, const iterator_t& rhs) { return lhs.ptr_ == rhs.ptr_; }
    private:
        node_t* ptr_;
    };

    custom_list() = default;
    ~custom_list() {
        clear();
    }
    explicit custom_list(const custom_list<T, allocator_t>& rhs) {
        *this = rhs;
    }
    custom_list& operator=(const custom_list<T, allocator_t>& rhs) {
        clear();
        for (auto it = rhs.begin(); it != rhs.end(); ++it) {
            push_back(*it);
        }
    }
    explicit custom_list(custom_list<T, allocator_t>&& rhs) = delete;
    custom_list& operator=(custom_list<T, allocator_t>&& rhs) = delete;

    iterator_t begin() const { return iterator_t(head_); }
    iterator_t end() const { return iterator_t(nullptr); }

    T& front() const { return head_->value_; }
    T& back() const { return tail_->value_; }

    bool empty() const {
        return !head_;
    }

    size_t size() const {
        size_t n = 0;
        for (auto it = begin(); it != end(); ++it) {
            n++;
        }
        return n;
    }

    void push_back(const T& value) {
        auto node = allocator_.allocate(1);
        if (!node) {
            throw std::runtime_error("Failed to allocate memory in custom_list::push_back");
        }
        allocator_.construct(node, value);
        if (head_) {
            tail_->next_ = node;
        } else {
            head_ = node;
        }
        tail_ = node;
    }

    void pop_back() {
        auto del_node = tail_;
        if (del_node != head_) {
            auto it = begin();
            for (; it->next_ != tail_; ++it) {}
            tail_ = *it;
        }
        else {
            head_ = nullptr;
            tail_ = nullptr;
        }
        allocator_.destroy(del_node);
        allocator_.deallocate(del_node, 1);
    }

    void clear() {
        size_t n = 0;
        for (auto cur = head_; cur != nullptr; ++n) {
            auto next = cur->next_;
            allocator_.destroy(cur);
            allocator_.deallocate(cur, 1);
            cur = next;

        }
        head_ = nullptr;
        tail_ = nullptr;
    }

private:
    node_t* head_{nullptr};
    node_t* tail_{nullptr};
    allocator_t allocator_;
};
