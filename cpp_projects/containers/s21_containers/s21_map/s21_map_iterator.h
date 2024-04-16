#ifndef S21_CONTAINERS_S21_MAP_ITERATOR_H_
#define S21_CONTAINERS_S21_MAP_ITERATOR_H_

#include "s21_map.h"

template <typename Key, typename T>
class map<Key, T>::PairIterator : public RbTree<Key, T>::Iterator {
 public:
  typename map<Key, T>::reference operator*() const;
  typename map<Key, T>::reference operator*();

  PairIterator() : RbTree<Key, T>::Iterator(){};
  PairIterator(const map<Key, T> *mouter, TreeNode<Key, T> *it) {
    RbTree<Key, T>::Iterator::cur = it;
    RbTree<Key, T>::Iterator::outer = mouter;
  }
  PairIterator([[maybe_unused]] typename RbTree<Key, T>::Iterator iter) {}
};

template <typename Key, typename T>
class map<Key, T>::ConstPairIterator : public PairIterator {
 public:
  typename map<Key, T>::const_reference operator*() const;
};

#include "s21_map_iterator.tpp"

#endif  // S21_CONTAINERS_S21_MAP_ITERATOR_H_