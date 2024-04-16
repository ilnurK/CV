#ifndef S21_CONTAINERS_S21_RB_TREE_H_
#define S21_CONTAINERS_S21_RB_TREE_H_

#include <limits>

namespace S21RbTree {
const bool RED = 1;
const bool BLACK = 0;
const bool LEFT = 1;
const bool RIGHT = 0;

template <typename K, typename V>
class TreeNode {
 public:
  K key{};
  V value{};
  bool color = RED;
  TreeNode *parent = nullptr;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;

 public:
  TreeNode(K key_in, V value_in) : key(key_in), value(value_in){};
  TreeNode(K key_in) : TreeNode(key_in, 0){};
  TreeNode() {}
};

template <typename K, typename V>
class RbTree {
 private:
  size_t tree_size = 0;

 protected:
  bool is_multiset = false;
  TreeNode<K, V> *fake_node_ = new TreeNode<K, V>{};

 public:
  TreeNode<K, V> *top_{};
  TreeNode<K, V> *first_node{};
  TreeNode<K, V> *last_node{};

 protected:
  TreeNode<K, V> *FindFurthest(TreeNode<K, V> *cur);
  void Rebalance(TreeNode<K, V> *cur);
  void Turn(TreeNode<K, V> *cur, bool turn);
  void SwapColor(TreeNode<K, V> *cur);

  TreeNode<K, V> *ReplaceCycle(TreeNode<K, V> *del);
  void SwapToGreater(TreeNode<K, V> *del, TreeNode<K, V> *greater);
  void MakeAllOtherChildRed(TreeNode<K, V> *other);
  TreeNode<K, V> *FindNearestGreater(TreeNode<K, V> *cur);
  TreeNode<K, V> *FindPosition(K key_in) const;

 public:
  RbTree(K key_in, V value_in);
  RbTree(K key) : RbTree(key, 0) {}
  RbTree() {}
  RbTree(const RbTree &other);
  RbTree(RbTree &&other);

  ~RbTree();
  class Iterator;
  class ConstIterator;

  std::pair<Iterator, bool> insert(const K &key_in, const V &value_in);
  std::pair<Iterator, bool> insert(const K &key_in) {
    return this->insert(key_in, 0);
  }
  void erase(TreeNode<K, V> *cur);
  void erase(Iterator it);
  bool empty() { return top_ == nullptr; }
  size_t size() { return tree_size; }
  size_t max_size();
  void clear();
  void swap(RbTree<K, V> &other);
  void merge(RbTree<K, V> &other);
  bool contains(const K &key) const;

  Iterator begin();
  Iterator end();
  ConstIterator begin() const;
  ConstIterator end() const;
  bool operator!=(const RbTree<K, V> &other) const;
  RbTree<K, V> &operator=(RbTree<K, V> &&m);
  RbTree<K, V> &operator=(const RbTree<K, V> &m);
};

#include "s21_rb_tree.tpp"

}  // namespace S21RbTree

#endif  // S21_CONTAINERS_S21_RB_TREE_H_