#ifndef S21_CONTAINERS_S21_SET_H_
#define S21_CONTAINERS_S21_SET_H_

#include <vector>

#include "../s21_rb_tree/s21_rb_tree.h"

namespace s21 {

template <typename Key>
class set : public S21RbTree::RbTree<Key, int> {
 private:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using Tree = S21RbTree::RbTree<key_type, int>;
  using iterator = typename Tree::Iterator;
  using const_iterator = typename Tree::ConstIterator;
  using size_type = size_t;

 public:
  set() {}

  set(Key key) : Tree::RbTree(key) {}

  set(std::initializer_list<value_type> const &items) {
    for (value_type item : items) this->insert(item, 0);
  }

  iterator find(const_reference key) {
    S21RbTree::TreeNode<Key, int> *found = this->FindPosition(key);
    if (found && found->key != key) {
      found = nullptr;
    }
    return iterator(this, found);
  }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<typename set<Key>::iterator, bool>> vector;
    for (const auto &arg : {args...}) {
      vector.push_back(Tree::insert(arg));
    }
    return vector;
  }
};

}  // namespace s21

#endif  // S21_CONTAINERS_S21_SET_H_