#include <cassert>
#ifndef LIST_H
#define LIST_H

template <typename T>
struct ListNode {
    ListNode* prev_;
    ListNode* next_;
    T value_;
    ListNode(ListNode* prev, ListNode* next, const T& value): prev_(prev), next_(next), value_(value) {}
    ListNode(ListNode* prev, ListNode* next, T&& value): prev_(prev), next_(next), value_(std::move(value)) {}
    ListNode& operator=(const ListNode& rhs) {
        prev_ = rhs.prev_;
        next_ = rhs.next_;
        value_ = rhs.value_;
    }
    ListNode& operator=(ListNode&& rhs) {
        this->prev_ = rhs.prev_;
        this->next_ = rhs.next_;
        this->value_ = std::move(rhs.value_);
        rhs.next_ = nullptr;
        rhs.prev_ = nullptr;
    }
};


template <typename T>
class List {
 public:
  class Iterator {
   public:

    Iterator(ListNode<T>* value = nullptr) {
          value_ = value;
      }

    Iterator& operator++() {
        value_ = value_->next_;
        return *this;
    }

    Iterator operator++(int) {
        Iterator value(value_);
        value_ = value_->next_;
        return value;
    }

    T& operator*() const {
        return value_->value_;
    }

    T* operator->() const {
        return &value_->value_;
    }

    bool operator==(const Iterator& rhs) const {
        return (value_ == rhs.value_);
    }
    bool operator!=(const Iterator& rhs) const {
        return (value_ != rhs.value_);
    }
  private:
    ListNode<T>* value_;
  };

  List(): first_(nullptr), last_(nullptr) {}
  List(const List& list) {
      for (ListNode<T>* i = list.first_; i != list.last_->next_; i = i->next_) {
          this->PushBack(i->value_);
      }
  }
  List(List&& list) {
      first_ = list.first_;
      last_ = list.last_;
      size_ = list.size_;
      list.first_ = nullptr;
      list.last_ = nullptr;
      list.size_ = 0;
  }
  ~List() {
      Clear();
  }

  List& operator=(const List& list) {
      Clear();
      for (ListNode<T>* i = list.first_; i != list.last_->next_; i = i->next_) {
          this->PushBack(i->value_);
      }
      return *this;
  }
  List& operator=(List&& list) {
      Clear();
      first_ = list.first_;
      last_ = list.last_;
      size_ = list.size_;
      list.first_ = nullptr;
      list.last_ = nullptr;
      list.size_ = 0;
      return *this;
  }

  bool IsEmpty() const {
      return (size_ == 0);
  }
  size_t Size() const {
      return size_;
  }

  void PushBack(const T& elem) {
      if (size_ > 1) {
          ListNode<T>* newNode = new ListNode<T>(last_, nullptr, elem);
          last_->next_ = newNode;
          last_ = newNode;
      } else if (size_ == 1) {
          ListNode<T>* newNode = new ListNode<T>(first_, nullptr, elem);
          first_->next_ = newNode;
          last_ = newNode;
      } else {
          ListNode<T>* newNode = new ListNode<T>(nullptr, nullptr, elem);
          first_ = last_ = newNode;
      }
      size_++;
  }
  void PushBack(T&& elem) {
      if (size_ > 1) {
          ListNode<T>* newNode = new ListNode<T>(last_, nullptr, std::move(elem));
          last_->next_ = newNode;
          last_ = newNode;
      } else if (size_ == 1) {
          ListNode<T>* newNode = new ListNode<T>(first_, nullptr, std::move(elem));
          first_->next_ = newNode;
          last_ = newNode;
      } else {
          ListNode<T>* newNode = new ListNode<T>(nullptr, nullptr, std::move(elem));
          first_ = last_ = newNode;
      }
      size_++;
  }
  void PushFront(const T& elem) {
      if (size_ > 1) {
          ListNode<T>* newNode = new ListNode<T>(nullptr, first_, elem);
          first_->prev_ = newNode;
          first_ = newNode;
      } else if (size_ == 1) {
          ListNode<T>* newNode = new ListNode<T>(nullptr, first_, elem);
          last_->prev_ = newNode;
          first_ = newNode;
      } else {
          ListNode<T>* newNode = new ListNode<T>(nullptr, nullptr, elem);
          first_ = last_ = newNode;
      }
      size_++;
  }
  void PushFront(T&& elem) {
      if (size_ > 1) {
          ListNode<T>* newNode = new ListNode<T>(nullptr, first_, std::move(elem));
          first_->prev_ = newNode;
          first_ = newNode;
      } else if (size_ == 1) {
          ListNode<T>* newNode = new ListNode<T>(nullptr, first_, std::move(elem));
          last_->prev_ = newNode;
          first_ = newNode;
      } else {
          ListNode<T>* newNode = new ListNode<T>(nullptr, nullptr, std::move(elem));
          first_ = last_ = newNode;
      }
      size_++;
  }

  T& Front() {
      return first_->value_;
  }
  const T& Front() const {
      return first_->value_;
  }
  T& Back() {
      return last_->value_;
  }
  const T& Back() const {
      return last_->value_;
  }

  void PopBack() {
      assert(size_ > 0);
      ListNode<T>* temp = last_->prev_;
      delete last_;
      last_ = temp;
      size_--;
  }

  void PopFront() {
      assert(size_ > 0);
      ListNode<T>* temp = first_->next_;
      delete first_;
      first_ = temp;
      size_--;
  }
  void Clear() {
      while (!this->IsEmpty()) {
          this->PopBack();
      }
      first_ = last_ = nullptr;
  }

  Iterator Begin() {
      return Iterator(first_);
  }

  Iterator End() {
      return Iterator(last_->next_);
  }

private:
  ListNode<T>* first_;
  ListNode<T>* last_;
  size_t size_ = 0;
};

template <typename T>
typename List<T>::Iterator begin(List<T>& list) {
    return list.Begin();
}

template <typename T>
typename List<T>::Iterator end(List<T>& list) {
    return list.End();
}

#endif
