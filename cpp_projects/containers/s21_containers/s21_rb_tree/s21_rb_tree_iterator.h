#ifndef S21_CONTAINERS_S21_RB_TREE_ITERATOR_H_
#define S21_CONTAINERS_S21_RB_TREE_ITERATOR_H_

#include "s21_rb_tree.h"

template <typename K, typename V>
class RbTree<K, V>::Iterator {
 protected:
  TreeNode<K, V> *cur{};
  TreeNode<K, V> *FindLeftmost(TreeNode<K, V> *cur);
  TreeNode<K, V> *FindRightmost(TreeNode<K, V> *cur);

 public:
  Iterator() {}
  Iterator(RbTree<K, V> *outer_in) : cur(nullptr), outer(outer_in) {}
  Iterator(const RbTree<K, V> *outer_in, TreeNode<K, V> *it)
      : cur(it), outer(outer_in) {}
  Iterator operator+(int n) const;
  Iterator operator-(int n) const;
  Iterator operator++(int);
  Iterator operator--(int);
  Iterator &operator++();
  Iterator &operator++() const;
  Iterator &operator--();
  Iterator &operator+=(int n);

  bool operator==(Iterator &it) const;
  bool operator!=(const Iterator &it) const;

  K operator*() const;
  Iterator operator[](int index);
  V GetValue() const;
  bool GetColor() const;

 protected:
  const RbTree<K, V> *outer;
};

template <typename K, typename V>
class RbTree<K, V>::ConstIterator : public RbTree<K, V>::Iterator {
 public:
  ConstIterator(const RbTree<K, V> *outer_in, TreeNode<K, V> *it)
      : Iterator(outer_in, it) {}
  TreeNode<K, V> *FindLeftmost(TreeNode<K, V> *find);
  ConstIterator &operator++();
  K operator*() const;
  bool operator!=(const ConstIterator &it) const;
  V GetValue() const;
};

#include "s21_rb_tree_iterator.tpp"

#endif  // S21_CONTAINERS_S21_RB_TREE_ITERATOR_H_