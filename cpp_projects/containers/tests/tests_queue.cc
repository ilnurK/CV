#include <queue>

#include "test_main.h"

template <typename value_type>
bool check_eq(s21::queue<value_type> my, std::queue<value_type> orig) {
  bool result = true;
  if (my.size() == orig.size()) {
    while (!my.empty() && !orig.empty()) {
      if (my.front() != orig.front()) {
        result = false;
        break;
      }
      my.pop();
      orig.pop();
    }
  } else {
    result = false;
  }
  return result;
}

TEST(Queue_test, construct_def_empty) {
  s21::queue<int> my_queue;
  EXPECT_THROW(my_queue.back(), std::logic_error);

  s21::queue<int> my_queue1;
  my_queue1.push(1);
  my_queue1.push(2);
  my_queue1.push(3);
  my_queue1.push(4);

  std::queue<int> orig;
  orig.push(1);
  orig.push(2);
  orig.push(3);
  orig.push(4);

  int my_res = my_queue1.front();
  int res_orig = orig.front();
  int my_res1 = my_queue1.back();
  int res_orig1 = orig.back();
  EXPECT_EQ(my_res, res_orig);
  EXPECT_EQ(my_res1, res_orig1);
}

TEST(Queue_test, front) {
  s21::queue<int> my_queue;
  EXPECT_THROW(my_queue.front(), std::logic_error);
}

TEST(Queue_test, empty) {
  s21::queue<int> my_queue;
  std::queue<int> orig;
  EXPECT_EQ(my_queue.empty(), orig.empty());
}

TEST(Queue_test, swap1) {
  s21::queue<int> q1 = {1, 2, 3, 5, 6, 7};
  s21::queue<int> q2 = {55, 22, 53, 8342, 5643, 422};
  q1.swap(q2);
  EXPECT_EQ(q1.back(), 422);
  EXPECT_EQ(q1.front(), 55);
}

TEST(Queue_test, swap2) {
  s21::queue<int> q1 = {1, 2, 3, 5, 6, 7};
  s21::queue<int> q2 = {55, 22, 53, 8342, 5643, 422, 44, 76, 33};
  q1.swap(q2);
  EXPECT_EQ(q1.back(), 33);
  EXPECT_EQ(q1.front(), 55);
}

TEST(Queue_test, swap3) {
  s21::queue<int> q1;
  s21::queue<int> q2;
  q1.swap(q2);
  EXPECT_THROW(q1.back(), std::logic_error);
  EXPECT_THROW(q1.front(), std::logic_error);
}

TEST(Queue_test, CompareQueues) {
  s21::queue<int> my_queue{1, 3, 10, -5, 20};
  std::queue<int> orig_queue;
  orig_queue.push(1);
  orig_queue.push(3);
  orig_queue.push(10);
  orig_queue.push(-5);
  orig_queue.push(20);
  EXPECT_TRUE(check_eq(my_queue, orig_queue));
  orig_queue.push(20);
  EXPECT_FALSE(check_eq(my_queue, orig_queue));
}

TEST(Queue_test, pop) {
  s21::queue<int> my{1, 3, 10, -5, 20, 21};
  std::queue<int> orig;
  orig.push(1);
  orig.push(3);
  orig.push(10);
  orig.push(-5);
  orig.push(20);
  orig.push(21);
  my.pop();
  my.pop();
  orig.pop();
  orig.pop();
  EXPECT_TRUE(check_eq(my, orig));
  EXPECT_EQ(my.front(), 10);

  s21::queue<int> empty_my;
  EXPECT_THROW(empty_my.back(), std::logic_error);
  EXPECT_THROW(empty_my.pop(), std::logic_error);
  EXPECT_THROW(empty_my.front(), std::logic_error);
}

TEST(Queue_test, InitializerqueueConstructor_2) {
  std::initializer_list<int> b;
  s21::queue<int> my{b};
  std::queue<int> orig{b};
  EXPECT_TRUE(check_eq(my, orig));
}

TEST(Queue_test, MoveConstructor) {
  std::queue<int> orig;
  orig.push(1);
  orig.push(3);
  orig.push(10);
  orig.push(-5);
  orig.push(20);
  orig.push(21);

  s21::queue<int> my;
  my.push(1);
  my.push(3);
  my.push(10);
  my.push(-5);
  my.push(20);
  my.push(21);
  EXPECT_TRUE(check_eq(my, orig));
}

TEST(Queue_test, InsertManyBack) {
  s21::queue<int> my_queue;
  my_queue.push(97);
  ASSERT_EQ(my_queue.front(), 97);
  my_queue.insert_many_back(1, 2, 3, 4, 5);
  ASSERT_EQ(my_queue.front(), 97);
  my_queue.pop();
  ASSERT_EQ(my_queue.front(), 1);
  my_queue.pop();
  ASSERT_EQ(my_queue.front(), 2);
}
