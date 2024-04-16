#include "test_main.h"

using namespace S21RbTree;

class S21RbTreeDeleteTest : public testing::Test {
 protected:
  RbTree<int, int> Tree;

 public:
  S21RbTreeDeleteTest() : Tree(54, 0) {}
};

TEST_F(S21RbTreeDeleteTest, DeleteTop0) { Tree.erase(Tree.top_); }

TEST_F(S21RbTreeDeleteTest, DeleteTop1) {
  Tree.insert(41, 0);
  Tree.erase(Tree.top_);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key = 41);
}

TEST_F(S21RbTreeDeleteTest, DeleteTop2) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.erase(Tree.top_);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
}

TEST_F(S21RbTreeDeleteTest, DeleteTop3) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.erase(Tree.top_);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
}

TEST_F(S21RbTreeDeleteTest, DeleteTop4) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.erase(Tree.top_);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 36);
}

TEST_F(S21RbTreeDeleteTest, DeleteTop5) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.erase(Tree.top_);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 40);
}

TEST_F(S21RbTreeDeleteTest, DeleteTop6) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);

  Tree.erase(Tree.top_);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 40);
}

TEST_F(S21RbTreeDeleteTest, DeleteTop7) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.erase(Tree.top_);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 40);
}

TEST_F(S21RbTreeDeleteTest, DeleteTop8) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);

  Tree.erase(Tree.top_);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
}

TEST_F(S21RbTreeDeleteTest, DeleteTop9) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.erase(Tree.top_);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 43 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 40);
}

TEST_F(S21RbTreeDeleteTest, DeleteTop10) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.insert(44, 0);
  Tree.erase(Tree.top_);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 38);
}

TEST_F(S21RbTreeDeleteTest, DeleteTop11) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.insert(44, 0);
  Tree.insert(46, 0);
  Tree.erase(Tree.top_);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 46 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 44);
}

TEST_F(S21RbTreeDeleteTest, DeleteTop12) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.insert(44, 0);
  Tree.insert(46, 0);
  Tree.insert(47, 0);
  Tree.erase(Tree.top_);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 46 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 47 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 44);
}

TEST_F(S21RbTreeDeleteTest, DeleteTop13) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.insert(44, 0);
  Tree.insert(46, 0);
  Tree.insert(47, 0);
  Tree.insert(48, 0);
  Tree.erase(Tree.top_);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 46 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 47 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 48 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 44);
}

TEST_F(S21RbTreeDeleteTest, DeleteTop14) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.insert(44, 0);
  Tree.insert(46, 0);
  Tree.insert(47, 0);
  Tree.insert(48, 0);
  Tree.insert(49, 0);
  Tree.erase(Tree.top_);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 46 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 47 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 48 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 49 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 44);
}

TEST_F(S21RbTreeDeleteTest, Delete2Right1) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);

  Tree.erase(Tree.top_->right);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 38);
}

TEST_F(S21RbTreeDeleteTest, Delete2Right2) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.insert(44, 0);
  Tree.insert(46, 0);
  Tree.insert(47, 0);
  Tree.insert(48, 0);
  Tree.insert(49, 0);
  Tree.erase(Tree.top_->right);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 43 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 46 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 48 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 49 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 43);
}

TEST_F(S21RbTreeDeleteTest, Delete2Right3) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.insert(44, 0);
  Tree.insert(46, 0);
  Tree.insert(47, 0);
  Tree.insert(48, 0);
  Tree.insert(49, 0);
  Tree.erase(Tree.top_->right->right);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 43 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 46 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 47 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 48 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 43);
}

TEST_F(S21RbTreeDeleteTest, Delete2Right4) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.insert(44, 0);
  Tree.insert(46, 0);
  Tree.insert(47, 0);
  Tree.erase(Tree.top_->right);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 43 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 46 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 43);
}

TEST_F(S21RbTreeDeleteTest, Delete2Left1) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);

  Tree.erase(Tree.first_node->parent);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 41);
}

TEST_F(S21RbTreeDeleteTest, Delete2Left2) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.insert(44, 0);
  Tree.insert(46, 0);
  Tree.insert(47, 0);
  Tree.insert(48, 0);
  Tree.insert(49, 0);
  Tree.erase(Tree.first_node->parent);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 43 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 46 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 47 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 48 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 49 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 47);
}

TEST_F(S21RbTreeDeleteTest, Delete2Left3) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.insert(44, 0);
  Tree.insert(46, 0);
  Tree.insert(47, 0);
  Tree.insert(48, 0);
  Tree.insert(49, 0);
  Tree.erase(Tree.first_node->parent->parent);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 43 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 46 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 47 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 48 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 49 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 47);
}

TEST_F(S21RbTreeDeleteTest, Delete2Left4) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.insert(44, 0);
  Tree.insert(46, 0);
  Tree.insert(47, 0);
  Tree.insert(48, 0);
  Tree.erase(Tree.first_node->parent->parent->right);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 43 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 46 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 47 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 48 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 43);
}

TEST_F(S21RbTreeDeleteTest, Delete2LeftRed1) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.insert(44, 0);
  Tree.insert(46, 0);
  Tree.insert(47, 0);
  Tree.insert(48, 0);
  Tree.erase(Tree.first_node->parent->parent);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 43 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 46 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 47 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 48 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 43);
}

TEST_F(S21RbTreeDeleteTest, Delete2LeftRed2) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.erase(Tree.first_node->parent);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 41);
}

TEST_F(S21RbTreeDeleteTest, Delete2LeftRed3) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.insert(44, 0);
  Tree.insert(46, 0);
  Tree.insert(47, 0);
  Tree.insert(48, 0);
  Tree.erase(Tree.top_->right->left);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 43 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 46 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 47 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 48 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 43);
}

TEST_F(S21RbTreeDeleteTest, Delete1Left1) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.erase(Tree.first_node->parent);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 41);
}

TEST_F(S21RbTreeDeleteTest, Delete1Left2) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);

  Tree.erase(Tree.first_node->parent->right);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 41);
}

TEST_F(S21RbTreeDeleteTest, Delete1Right1) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.erase(Tree.top_->right->right);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 38);
}

TEST_F(S21RbTreeDeleteTest, Delete0Child1) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.erase(Tree.first_node);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 41 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 54);
}

TEST_F(S21RbTreeDeleteTest, Delete0Child2) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.erase(Tree.top_->right);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 38);
}

TEST_F(S21RbTreeDeleteTest, Delete0Child3) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.erase(Tree.top_->right);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 36);
}

TEST_F(S21RbTreeDeleteTest, Delete0Child4) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.insert(44, 0);
  Tree.insert(46, 0);
  Tree.insert(47, 0);
  Tree.erase(Tree.top_->left->right->left);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 43 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 46 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 47 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 43);
}

TEST_F(S21RbTreeDeleteTest, Delete0Child5) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.insert(44, 0);
  Tree.insert(46, 0);
  Tree.insert(47, 0);
  Tree.erase(Tree.top_->left->right->right);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 43 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 46 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 47 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 43);
}

TEST_F(S21RbTreeDeleteTest, Delete0Child6) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.insert(44, 0);
  Tree.insert(46, 0);
  Tree.insert(47, 0);
  Tree.erase(Tree.first_node);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 36 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 43 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 46 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 47 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 43);
}

TEST_F(S21RbTreeDeleteTest, Delete0Child7) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.insert(44, 0);
  Tree.insert(46, 0);
  Tree.insert(47, 0);
  Tree.erase(Tree.first_node->parent->right);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 43 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 46 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 47 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 43);
}

TEST_F(S21RbTreeDeleteTest, Delete0Child8) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);
  Tree.insert(44, 0);
  Tree.insert(46, 0);
  Tree.insert(47, 0);
  Tree.insert(48, 0);
  Tree.insert(49, 0);
  Tree.erase(Tree.first_node->parent->right);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 43 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 46 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 47 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 48 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 49 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
  EXPECT_TRUE(Tree.top_->key == 47);
}