#pragma once

template <class T> class smart_ptr {
public:
  explicit smart_ptr(T *pointee) : pointee_(pointee);
  smart_ptr &operator=(const smart_ptr &other);
  ~smart_ptr();
  T &operator*() const { return *pointee_; }
  T *operator->() const { return pointee_; }

private:
  T *pointee_;
};


