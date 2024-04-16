#ifndef S21_CONTAINERS_S21_ARRAY_H_
#define S21_CONTAINERS_S21_ARRAY_H_

#include <iostream>

namespace s21 {

template <typename T, size_t N>
class array {
 private:
  T arr_[N]{};

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = T *;
  using const_iterator = const T *;

 public:
  array(){};
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a);
  ~array(){};
  array &operator=(array &&a);
  array &operator=(const array &a);

 public:
  iterator begin() { return arr_; };
  iterator end() { return arr_ + N; };
  const_iterator begin() const { return arr_; };
  const_iterator end() const { return arr_ + N; };
  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;

  const_reference front() const;
  const_reference back() const;
  iterator data();
  const_iterator data() const;

  bool empty() const;
  size_type size() const { return N; };
  size_type max_size() const { return size(); }
  void swap(array &other);
  void fill(const_reference value);
};

#include "s21_array.tpp"

}  // namespace s21

#endif  // S21_CONTAINERS_S21_ARRAY_H_