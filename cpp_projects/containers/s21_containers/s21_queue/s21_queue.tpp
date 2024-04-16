#ifndef S21_CONTAINERS_S21_QUEUE_METHODS_H_
#define S21_CONTAINERS_S21_QUEUE_METHODS_H_

#include "s21_queue.h"

template <typename T>
inline queue<T>::queue() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
inline queue<T>::queue(const std::initializer_list<value_type> &items) noexcept
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (value_type i : items) {
    push(i);
  }
}

template <typename T>
inline queue<T>::queue(const queue<T> &other)
    : head_(nullptr), tail_(nullptr), size_(0) {
  *this = other;
}

template <typename T>
inline queue<T>::queue(queue<T> &&other) noexcept
    : head_(nullptr), tail_(nullptr), size_(0) {
  *this = std::move(other);
}

template <typename T>
inline queue<T>::~queue() {
  Clear_();
}

template <typename T>
inline queue<T> &queue<T>::operator=(const queue<T> &other) noexcept {
  if (this != &other) {
    Clear_();
    size_type i = 0;
    while (i < other.size_) {
      push(other.At_(i));
      i++;
    }
  }
  return *this;
}

template <typename T>
inline queue<T> &queue<T>::operator=(queue<T> &&other) noexcept {
  if (this != &other) {
    Clear_();
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.tail_ = nullptr;
    other.head_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename T>
inline void queue<T>::pop() {
  if (!head_) throw std::logic_error("queue is empty");
  Node_ *prev_node = head_->ptr_prev_;
  delete head_;
  head_ = prev_node;
  --size_;
}

template <typename T>
inline void queue<T>::push(const_reference value) noexcept {
  Node_ *new_node = new Node_(value);
  if (!head_) {
    head_ = new_node;
  } else if (!tail_) {
    head_->ptr_prev_ = new_node;
    tail_ = new_node;
  } else {
    tail_->ptr_prev_ = new_node;
    tail_ = new_node;
  }
  ++size_;
}

template <typename T>
inline bool queue<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
inline typename queue<T>::const_reference queue<T>::front() {
  if (!head_) throw std::logic_error("queue is empty");
  return head_->value_;
}

template <typename T>
inline typename queue<T>::const_reference queue<T>::back() {
  if (!tail_) throw std::logic_error("queue is empty");
  return tail_->value_;
}

template <typename T>
inline typename queue<T>::value_type queue<T>::At_(int i) const {
  if (i < 0 || i >= (int)size_) throw std::out_of_range("Index out of range");
  value_type result = T();
  Node_ *tmp_head = head_;
  for (int j = 0; j < i; j++) {
    tmp_head = tmp_head->ptr_prev_;
  }
  result = tmp_head->value_;
  return result;
}

template <typename T>
inline void queue<T>::Clear_() {
  while (head_) {
    pop();
  }
  if (tail_) tail_ = nullptr;
}

template <typename T>
inline typename queue<T>::size_type queue<T>::size() const noexcept {
  return size_;
}

#endif  // S21_CONTAINERS_S21_QUEUE_METHODS_H_
