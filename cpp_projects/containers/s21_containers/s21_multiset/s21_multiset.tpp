#ifndef S21_CONTAINERS_S21_MULTISET_METHODS_H_
#define S21_CONTAINERS_S21_MULTISET_METHODS_H_

#include "s21_multiset.h"

template <class Key>
s21::multiset<Key>::multiset(const std::initializer_list<Key> &items) {
  Tree::is_multiset = true;
  for (value_type item : items) this->insert(item, 0);
}

template <class Key>
size_t s21::multiset<Key>::count(const Key &key) {
  size_type counter = 0;
  std::pair<iterator, iterator> range = equal_range(key);
  for (iterator it = range.first; it != range.second; ++it) {
    if (*it == key) {
      counter++;
    }
  }
  if (*range.second == key) {
    counter++;
  }
  return counter;
}

template <class Key>
std::pair<typename s21::multiset<Key>::iterator,
          typename s21::multiset<Key>::iterator>
s21::multiset<Key>::equal_range(const Key &key) {
  TreeNode<Key, int> *tnode = Tree::FindPosition(key);
  s21::multiset<Key>::iterator it(this, tnode);
  iterator range_start = it;
  iterator range_end = it;

  while ((range_start - 1) != nullptr && *(range_start - 1) == key) {
    range_start--;
  }
  while ((range_start + 1) != nullptr && *(range_end + 1) == key) {
    range_end++;
  }
  return std::pair<iterator, iterator>(range_start, range_end);
}

template <class Key>
typename s21::multiset<Key>::iterator s21::multiset<Key>::lower_bound(
    const Key &key) {
  TreeNode<Key, int> *tnode = Tree::FindPosition(key);
  s21::multiset<Key>::iterator it(this, tnode);
  while (it != this->end() && *it < key) {
    it++;
  }
  return it;
}

template <class Key>
typename s21::multiset<Key>::iterator s21::multiset<Key>::upper_bound(
    const Key &key) {
  TreeNode<Key, int> *tnode = Tree::FindPosition(key);
  s21::multiset<Key>::iterator it(this, tnode);
  auto ite = this->end();
  while (it != ite && *it <= key) {
    it++;
  }
  return it;
}

#endif  // S21_CONTAINERS_S21_MULTISET_METHODS_H_