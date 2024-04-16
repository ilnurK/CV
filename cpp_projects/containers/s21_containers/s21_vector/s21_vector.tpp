#ifndef S21_CONTAINERS_S21_VECTOR_METHODS_H_
#define S21_CONTAINERS_S21_VECTOR_METHODS_H_

#include "s21_vector.h"

template <typename T>
inline vector<T>::vector() : arr_(nullptr), size_(0), capacity_(0) {}

template <typename T>
inline vector<T>::vector(size_type n)
    : arr_(new value_type[n]), size_(n), capacity_(n) {
  if (arr_ == nullptr) {
    throw std::bad_alloc();
  }
  for (size_type i = 0; i < n; ++i) {
    arr_[i] = T();
  }
}

template <typename T>
inline vector<T>::vector(std::initializer_list<value_type> const &items)
    : vector(items.size()) {
  for (size_type i = 0; i < size_; ++i) {
    arr_[i] = *(items.begin() + i);
  }
}

template <typename T>
inline vector<T>::vector(const vector<T> &v) : vector(v.size_) {
  for (size_type i = 0; i < size_; ++i) {
    arr_[i] = v.arr_[i];
  }
}

template <typename T>
inline vector<T>::vector(vector<T> &&v) noexcept {
  size_ = v.size_;
  v.size_ = 0;
  capacity_ = v.capacity_;
  v.capacity_ = 0;
  arr_ = v.arr_;
  v.arr_ = nullptr;
}

template <typename T>
inline vector<T>::~vector() {
  delete[] arr_;
  arr_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
inline vector<T> &vector<T>::operator=(vector<T> &&v) noexcept {
  if (this != &v) {
    this->swap(v);
  }
  return *this;
}

template <typename T>
inline typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_ || size_ == 0) {
    throw std::out_of_range("Index out range");
  }
  return arr_[pos];
}

template <typename T>
inline typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return *(arr_ + pos);
}

template <typename T>
inline typename vector<T>::const_reference vector<T>::front() {
  return *arr_;
}

template <typename T>
inline typename vector<T>::const_reference vector<T>::back() {
  return arr_[size_ - 1];
}

template <typename T>
inline typename vector<T>::iterator vector<T>::data() noexcept {
  return arr_;
}

template <typename T>
inline typename vector<T>::iterator vector<T>::begin() {
  return arr_;
}

template <typename T>
inline typename vector<T>::iterator vector<T>::end() {
  return arr_ + size_;
}

template <typename T>
inline bool vector<T>::empty() const noexcept {
  return arr_ == nullptr;
}

template <typename T>
inline typename vector<T>::size_type vector<T>::size() {
  return size_;
}

template <typename T>
inline typename vector<T>::size_type vector<T>::max_size() {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
}

template <typename T>
inline void vector<T>::reserve(size_type size) {
  if (size <= capacity_) {
    return;
  }

  if (size > max_size()) {
    throw std::out_of_range("ReserveError: Too large size for a new capacity");
  }

  iterator new_arr = new value_type[size];
  std::copy(arr_, arr_ + size_, new_arr);
  delete[] arr_;
  arr_ = new_arr;
  capacity_ = size;
}

template <typename T>
inline typename vector<T>::size_type vector<T>::capacity() {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    iterator new_arr = new value_type[size_];
    std::copy(arr_, arr_ + size_, new_arr);
    delete[] arr_;
    arr_ = new_arr;
    capacity_ = size_;
  }
}

template <typename T>
inline void vector<T>::clear() {
  delete[] arr_;
  arr_ = nullptr;
  size_ = 0;
}

template <typename T>
inline typename vector<T>::iterator vector<T>::insert(iterator pos,
                                                      const_reference value) {
  vector<value_type> tmp(size_ + 1);
  size_type j = 0, position = pos - this->begin();
  for (size_type i = 0; i < tmp.size_; ++i) {
    if (i == position) {
      tmp.arr_[i] = value;
    } else {
      tmp.arr_[i] = arr_[j++];
    }
  }
  *this = std::move(tmp);
  return arr_ + position;
}

template <typename T>
inline void vector<T>::erase(iterator pos) {
  vector<value_type> tmp(size_ - 1);
  size_type j = 0, position = pos - this->begin();
  for (size_type i = 0; i < size_; ++i) {
    if (i != position) {
      tmp.arr_[j++] = arr_[i];
    }
  }
  *this = std::move(tmp);
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ == capacity_) {
    reserve(capacity_ ? capacity_ * 2 : 1);
  }
  arr_[size_++] = value;
}

template <typename T>
inline void vector<T>::pop_back() {
  size_ -= 1;
}

template <typename T>
inline void vector<T>::swap(vector &other) noexcept {
  value_type *tmp_arr = arr_;
  size_type tmp_size = size_;
  size_type tmp_capacity = capacity_;
  arr_ = other.arr_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.arr_ = tmp_arr;
  other.size_ = tmp_size;
  other.capacity_ = tmp_capacity;
}

template <typename T>
template <typename... Args>
inline typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                           Args &&...args) {
  s21::vector<value_type> tmp{args...};
  iterator position = (iterator)pos;
  for (size_t i = 0; i < tmp.size(); ++i) {
    position = insert(position, tmp[i]) + 1;
  }
  return position;
}

template <typename T>
template <typename... Args>
inline void vector<T>::insert_many_back(Args &&...args) {
  insert_many(this->end(), args...);
}

#endif  // S21_CONTAINERS_S21_VECTOR_METHODS_H_