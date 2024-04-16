#ifndef S21_CONTAINERS_S21_ARRAY_METHODS_H_
#define S21_CONTAINERS_S21_ARRAY_METHODS_H_

#include "s21_array.h"

template <typename T, size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  if (items.size() > N) {
    throw std::out_of_range("Position greater than array size");
  }
  size_type j = 0;
  for (const auto &it : items) {
    arr_[j++] = it;
  }
}

template <typename T, size_t N>
array<T, N>::array(const array &a) {
  size_type j = 0;
  for (const auto &it : a) {
    arr_[j++] = it;
  }
}

template <typename T, size_t N>
array<T, N>::array(array &&a) {
  std::move(a.arr_, a.arr_ + N, arr_);
}

template <typename T, size_t N>
array<T, N> &array<T, N>::operator=(array &&a) {
  std::move(a.arr_, a.arr_ + N, arr_);
  return *this;
}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(const array &a) {
  std::copy(a.arr_, a.arr_ + N, arr_);
  return *this;
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Position greater than array size");
  }
  return *(arr_ + pos);
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
  if (pos >= N) {
    throw std::out_of_range("Position greater than array size");
  }
  return *(arr_ + pos);
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return *(arr_ + pos);
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::operator[](
    size_type pos) const {
  return *(arr_ + pos);
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return *arr_;
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return *(arr_ + N - 1);
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return arr_;
}

template <typename T, size_t N>
typename array<T, N>::const_iterator array<T, N>::data() const {
  return arr_;
}

template <typename T, size_t N>
bool array<T, N>::empty() const {
  return N == 0;
}

template <typename T, size_t N>
void array<T, N>::swap(array &other) {
  std::swap_ranges(begin(), end(), other.arr_);
}

template <typename T, size_t N>
void array<T, N>::fill(const_reference value) {
  for (auto it = begin(), ite = end(); it != ite; ++it) {
    *it = value;
  }
}

#endif  // S21_CONTAINERS_S21_ARRAY_H_