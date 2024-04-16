#ifndef S21_CONTAINERS_S21_RB_TREE_ITERATOR_METHODS_H_
#define S21_CONTAINERS_S21_RB_TREE_ITERATOR_METHODS_H_

#include "s21_rb_tree_iterator.h"

template <typename K, typename V>
typename RbTree<K, V>::Iterator RbTree<K, V>::Iterator::operator+(int n) const {
  Iterator result = *this;
  while (n > 0 && result.cur != nullptr) {
    ++result;
    --n;
  }
  return result;
}

template <typename K, typename V>
typename RbTree<K, V>::Iterator RbTree<K, V>::Iterator::operator-(int n) const {
  Iterator result = *this;
  while (n > 0 && result.cur != nullptr) {
    --result;
    --n;
  }
  return result;
}

template <typename K, typename V>
TreeNode<K, V> *RbTree<K, V>::Iterator::FindLeftmost(TreeNode<K, V> *cur) {
  while (cur->left) {
    cur = cur->left;
  }
  return cur;
}

template <typename K, typename V>
TreeNode<K, V> *RbTree<K, V>::Iterator::FindRightmost(TreeNode<K, V> *cur) {
  if (cur == nullptr) return nullptr;
  while (cur->right) {
    cur = cur->right;
  }
  return cur;
}

template <typename K, typename V>
typename RbTree<K, V>::Iterator RbTree<K, V>::Iterator::operator++(int) {
  Iterator oldIterator(*this);
  ++*this;
  return oldIterator;
}

template <typename K, typename V>
typename RbTree<K, V>::Iterator RbTree<K, V>::Iterator::operator--(int) {
  Iterator oldIterator(*this);
  --*this;
  return oldIterator;
}

template <typename K, typename V>
typename RbTree<K, V>::Iterator &RbTree<K, V>::Iterator::operator++() {
  if (cur != nullptr) {
    if (cur->right) {
      cur = this->FindLeftmost(cur->right);
    } else {
      TreeNode<K, V> *parent = cur->parent;
      while (parent && cur == parent->right) {
        cur = parent;
        parent = parent->parent;
      }
      if (parent) {
        cur = parent;
      } else {
        cur = outer->fake_node_;
      }
    }
  }
  return *this;
}

template <typename K, typename V>
typename RbTree<K, V>::Iterator &RbTree<K, V>::Iterator::operator++() const {
  if (cur != nullptr) {
    if (cur->right) {
      cur = this->FindLeftmost(cur->right);
    } else {
      TreeNode<K, V> *parent = cur->parent;
      while (parent && cur == parent->right) {
        cur = parent;
        parent = parent->parent;
      }
      if (parent) {
        cur = parent;
      } else {
        cur = outer->fake_node_;
      }
    }
  }
  return *this;
}

template <typename K, typename V>
typename RbTree<K, V>::Iterator &RbTree<K, V>::Iterator::operator--() {
  if (cur != nullptr) {
    if (cur->left) {
      cur = this->FindRightmost(cur->left);
    } else {
      TreeNode<K, V> *parent = cur->parent;
      while (parent && cur == parent->left) {
        cur = parent;
        parent = parent->parent;
      }
      cur = parent;
    }
  }
  return *this;
}

template <typename K, typename V>
typename RbTree<K, V>::Iterator &RbTree<K, V>::Iterator::operator+=(int n) {
  *this = *this + n;
  return *this;
}

template <typename K, typename V>
bool RbTree<K, V>::Iterator::operator==(Iterator &it) const {
  bool res = 0;
  if (cur && it.cur) {
    res = (cur->key == it.cur->key);
  }
  return res;
}

template <typename K, typename V>
bool RbTree<K, V>::Iterator::operator!=(const Iterator &it) const {
  bool res = 0;
  if (cur && it.cur) {
    res = (cur != it.cur);
  } else if (cur) {
    res = 1;
  }
  return res;
}

template <typename K, typename V>
K RbTree<K, V>::Iterator::operator*() const {
  K key{};
  if (cur != nullptr) {
    key = cur->key;
  }
  return key;
}

template <typename K, typename V>
typename RbTree<K, V>::Iterator RbTree<K, V>::Iterator::operator[](int index) {
  Iterator result = *this;
  while (index > 0 && result.cur != nullptr) {
    ++result;
    --index;
  }
  return result;
}

template <typename K, typename V>
bool RbTree<K, V>::Iterator::GetColor() const {
  bool color = BLACK;
  if (cur) {
    color = cur->color;
  }
  return color;
}

template <typename K, typename V>
V RbTree<K, V>::Iterator::GetValue() const {
  V value{};
  if (cur) {
    value = cur->value;
  }
  return value;
}

template <typename K, typename V>
TreeNode<K, V> *RbTree<K, V>::ConstIterator::FindLeftmost(
    TreeNode<K, V> *find) {
  while (find->left) {
    find = find->left;
  }
  return find;
}

template <typename K, typename V>
typename RbTree<K, V>::ConstIterator &
RbTree<K, V>::ConstIterator::operator++() {
  if (Iterator::cur != nullptr) {
    if (Iterator::cur->right) {
      TreeNode<K, V> *found = FindLeftmost(Iterator::cur->right);
      Iterator::cur = found;
    } else {
      TreeNode<K, V> *parent = Iterator::cur->parent;
      while (parent && Iterator::cur == parent->right) {
        Iterator::cur = parent;
        parent = parent->parent;
      }
      if (parent) {
        Iterator::cur = parent;
      } else {
        Iterator::cur = Iterator::outer->fake_node_;
      }
    }
  }
  return *this;
}

template <typename K, typename V>
bool RbTree<K, V>::ConstIterator::operator!=(const ConstIterator &it) const {
  bool res = 0;
  if (Iterator::cur && it.Iterator::cur) {
    res = (Iterator::cur != it.Iterator::cur);
  } else if (Iterator::cur) {
    res = 1;
  }
  return res;
}

template <typename K, typename V>
K RbTree<K, V>::ConstIterator::operator*() const {
  K key{};
  if (Iterator::cur != nullptr) {
    key = Iterator::cur->key;
  }
  return key;
}

template <typename K, typename V>
V RbTree<K, V>::ConstIterator::GetValue() const {
  V value{};
  if (Iterator::cur) {
    value = Iterator::cur->value;
  }
  return value;
}

#endif  // S21_CONTAINERS_S21_RB_TREE_ITERATOR_METHODS_H_
