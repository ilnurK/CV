#ifndef S21_CONTAINERS_MAP_METHODS_H_
#define S21_CONTAINERS_MAP_METHODS_H_

#include "s21_map.h"
#include "s21_map_iterator.h"

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const &items) {
  for (const auto &it : items) {
    this->insert(it);
  }
}

template <typename Key, typename T>
T &map<Key, T>::at(const Key &key) {
  if (!this->contains(key)) {
    throw std::out_of_range("Not found");
  }
  TreeNode<Key, T> *found = this->FindPosition(key);
  T &value = found->value;
  return value;
}

template <typename Key, typename T>
T &map<Key, T>::operator[](const Key &key) {
  if (!this->contains(key)) {
    this->insert(key, 0);
  }
  TreeNode<Key, T> *found = this->FindPosition(key);
  T &value = found->value;
  return value;
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key &key, const T &obj) {
  std::pair<iterator, bool> result_pair{};
  if (this->contains(key)) {
    this->at(key) = obj;
    TreeNode<Key, T> *tnode = this->FindPosition(key);
    iterator it(this, tnode);
    result_pair = std::make_pair(it, false);
  } else {
    result_pair = this->insert(key, obj);
  }
  return result_pair;
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const typename map<Key, T>::value_type &value) {
  std::pair<typename RbTree<Key, T>::Iterator, bool> old_pair =
      this->RbTree<Key, T>::insert(value.first, value.second);
  std::pair<typename map<Key, T>::iterator, bool> result_pair =
      std::make_pair(old_pair.first, old_pair.second);
  return result_pair;
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key &key, const T &obj) {
  std::pair<typename RbTree<Key, T>::Iterator, bool> old_pair =
      this->RbTree<Key, T>::insert(key, obj);
  std::pair<typename map<Key, T>::iterator, bool> result_pair =
      std::make_pair(old_pair.first, old_pair.second);
  return result_pair;
}

template <typename Key, typename T>
template <typename... Args>
std::vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args &&...args) {
  std::vector<std::pair<typename map<Key, T>::iterator, bool>> vp{};
  for (auto arg : {args...}) {
    vp.push_back(this->insert(arg));
  }
  return vp;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  return map<Key, T>::iterator(this, RbTree<Key, T>::first_node);
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() {
  TreeNode<Key, T> *res = RbTree<Key, T>::fake_node_;
  if (res) {
    res->parent = RbTree<Key, T>::last_node;
  }
  return map<Key, T>::iterator(this, res);
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::begin() const {
  return map<Key, T>::const_iterator(this, RbTree<Key, T>::first_node);
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::end() const {
  TreeNode<Key, T> *res = RbTree<Key, T>::fake_node_;
  if (res) {
    res->parent = RbTree<Key, T>::last_node;
  }
  return map<Key, T>::const_iterator(this, res);
}

#endif  // S21_CONTAINERS_MAP_METHODS_H_
