#ifndef S21_CONTAINERS_S21_VECTOR_H_
#define S21_CONTAINERS_S21_VECTOR_H_

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector<T> &v);
  vector(vector<T> &&v) noexcept;
  ~vector();
  vector<T> &operator=(vector<T> &&v) noexcept;

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T *data() noexcept;

  iterator begin();
  iterator end();

  bool empty() const noexcept;
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other) noexcept;

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  value_type *arr_;
  size_type size_;
  size_type capacity_;
};

#include "s21_vector.tpp"

}  // namespace s21

#endif  // S21_CONTAINERS_S21_VECTOR_H_