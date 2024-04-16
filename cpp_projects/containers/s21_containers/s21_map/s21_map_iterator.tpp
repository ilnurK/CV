#ifndef S21_CONTAINERS_S21_MAP_ITERATOR_METHODS_H_
#define S21_CONTAINERS_S21_MAP_ITERATOR_METHODS_H_

#include "s21_map_iterator.h"

template <typename Key, typename T>
typename map<Key, T>::reference map<Key, T>::PairIterator::operator*() const {
  static value_type val{};
  if (RbTree<Key, T>::Iterator::cur != nullptr) {
    val = std::make_pair(RbTree<Key, T>::Iterator::cur->key,
                         RbTree<Key, T>::Iterator::cur->value);
  }
  return val;
}

template <typename Key, typename T>
typename map<Key, T>::reference map<Key, T>::PairIterator::operator*() {
  static value_type val{};
  if (RbTree<Key, T>::Iterator::cur != nullptr) {
    val = std::make_pair(RbTree<Key, T>::Iterator::cur->key,
                         RbTree<Key, T>::Iterator::cur->value);
  }
  return val;
}

template <typename Key, typename T>
typename map<Key, T>::const_reference
map<Key, T>::ConstPairIterator::operator*() const {
  static value_type val{};
  if (RbTree<Key, T>::Iterator::cur != nullptr) {
    val = std::make_pair(RbTree<Key, T>::Iterator::cur->key,
                         RbTree<Key, T>::Iterator::cur->value);
  }
  return val;
}

#endif  // S21_CONTAINERS_S21_MAP_ITERATOR_METHODS_H_
