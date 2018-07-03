#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

class Vector {
public:
    Vector() : size_(0), capacity_(1), container_(new int[1]) {}

    ~Vector() {
        delete[] container_;
    }

    void pop_back() {
        assert (size_ > 0);
        size_--;
    }

    void push_back(int x) {
        if (size_ < capacity_) {
            this->container_[size_] = x;
            size_++;
        }
        else {
            capacity_ *= 2;
            int* cont = new int[capacity_];
            for (size_t i = 0; i < size_; i++) {
                cont[i] = container_[i];
            }
                cont[size_] = x;
                size_++;
                delete[] container_;
                container_ = cont;
        }
    }

    int at(size_t index) const {
        return container_[index];
    }

    size_t size() const{
        return size_;
    }

private:    
    size_t size_;
    size_t capacity_;
    int* container_;
};

class Stack {

public:
    void push(int& x) {
        all_.push_back(x);
    }

    void pop() {
        all_.pop_back();
    }

    int top() const {
        return all_.at(all_.size()-1);
    }

    size_t size() const {
        return all_.size();
    }

private:
    Vector all_;
};

class StackWithMaximum {
public:
    void push(int& x) {
        main.push(x);
        int temp = std::max(x, max_.top());
        max_.push(temp);
    }

    void pop() {
        main.pop();
        max_.pop();
    }

    int max() const {
        return max_.top();
    }

    int top() const {
        return main.top();
    }

    size_t size() const {
        return main.size();
    }

private:
    Stack main;
    Stack max_;

};

class QueueWithMaximum {
public:
    void push(int& x) {
        top_.push(x);
    }

    int top() {
    if (bottom.size() == 0) {
            while (top_.size() > 0) {
                int temp = top_.top();
                bottom.push(temp);
                top_.pop();
            }
        }
        return bottom.top();
    }

    void pop() {
        if (bottom.size() == 0) {
            while (top_.size() > 0) {
                int temp = top_.top();
                bottom.push(temp);
                top_.pop();
            }
        }
        bottom.pop();
    }

    long long int max() const {
        assert(top_.size() != 0 || bottom.size() != 0);
        if (top_.size() > 0 && bottom.size() > 0) {
            return std::max (top_.max(), bottom.max());
        } else if (top_.size() > 0) {
            return top_.max();
        } else {
            return bottom.max();
        }
    }

private:
    StackWithMaximum top_;
    StackWithMaximum bottom;
};

int main()
{
    QueueWithMaximum queue;
    long long int n, W;
    std::cin >> n >> W;
    long long int sum = 0;
    int temp;
    for (int i = 0; i < W; i++) {
        std::cin >> temp;
        queue.push(temp);
        sum += temp;
    }
    long long int minimum = queue.max()*W - sum;
    for (int i = W; i < n; i++) {
        sum -= queue.top();
        queue.pop();
        std::cin >> temp;
        queue.push(temp);
        sum += temp;
        minimum = std::min(minimum, queue.max()*W - sum);
    }
    std::cout << minimum << std::endl;
    return 0;
}
