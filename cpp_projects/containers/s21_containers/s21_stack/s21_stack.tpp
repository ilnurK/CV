#ifndef S21_CONTAINERS_S21_STACK_METHODS_H_
#define S21_CONTAINERS_S21_STACK_METHODS_H_

#include "s21_stack.h"

template <typename T>
inline stack<T>::stack() noexcept : tail_(nullptr), size_(0) {}

template <typename T>
inline stack<T>::stack(const std::initializer_list<value_type> &items) noexcept
    : tail_(nullptr), size_(0) {
  for (value_type i : items) {
    push(i);
  }
}

template <typename T>
inline stack<T>::stack(const stack<T> &other) : tail_(nullptr), size_(0) {
  *this = other;
}

template <typename T>
inline stack<T>::stack(stack<T> &&other) noexcept : tail_(nullptr), size_(0) {
  *this = std::move(other);
}

template <typename T>
inline stack<T>::~stack() {
  Clear_();
}

template <typename T>
inline stack<T> &stack<T>::operator=(const stack<T> &other) noexcept {
  if (this != &other) {
    Clear_();
    int i = other.size_ - 1;
    while (i >= 0) push(other.At_(i--));
  }
  return *this;
}

template <typename T>
inline stack<T> &stack<T>::operator=(stack<T> &&other) noexcept {
  if (this != &other) {
    Clear_();
    tail_ = other.tail_;
    size_ = other.size_;
    other.tail_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename T>
inline bool stack<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
inline typename stack<T>::size_type stack<T>::size() const noexcept {
  return size_;
}

template <typename T>
inline typename stack<T>::const_reference stack<T>::top() const {
  if (!tail_) throw std::logic_error("stack is empty");
  return tail_->value_;
}

template <typename T>
inline void stack<T>::push(const_reference value) noexcept {
  Node_ *new_node = new Node_(value);
  if (!tail_) {
    tail_ = new_node;
  } else {
    new_node->ptr_prev_ = tail_;
    tail_ = new_node;
  }
  ++size_;
}

template <typename T>
inline void stack<T>::pop() {
  if (!tail_) throw std::logic_error("stack is empty");
  Node_ *prev_node = tail_->ptr_prev_;
  delete tail_;
  tail_ = prev_node;
  --size_;
}

template <typename T>
inline void stack<T>::swap(stack<T> &other) noexcept {
  if (this != &other) {
    Node_ *tmp_tail = tail_;
    tail_ = other.tail_;
    other.tail_ = tmp_tail;
    size_type tmp_size = size_;
    size_ = other.size_;
    other.size_ = tmp_size;
  }
}

template <typename T>
inline void stack<T>::Clear_() {
  while (tail_) pop();
}

template <typename T>
inline typename stack<T>::value_type stack<T>::At_(int i) const {
  if (i < 0 || i >= (int)size_) throw std::out_of_range("Index out of range");
  value_type result = T();
  Node_ *tmp_tail = tail_;
  int j = 0;
  while ((j++) != i) tmp_tail = tmp_tail->ptr_prev_;
  result = tmp_tail->value_;
  return result;
}

#endif  // S21_CONTAINERS_S21_STACK_METHODS_H_