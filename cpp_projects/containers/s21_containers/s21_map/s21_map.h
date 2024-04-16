#ifndef S21_CONTAINERS_S21_MAP_H_
#define S21_CONTAINERS_S21_MAP_H_

#include <vector>

#include "../s21_rb_tree/s21_rb_tree.h"

namespace s21 {

using namespace S21RbTree;

template <typename Key, typename T>
class map : public RbTree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

 public:
  map(){};
  map(std::initializer_list<value_type> const &items);

 public:
  class PairIterator;
  class ConstPairIterator;
  using iterator = PairIterator;
  using const_iterator = ConstPairIterator;

 public:
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

 public:
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
  T &at(const Key &key);
  T &operator[](const Key &key);
};

#include "s21_map.tpp"

}  // namespace s21

#endif  // S21_CONTAINERS_S21_MAP_H_
