#include <utility>
#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

template <class TestClass>
class UniquePtr {
public:
    UniquePtr(): ptr_(nullptr) {}
    UniquePtr(TestClass* class_): ptr_(class_) {}
    UniquePtr(const UniquePtr& ptr): ptr_(ptr.ptr_) {}
    UniquePtr(UniquePtr&& ptr) {
        ptr_ = std::move(ptr.ptr_);
        ptr.ptr_ = nullptr;
    }
    ~UniquePtr() {
        delete ptr_;
    }
    UniquePtr& operator =(const UniquePtr&) = default;
    UniquePtr& operator =(UniquePtr&& ptr) {
        this->~UniquePtr();
        ptr_ = std::move(ptr.ptr_);
        ptr.ptr_ = nullptr;
        return *this;
    }
    void reset(TestClass* class_ = nullptr) {
        this->~UniquePtr();
        ptr_ = class_;
    }
    TestClass* operator->() {
        return ptr_;
    }

private:
    TestClass* ptr_;
};

#endif
