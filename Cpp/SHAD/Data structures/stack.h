#include <vector>

#ifndef STACK_H
#define STACK_H

class Stack {
 public:
    Stack() : size_(0), container_(nullptr) {}
    void Push(int x);
    bool Pop();
    int Top() const;
    bool Empty() const;
    size_t Size() const;
 private:
    size_t size_;
    int* container_;
};

void Stack::Push(int x) {
    int* cont = new int[size_+1];
    int j = 0;
    for (size_t i = 0; i < size_; i++) {
        cont[i] = container_[i];
    }
    cont[size_] = x;
    container_ = cont;
    size_++;
}

bool Stack::Empty() const {
    if (size_ == 0)
        return true;
    else
        return false;
}

bool Stack::Pop() {
    if (!this->Empty()) {
        int* cont = new int[size_-1];
        size_--;
        for (size_t i = 0; i < size_; i++) {
            cont[i] = container_[i];
        }
        container_ = cont;
        return true;
    } else {
        return false;
    }
}

int Stack::Top() const {
    return container_[size_-1];
}

size_t Stack::Size() const {
    return size_;
}

#endif
