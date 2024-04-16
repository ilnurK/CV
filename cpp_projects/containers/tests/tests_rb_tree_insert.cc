#include "test_main.h"

using namespace S21RbTree;

class S21RbTreeInsertTest : public testing::Test {
 protected:
  RbTree<int, int> Tree;

 public:
  S21RbTreeInsertTest() : Tree(54, 0) {}
};

TEST_F(S21RbTreeInsertTest, Insert1) {
  Tree.insert(41, 0);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 41 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
}

TEST_F(S21RbTreeInsertTest, Insert2) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
}

TEST_F(S21RbTreeInsertTest, Insert3) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
}

TEST_F(S21RbTreeInsertTest, Insert4) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
}

TEST_F(S21RbTreeInsertTest, Insert5) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
}

TEST_F(S21RbTreeInsertTest, Insert6) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
}

TEST_F(S21RbTreeInsertTest, Insert7) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
}

TEST_F(S21RbTreeInsertTest, Insert8) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
}

TEST_F(S21RbTreeInsertTest, Insert9) {
  Tree.insert(41, 0);
  Tree.insert(30, 0);
  Tree.insert(38, 0);
  Tree.insert(36, 0);
  Tree.insert(40, 0);
  Tree.insert(37, 0);
  Tree.insert(45, 0);
  Tree.insert(42, 0);
  Tree.insert(43, 0);

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == RED);
  EXPECT_TRUE(*(++it) == 43 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
}

TEST_F(S21RbTreeInsertTest, Insert10) {
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
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
}

TEST_F(S21RbTreeInsertTest, Insert11) {
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
}

TEST_F(S21RbTreeInsertTest, Insert12) {
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
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
}

TEST_F(S21RbTreeInsertTest, Insert13) {
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
}

TEST_F(S21RbTreeInsertTest, Insert14) {
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

  auto it = Tree.begin();
  EXPECT_TRUE(*it == 30 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 36 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 37 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 38 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 40 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 41 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 42 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 43 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 44 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 45 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 46 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 47 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 48 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 49 && it.GetColor() == BLACK);
  EXPECT_TRUE(*(++it) == 54 && it.GetColor() == BLACK);
}

TEST(S21RbTreeNullConstructor, Test1) { RbTree<int, int> a; }
