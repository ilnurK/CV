#ifndef S21_CONTAINERS_S21_MULTISET_H_
#define S21_CONTAINERS_S21_MULTISET_H_

#include <type_traits>

#include "../s21_set/s21_set.h"

namespace s21 {

using namespace S21RbTree;

template <typename Key>
class multiset : public set<Key> {
 private:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using Tree = RbTree<key_type, int>;
  using iterator = typename Tree::Iterator;
  using const_iterator = typename Tree::ConstIterator;
  using size_type = size_t;

 public:
  multiset() { Tree::is_multiset = true; }
  multiset(Key key) : Tree::RbTree(key) { Tree::is_multiset = true; }
  multiset(std::initializer_list<value_type> const &items);
  size_type count(const Key &key);
  std::pair<iterator, iterator> equal_range(const Key &key);
  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);
};

#include "s21_multiset.tpp"

}  // namespace s21

#endif  // S21_CONTAINERS_S21_MULTISET_H_