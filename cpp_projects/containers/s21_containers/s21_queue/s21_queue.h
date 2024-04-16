#ifndef S21_CONTAINERS_S21_QUEUE_H_
#define S21_CONTAINERS_S21_QUEUE_H_

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue() noexcept;
  queue(std::initializer_list<value_type> const &items) noexcept;
  queue(const queue &other);
  queue(queue &&other) noexcept;

  ~queue();

  queue &operator=(const queue &other) noexcept;
  queue &operator=(queue &&other) noexcept;

  const_reference front();
  const_reference back();
  void pop();
  void push(const_reference value) noexcept;
  bool empty() const noexcept;
  size_type size() const noexcept;
  void swap(queue<T> &other) noexcept {
    Node_ *tmp_head = head_;
    Node_ *tmp_tail = tail_;
    size_t tmp_size = other.size_;
    if (head_ && other.head_) {
      head_ = other.head_;
      other.head_ = tmp_head;
    }
    if (tail_ && other.tail_) {
      tail_ = other.tail_;
      other.tail_ = tmp_tail;
    }
    other.size_ = size_;
    size_ = tmp_size;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    for (auto elem : {std::forward<Args>(args)...}) {
      push(elem);
    }
  }

 private:
  struct Node_ {
    value_type value_;
    Node_ *ptr_prev_;

    explicit Node_(value_type value) noexcept
        : value_(value), ptr_prev_(nullptr) {}
  };

  Node_ *head_;
  Node_ *tail_;
  size_type size_;
  void Clear_();
  value_type At_(int i) const;
};

#include "s21_queue.tpp"

}  // namespace s21

#endif  // S21_CONTAINERS_S21_QUEUE_H_
