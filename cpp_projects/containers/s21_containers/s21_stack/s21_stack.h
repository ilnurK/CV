#ifndef S21_CONTAINERS_S21_STACK_H_
#define S21_CONTAINERS_S21_STACK_H_

namespace s21 {
template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack() noexcept;
  stack(std::initializer_list<value_type> const &items) noexcept;
  stack(const stack &other);
  stack(stack &&other) noexcept;

  ~stack();

  const_reference top() const;
  bool empty() const noexcept;
  size_type size() const noexcept;
  void push(const_reference value) noexcept;
  void pop();
  void swap(stack &other) noexcept;

  stack &operator=(const stack &other) noexcept;
  stack &operator=(stack &&other) noexcept;

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    for (auto elem : {std::forward<Args>(args)...}) {
      push(elem);
    }
  }

 private:
  typedef struct Node_ {
    value_type value_;
    Node_ *ptr_prev_;
    explicit Node_(value_type value) noexcept
        : value_(value), ptr_prev_(nullptr) {}
  } Node_;

  Node_ *tail_;
  size_type size_;

  void Clear_();
  value_type At_(int i) const;
};

#include "s21_stack.tpp"

}  // namespace s21

#endif  // S21_CONTAINERS_S21_STACK_H_