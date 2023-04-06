#ifndef UNTITLED_UNIQUE_PTR_H
#define UNTITLED_UNIQUE_PTR_H

#include <iostream>

template <class T>
class UniquePtr {
 private:
  T* ptr_;

 public:
  UniquePtr() : ptr_(nullptr) {
  }
  explicit UniquePtr(T* other) : ptr_(other) {
  }

  UniquePtr(const UniquePtr<T>& other) = delete;
  UniquePtr& operator=(const UniquePtr<T>& other) = delete;

  UniquePtr(UniquePtr&& other) noexcept {
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }

  UniquePtr& operator=(UniquePtr&& other) noexcept {
    if (ptr_ == other.ptr_) {
      other.ptr_ = nullptr;
      return *this;
    }

    delete ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;

    return *this;
  }

  ~UniquePtr() {
    delete ptr_;
  }

  T* Release() {
    T* copy = ptr_;
    ptr_ = nullptr;
    return copy;
  }

  void Reset(T* other = nullptr) {
    if (ptr_ != other) {
      delete ptr_;
      ptr_ = other;
    }
  }

  void Swap(UniquePtr<T>& other) {
    std::swap(ptr_, other.ptr_);
  }

  T* Get() const {
    return ptr_;
  }

  T& operator*() const {
    return *ptr_;
  }

  T* operator->() const {
    return ptr_;
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }
};

#endif
