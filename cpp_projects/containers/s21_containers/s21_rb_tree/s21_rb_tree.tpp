#ifndef S21_CONTAINERS_S21_RB_TREE_METHODS_H_
#define S21_CONTAINERS_S21_RB_TREE_METHODS_H_

#include "s21_rb_tree.h"
#include "s21_rb_tree_iterator.h"

template <typename K, typename V>
RbTree<K, V>::RbTree(K key, V value) {
  top_ = new TreeNode<K, V>(key, value);
  first_node = last_node = top_;
  top_->color = BLACK;
  tree_size++;
}

template <typename K, typename V>
RbTree<K, V>::RbTree(RbTree &&other) {
  if (*this != other) {
    swap(other);
  }
  other.clear();
}

template <typename K, typename V>
RbTree<K, V>::RbTree(const RbTree &other) {
  for (ConstIterator it = other.begin(), ite = other.end(); it != ite; ++it) {
    insert(*it, it.GetValue());
  }
}

template <typename K, typename V>
RbTree<K, V>::~RbTree() {
  this->clear();
  delete fake_node_;
}

template <typename K, typename V>
std::pair<typename RbTree<K, V>::Iterator, bool> RbTree<K, V>::insert(
    const K &key_in, const V &value_in) {
  TreeNode<K, V> *new_node = new TreeNode<K, V>(key_in, value_in);
  TreeNode<K, V> *parent = this->FindPosition(key_in);
  bool is_inserted = true;
  if (parent) {
    new_node->parent = parent;
    if (key_in < parent->key) {
      parent->left = new_node;
      first_node = (parent == first_node) ? new_node : first_node;
    } else if (key_in > parent->key) {
      parent->right = new_node;
      last_node = (parent == last_node) ? new_node : last_node;
    } else if (key_in == parent->key && is_multiset) {
      TreeNode<K, V> *temp = FindNearestGreater(parent);
      if (temp) {
        new_node->parent = temp;
        temp->left = new_node;
      } else {
        parent->right = new_node;
      }
      first_node = (parent == first_node && parent->key != key_in) ? new_node
                                                                   : first_node;
    } else {
      delete new_node;
      is_inserted = false;
    }
    if (is_inserted) {
      Rebalance(new_node);
    }
  } else {
    top_ = first_node = last_node = new_node;
    top_->color = BLACK;
  }
  tree_size += is_inserted ? 1 : 0;
  TreeNode<K, V> *insert_node = new_node ? new_node : parent;
  return std::pair<Iterator, bool>(Iterator(this, insert_node), is_inserted);
}

template <typename K, typename V>
TreeNode<K, V> *RbTree<K, V>::FindPosition(K key_in) const {
  TreeNode<K, V> *cur = top_;
  bool find_pos = 0;
  while (!find_pos && cur) {
    if (key_in < cur->key) {
      if (cur->left == nullptr) {
        find_pos = 1;
      } else {
        cur = cur->left;
      }
    } else if (key_in > cur->key) {
      if (cur->right == nullptr) {
        find_pos = 1;
      } else {
        cur = cur->right;
      }
    } else {
      find_pos = 1;
    }
  }
  return cur;
}

template <typename K, typename V>
void RbTree<K, V>::Rebalance(TreeNode<K, V> *cur) {
  if (cur) {
    bool not_skip = 1;
    if (cur->left && cur->left->color == RED && cur->right &&
        cur->right->color == RED) {
      if (cur->color != RED) {
        SwapColor(cur);
      } else {
        not_skip = 0;
      }
    }
    if (cur->right && cur->right->color == RED && not_skip) {
      Turn(cur->right, LEFT);
      if (cur->right) {
        cur = cur->right;
      }
    }
    if (cur->left && cur->left->color == RED && cur->left->left &&
        cur->left->left->color == RED && not_skip) {
      if (cur->color == RED) {
        SwapColor(cur->parent);
      }
      Turn(cur->left, RIGHT);
      if (cur->left) {
        cur = cur->left;
      }
    }
    if (cur->parent != nullptr) {
      Rebalance(cur->parent);
    }
  }
}

template <typename K, typename V>
void RbTree<K, V>::SwapColor(TreeNode<K, V> *cur) {
  if (cur != top_) {
    cur->color = RED;
  }
  cur->right->color = BLACK;
  cur->left->color = BLACK;
}

template <typename K, typename V>
void RbTree<K, V>::Turn(TreeNode<K, V> *cur, bool turn) {
  TreeNode<K, V> *parent = cur->parent;
  TreeNode<K, V> *child = (turn == LEFT) ? cur->left : cur->right;
  bool temp_color = cur->color;

  cur->color = parent->color;
  cur->parent = parent->parent;
  if (turn == LEFT) {
    cur->left = parent;
  } else {
    cur->right = parent;
  }

  parent->color = temp_color;
  parent->parent = cur;
  if (turn == LEFT) {
    parent->right = child;
  } else {
    parent->left = child;
  }
  if (child) {
    child->parent = parent;
  }

  if (cur->parent) {
    if (cur->parent->left == parent) {
      cur->parent->left = cur;
    } else {
      cur->parent->right = cur;
    }
  } else {
    top_ = cur;
  }
}

template <typename K, typename V>
void RbTree<K, V>::erase(TreeNode<K, V> *del) {
  if (del && del->left && del->right) {
    ReplaceCycle(del);
  } else if (del && del->left) {
    TreeNode<K, V> *child = del->left;
    child->parent = del->parent;
    child->color = BLACK;
    if (del == top_) {
      top_ = child;
    } else {
      if (del == del->parent->left) {
        del->parent->left = child;
      } else {
        del->parent->right = child;
      }
    }
  } else if (del && del->parent) {
    if (del->color == BLACK) {
      MakeAllOtherChildRed(del);
      TreeNode<K, V> *sibling = nullptr;
      if (del == del->parent->left) {
        del->parent->left = nullptr;
        sibling = del->parent->right;
      } else {
        del->parent->right = nullptr;
        sibling = del->parent->left;
      }
      while (sibling && sibling->parent) {
        Rebalance(sibling);
        sibling = sibling->parent;
      }
    } else {
      del->parent->left = nullptr;
    }
    if (del == first_node) {
      first_node = del->parent;
    } else if (del == first_node) {
      last_node = del->parent;
    }
  } else {
    top_ = nullptr;
  }
  tree_size -= (del) ? 1 : 0;
  delete del;
}

template <typename K, typename V>
void RbTree<K, V>::erase(Iterator it) {
  TreeNode<K, V> *found = FindPosition(*it);
  erase(found);
}

template <typename K, typename V>
TreeNode<K, V> *RbTree<K, V>::ReplaceCycle(TreeNode<K, V> *del) {
  TreeNode<K, V> *greater = FindNearestGreater(del);
  TreeNode<K, V> *grt_parent = greater->parent;
  TreeNode<K, V> *right = del->right;
  if (greater->color == BLACK) {
    MakeAllOtherChildRed(greater);
    SwapToGreater(del, greater);
    Rebalance(greater);
    TreeNode<K, V> *sibling = nullptr;
    if (grt_parent->right != right) {
      sibling = grt_parent->right;
    }
    while (sibling && sibling->parent) {
      Rebalance(sibling);
      sibling = sibling->parent;
    }
    Rebalance(greater);
    Rebalance(top_->left);
  } else {
    SwapToGreater(del, greater);
  }
  return greater;
}

template <typename K, typename V>
TreeNode<K, V> *RbTree<K, V>::FindNearestGreater(TreeNode<K, V> *cur) {
  TreeNode<K, V> *greater = cur->right;
  while (greater && greater->left != nullptr) {
    greater = greater->left;
  }
  return greater;
}

template <typename K, typename V>
void RbTree<K, V>::MakeAllOtherChildRed(TreeNode<K, V> *sibling) {
  while (sibling->parent) {
    TreeNode<K, V> *req_side = nullptr;
    if (sibling == sibling->parent->right) {
      req_side = sibling->parent->left;
    } else {
      req_side = sibling->parent->right;
    }
    if (req_side->color == RED) {
      req_side->left->color = RED;
      req_side->right->color = RED;
    } else {
      req_side->color = RED;
    }
    sibling = sibling->parent;
  }
}

template <typename K, typename V>
void RbTree<K, V>::SwapToGreater(TreeNode<K, V> *del, TreeNode<K, V> *greater) {
  greater->left = del->left;
  greater->left->parent = greater;
  if (greater == del->right) {
    greater->right = nullptr;
  } else {
    greater->right = del->right;
    greater->right->parent = greater;
  }
  greater->parent->left = nullptr;
  greater->parent = nullptr;
  if (del->parent) {
    if (del == del->parent->right) {
      del->parent->right = greater;
    } else {
      del->parent->left = greater;
    }
    greater->parent = del->parent;
  }
  greater->color = del->color;
  if (del == top_) {
    top_ = greater;
    greater->color = BLACK;
  }
}

template <typename K, typename V>
size_t RbTree<K, V>::max_size() {
  return std::numeric_limits<size_t>::max() / sizeof(TreeNode<K, V>);
}

template <typename K, typename V>
void RbTree<K, V>::clear() {
  TreeNode<K, V> *cur = this->FindFurthest(top_);
  TreeNode<K, V> *parent = nullptr;
  do {
    if (cur && cur->parent) {
      parent = cur->parent;
      if (cur == parent->left) {
        cur->parent->left = nullptr;
      } else {
        cur->parent->right = nullptr;
      }
    } else {
      parent = nullptr;
    }
    delete cur;
  } while ((cur = this->FindFurthest(parent)) != nullptr);
  top_ = first_node = last_node = nullptr;
  tree_size = 0;
}

template <typename K, typename V>
TreeNode<K, V> *RbTree<K, V>::FindFurthest(TreeNode<K, V> *cur) {
  if (cur) {
    bool find_last = 0;
    while (!find_last) {
      if (cur->left != nullptr) {
        cur = cur->left;
      } else if (cur->right != nullptr) {
        cur = cur->right;
      } else {
        find_last = 1;
      }
    }
  }
  return cur;
}

template <typename K, typename V>
void RbTree<K, V>::swap(RbTree<K, V> &other) {
  std::swap(top_, other.top_);
  std::swap(first_node, other.first_node);
  std::swap(last_node, other.last_node);
  std::swap(tree_size, other.tree_size);
}

template <typename K, typename V>
void RbTree<K, V>::merge(RbTree<K, V> &other) {
  for (Iterator it = other.begin(), end = other.end(); it != end; ++it) {
    this->insert(*it, it.GetValue());
  }
  other.clear();
}

template <typename K, typename V>
bool RbTree<K, V>::contains(const K &key) const {
  TreeNode<K, V> *found = this->FindPosition(key);
  return found && found->key == key ? true : false;
}

template <typename K, typename V>
bool RbTree<K, V>::operator!=(const RbTree<K, V> &other) const {
  bool res = 0, in_cycle = 0;
  auto it = begin(), ite = end();
  auto ito = other.begin(), itoe = other.end();
  while (!res && it != ite && ito != itoe) {
    if (it != ito) {
      res = 1;
    }
    ++it;
    ++ito;
    in_cycle = 1;
  }
  res = (res == 0 && in_cycle == 0) ? 1 : 0;
  return res;
}

template <typename K, typename V>
RbTree<K, V> &RbTree<K, V>::operator=(RbTree<K, V> &&other) {
  if (*this != other) {
    swap(other);
  }
  other.clear();
  return *this;
}

template <typename K, typename V>
RbTree<K, V> &RbTree<K, V>::operator=(const RbTree<K, V> &other) {
  if (*this != other) {
    clear();
    for (auto it : other) {
      insert(it, it.GetValue());
    }
  }
  return *this;
}

template <typename K, typename V>
typename RbTree<K, V>::Iterator RbTree<K, V>::begin() {
  return Iterator(this, first_node);
}

template <typename K, typename V>
typename RbTree<K, V>::Iterator RbTree<K, V>::end() {
  TreeNode<K, V> *res = fake_node_;
  if (last_node) {
    res->parent = last_node;
  }
  return Iterator(this, res);
}

template <typename K, typename V>
typename RbTree<K, V>::ConstIterator RbTree<K, V>::begin() const {
  return ConstIterator(this, first_node);
}

template <typename K, typename V>
typename RbTree<K, V>::ConstIterator RbTree<K, V>::end() const {
  TreeNode<K, V> *res = fake_node_;
  if (last_node) {
    res->parent = last_node;
  }
  return ConstIterator(this, res);
}

#endif  // S21_CONTAINERS_S21_RB_TREE_METHODS_H