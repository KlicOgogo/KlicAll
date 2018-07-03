#include <algorithm>
#include <cassert>
#ifndef INTRUSIVE_LIST_H
#define INTRUSIVE_LIST_H

class BaseList {
    friend class ListHook;
protected:
    size_t size_ = 0;
};

class ListHook {
 public:
  ListHook(): next_(nullptr), prev_(nullptr), baseList_(nullptr) {}

  bool IsLinked() const {
      return baseList_ != nullptr;
  }

  void Unlink() {
      if (IsLinked()) {
          prev_->next_ = next_;
          next_->prev_ = prev_;
          prev_ = nullptr;
          next_ = nullptr;
          baseList_->size_--;
          baseList_ = nullptr;
      }
  }

  ~ListHook() {
      Unlink();
  }

  ListHook(const ListHook&) = delete;

 private:
  template<class T>
  friend class List;
  ListHook* next_;
  ListHook* prev_;
  BaseList* baseList_;
};

template <typename T>
class List : BaseList {
 public:
  class Iterator :
public std::iterator<std::bidirectional_iterator_tag, T> {
   public:
    Iterator (ListHook* hook) {
        hook_ = hook;
    }

    Iterator& operator++() {
        hook_ = hook_->next_;
        return *this;
    }

    Iterator operator++(int) {
        Iterator value(hook_);
        hook_ = hook_->next_;
        return value;
    }

    T& operator*() const {
        return *static_cast<T*>(hook_);
    }
    T* operator->() const {
        return static_cast<T*>(hook_);
    }

    bool operator==(const Iterator& rhs) const {
        return hook_ == rhs.hook_;
    }
    bool operator!=(const Iterator& rhs) const {
        return hook_ != rhs.hook_;
    }
    ListHook* hook_;
  };

  List() {
      dummy_.prev_ = &dummy_;
      dummy_.next_ = &dummy_;
  }

  List(const List&) = delete;
  List(List&& other) {
    dummy_.next_ = other.dummy_.next_;
    dummy_.next_->prev_ = &dummy_;
    dummy_.prev_ = other.dummy_.prev_;
    dummy_.prev_->next_ = &dummy_;
    this->size_ = other.size_;
    ListHook* temp = dummy_.next_;
    while (temp != &dummy_) {
        temp->baseList_ = this;
        temp = temp->next_;
    }
    other.dummy_.next_ = nullptr;
    other.dummy_.prev_ = nullptr;
    other.size_ = 0;
  }

  ~List() {
      Clear();
  }

  List& operator=(const List&) = delete;
  List& operator=(List&& other) {
      dummy_.next_ = other.dummy_.next_;
      dummy_.next_->prev_ = &dummy_;
      dummy_.prev_ = other.dummy_.prev_;
      dummy_.prev_->next_ = &dummy_;
      this->size_ = other.size_;
      ListHook* temp = dummy_.next_;
      while (temp != &dummy_) {
          temp->baseList_ = this;
          temp = temp->next_;
      }
      other.dummy_.next_ = nullptr;
      other.dummy_.prev_ = nullptr;
      other.size_ = 0;
      return *this;
  }

  bool IsEmpty() const {
      return this->size_ == 0;
  }
  size_t Size() const {
      return this->size_;
  }

  void PushBack(T* elem) {
      this->size_++;
      ListHook* temp = dummy_.prev_;
      temp->next_ = elem;
      elem->prev_ = temp;
      elem->next_ = &dummy_;
      dummy_.prev_ = elem;
      elem->baseList_ = this;
  }

  void PushFront(T* elem) {
      this->size_++;
      ListHook* temp = dummy_.next_;
      temp->prev_ = elem;
      elem->next_ = temp;
      elem->prev_ = &dummy_;
      dummy_.next_ = elem;
      elem->baseList_ = this;
  }

  T& Front() {
      return *static_cast<T*>(dummy_.next_);
  }

  const T& Front() const {
      return *static_cast<T*>(dummy_.next_);
  }

  T& Back() {
      return *static_cast<T*>(dummy_.prev_);
  }

  const T& Back() const {
      return *static_cast<T*>(dummy_.prev_);
  }

  void PopBack() {
      assert(this->size_ > 0);
      dummy_.prev_->Unlink();
  }

  void PopFront() {
      assert(this->size_ > 0);
      dummy_.next_->Unlink();
  }

  Iterator Begin() {
      return Iterator(dummy_.next_);
  }

  Iterator End() {
      return Iterator(&dummy_);
  }

  Iterator IteratorTo(T* element) {
   if (element->baseList_ == this) {
       return Iterator(element);
   } else {
       return Iterator(&dummy_);
   }
  }

 private:
  ListHook dummy_;
  void Clear() {
      while(dummy_.next_ != &dummy_ && dummy_.next_ != nullptr) {
                  dummy_.next_->Unlink();
              }
  }
};

template <typename T>
typename List<T>::Iterator begin(List<T>& list) { return list.Begin(); }

template <typename T>
typename List<T>::Iterator end(List<T>& list) { return list.End(); }

#endif
