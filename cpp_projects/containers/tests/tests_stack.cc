#include <stack>

#include "test_main.h"

TEST(stack, case1) {
  s21::stack<int> s21_stack_int;
  s21::stack<double> s21_stack_double;
  s21::stack<std::string> s21_stack_string;

  EXPECT_EQ(s21_stack_int.size(), 0U);
  EXPECT_THROW(s21_stack_int.top(), std::logic_error);
  EXPECT_THROW(s21_stack_int.pop(), std::logic_error);

  EXPECT_EQ(s21_stack_double.size(), 0U);
  EXPECT_THROW(s21_stack_double.top(), std::logic_error);
  EXPECT_THROW(s21_stack_double.pop(), std::logic_error);

  EXPECT_EQ(s21_stack_string.size(), 0U);
  EXPECT_THROW(s21_stack_string.top(), std::logic_error);
  EXPECT_THROW(s21_stack_string.pop(), std::logic_error);
}

TEST(stack, case2) {
  s21::stack<int> s21_stack_int{1, 4, 8, 9, 1};
  s21::stack<double> s21_stack_double{1.7, -4.3, 8.2, 274.3, 0.1};
  s21::stack<std::string> s21_stack_string{"s", "21", "stack", "test", "!!"};

  EXPECT_EQ(s21_stack_int.size(), 5U);
  EXPECT_EQ(s21_stack_int.top(), 1);

  EXPECT_EQ(s21_stack_double.size(), 5U);
  EXPECT_EQ(s21_stack_double.top(), 0.1);

  EXPECT_EQ(s21_stack_string.size(), 5U);
  EXPECT_EQ(s21_stack_string.top(), "!!");
}

TEST(stack, case3) {
  s21::stack<int> s21_stack_ref_int{1, 4, 8, 9, 1};
  s21::stack<int> s21_stack_res_int(s21_stack_ref_int);

  s21::stack<double> s21_stack_ref_double{1.7, -4.3, 8.2, 274.3, 0.1};
  s21::stack<double> s21_stack_res_double(s21_stack_ref_double);

  s21::stack<std::string> s21_stack_ref_string{"s", "21", "stack", "test",
                                               "!!"};
  s21::stack<std::string> s21_stack_res_string(s21_stack_ref_string);

  EXPECT_EQ(s21_stack_res_int.size(), 5U);
  EXPECT_EQ(s21_stack_res_int.top(), 1);

  EXPECT_EQ(s21_stack_res_double.size(), 5U);
  EXPECT_EQ(s21_stack_res_double.top(), 0.1);

  EXPECT_EQ(s21_stack_res_string.size(), 5U);
  EXPECT_EQ(s21_stack_res_string.top(), "!!");
}

TEST(stack, case4) {
  s21::stack<int> s21_stack_ref_int{1, 4, 8, 9, 1};
  s21::stack<int> s21_stack_res_int = s21_stack_ref_int;

  s21::stack<double> s21_stack_ref_double{1.7, -4.3, 8.2, 274.3, 0.1};
  s21::stack<double> s21_stack_res_double = s21_stack_ref_double;

  s21::stack<std::string> s21_stack_ref_string{"s", "21", "stack", "test",
                                               "!!"};
  s21::stack<std::string> s21_stack_res_string = s21_stack_ref_string;

  EXPECT_EQ(s21_stack_res_int.size(), 5U);
  EXPECT_EQ(s21_stack_res_int.top(), 1);

  EXPECT_EQ(s21_stack_res_double.size(), 5U);
  EXPECT_EQ(s21_stack_res_double.top(), 0.1);

  EXPECT_EQ(s21_stack_res_string.size(), 5U);
  EXPECT_EQ(s21_stack_res_string.top(), "!!");
}

TEST(stack, case5) {
  s21::stack<int> s21_stack_ref_int{1, 4, 8, 9, 1};
  s21::stack<int> s21_stack_res_int = std::move(s21_stack_ref_int);

  s21::stack<double> s21_stack_ref_double{1.7, -4.3, 8.2, 274.3, 0.1};
  s21::stack<double> s21_stack_res_double = std::move(s21_stack_ref_double);

  s21::stack<std::string> s21_stack_ref_string{"s", "21", "stack", "test",
                                               "!!"};
  s21::stack<std::string> s21_stack_res_string =
      std::move(s21_stack_ref_string);

  EXPECT_EQ(s21_stack_ref_int.size(), 0U);
  EXPECT_EQ(s21_stack_res_int.size(), 5U);
  EXPECT_EQ(s21_stack_res_int.top(), 1);

  EXPECT_EQ(s21_stack_ref_double.size(), 0U);
  EXPECT_EQ(s21_stack_res_double.size(), 5U);
  EXPECT_EQ(s21_stack_res_double.top(), 0.1);

  EXPECT_EQ(s21_stack_ref_string.size(), 0U);
  EXPECT_EQ(s21_stack_res_string.size(), 5U);
  EXPECT_EQ(s21_stack_res_string.top(), "!!");
}

TEST(stack, case6) {
  s21::stack<int> s21_stack_ref_int{1, 4, 8, 9, 1};
  s21::stack<int> s21_stack_res_int;
  s21_stack_res_int = std::move(s21_stack_ref_int);

  s21::stack<double> s21_stack_ref_double{1.7, -4.3, 8.2, 274.3, 0.1};
  s21::stack<double> s21_stack_res_double;
  s21_stack_res_double = std::move(s21_stack_ref_double);

  s21::stack<std::string> s21_stack_ref_string{"s", "21", "stack", "test",
                                               "!!"};
  s21::stack<std::string> s21_stack_res_string;
  s21_stack_res_string = std::move(s21_stack_ref_string);

  EXPECT_EQ(s21_stack_ref_int.size(), 0U);
  EXPECT_EQ(s21_stack_res_int.size(), 5U);
  EXPECT_EQ(s21_stack_res_int.top(), 1);

  EXPECT_EQ(s21_stack_ref_double.size(), 0U);
  EXPECT_EQ(s21_stack_res_double.size(), 5U);
  EXPECT_EQ(s21_stack_res_double.top(), 0.1);

  EXPECT_EQ(s21_stack_ref_string.size(), 0U);
  EXPECT_EQ(s21_stack_res_string.size(), 5U);
  EXPECT_EQ(s21_stack_res_string.top(), "!!");
}

TEST(stack, case7) {
  int n = 5;
  s21::stack<int> my = {};
  std::stack<int> orig = {};
  for (int i = 0; i < n; i++) {
    my.push(i);
    orig.push(i);
  }
  EXPECT_EQ(my.size(), orig.size());
  my.pop();
  my.pop();
  orig.pop();
  orig.pop();
  EXPECT_EQ(my.size(), orig.size());
  int my_top = my.top();
  int orig_top = orig.top();
  EXPECT_EQ(my_top, orig_top);
}

TEST(stack, empty1) {
  s21::stack<int> s21_stack_int{1, 4, 8, 9, 1};
  s21::stack<double> s21_stack_double{1.7, -4.3, 8.2, 274.3, 0.1};
  s21::stack<std::string> s21_stack_string{"s", "21", "stack", "test", "!!"};

  EXPECT_EQ(s21_stack_int.empty(), 0);
  EXPECT_EQ(s21_stack_double.empty(), 0);
  EXPECT_EQ(s21_stack_string.empty(), 0);
}

TEST(stack, empty2) {
  s21::stack<int> s21_stack_int;
  s21::stack<double> s21_stack_double;
  s21::stack<std::string> s21_stack_string;

  EXPECT_EQ(s21_stack_int.empty(), 1);
  EXPECT_EQ(s21_stack_double.empty(), 1);
  EXPECT_EQ(s21_stack_string.empty(), 1);
}

TEST(stack, size1) {
  s21::stack<int> s21_stack_int{1, 4, 8, 9, 1};
  s21::stack<double> s21_stack_double{1.7, -4.3, 8.2, 274.3, 0.1};
  s21::stack<std::string> s21_stack_string{"s", "21", "stack", "test", "!!"};

  EXPECT_EQ(s21_stack_int.size(), 5U);
  EXPECT_EQ(s21_stack_double.size(), 5U);
  EXPECT_EQ(s21_stack_string.size(), 5U);
}

TEST(stack, size2) {
  s21::stack<int> s21_stack_int;
  s21::stack<double> s21_stack_double;
  s21::stack<std::string> s21_stack_string;

  EXPECT_EQ(s21_stack_int.size(), 0U);
  EXPECT_EQ(s21_stack_double.size(), 0U);
  EXPECT_EQ(s21_stack_string.size(), 0U);
}

TEST(stack, top1) {
  s21::stack<int> s21_stack_int{1, 4, 8, 9, 1};
  s21::stack<double> s21_stack_double{1.7, -4.3, 8.2, 274.3, 0.1};
  s21::stack<std::string> s21_stack_string{"s", "21", "stack", "test", "!!"};

  EXPECT_EQ(s21_stack_int.top(), 1);
  EXPECT_EQ(s21_stack_double.top(), 0.1);
  EXPECT_EQ(s21_stack_string.top(), "!!");
}

TEST(stack, top2) {
  s21::stack<int> s21_stack_int;
  s21::stack<double> s21_stack_double;
  s21::stack<std::string> s21_stack_string;

  EXPECT_THROW(s21_stack_int.top(), std::logic_error);
  EXPECT_THROW(s21_stack_double.top(), std::logic_error);
  EXPECT_THROW(s21_stack_string.top(), std::logic_error);
}

TEST(stack, push1) {
  s21::stack<int> s21_stack_int{1, 4, 8, 9, 1};
  s21::stack<double> s21_stack_double{1.7, -4.3, 8.2, 274.3, 0.1};
  s21::stack<std::string> s21_stack_string{"s", "21", "stack", "test", "!!"};

  s21_stack_int.push(322);
  s21_stack_double.push(322.0);
  s21_stack_string.push("322");

  EXPECT_EQ(s21_stack_int.top(), 322);
  EXPECT_EQ(s21_stack_double.top(), 322.0);
  EXPECT_EQ(s21_stack_string.top(), "322");
}

TEST(stack, push2) {
  s21::stack<int> s21_stack_int;
  s21::stack<double> s21_stack_double;
  s21::stack<std::string> s21_stack_string;

  s21_stack_int.push(322);
  s21_stack_double.push(322.0);
  s21_stack_string.push("322");

  EXPECT_EQ(s21_stack_int.top(), 322);
  EXPECT_EQ(s21_stack_double.top(), 322.0);
  EXPECT_EQ(s21_stack_string.top(), "322");
}

TEST(stack, pop1) {
  s21::stack<int> s21_stack_int{1, 4, 8, 9, 1};
  s21::stack<double> s21_stack_double{1.7, -4.3, 8.2, 274.3, 0.1};
  s21::stack<std::string> s21_stack_string{"s", "21", "stack", "test", "!!"};

  s21_stack_int.pop();
  s21_stack_double.pop();
  s21_stack_string.pop();

  EXPECT_EQ(s21_stack_int.top(), 9);
  EXPECT_EQ(s21_stack_double.top(), 274.3);
  EXPECT_EQ(s21_stack_string.top(), "test");
}

TEST(stack, pop2) {
  s21::stack<int> s21_stack_int;
  s21::stack<double> s21_stack_double;
  s21::stack<std::string> s21_stack_string;

  EXPECT_THROW(s21_stack_int.pop(), std::logic_error);
  EXPECT_THROW(s21_stack_double.pop(), std::logic_error);
  EXPECT_THROW(s21_stack_string.pop(), std::logic_error);
}

TEST(stack, swap1) {
  s21::stack<int> s21_stack_ref_int{1, 4, 8, 9, 1};
  s21::stack<int> s21_stack_res_int;

  s21::stack<double> s21_stack_ref_double{1.7, -4.3, 8.2, 274.3, 0.1};
  s21::stack<double> s21_stack_res_double;

  s21::stack<std::string> s21_stack_ref_string{"s", "21", "stack", "test",
                                               "!!"};
  s21::stack<std::string> s21_stack_res_string;

  s21_stack_ref_int.swap(s21_stack_res_int);
  s21_stack_ref_double.swap(s21_stack_res_double);
  s21_stack_ref_string.swap(s21_stack_res_string);

  EXPECT_EQ(s21_stack_ref_int.size(), 0U);
  EXPECT_EQ(s21_stack_res_int.size(), 5U);
  EXPECT_EQ(s21_stack_res_int.top(), 1);

  EXPECT_EQ(s21_stack_ref_double.size(), 0U);
  EXPECT_EQ(s21_stack_res_double.size(), 5U);
  EXPECT_EQ(s21_stack_res_double.top(), 0.1);

  EXPECT_EQ(s21_stack_ref_string.size(), 0U);
  EXPECT_EQ(s21_stack_res_string.size(), 5U);
  EXPECT_EQ(s21_stack_res_string.top(), "!!");
}

TEST(stack, swap2) {
  s21::stack<int> s21_stack_ref_int{1, 4, 8, 9, 1};
  s21::stack<int> s21_stack_res_int{12, 13, 14};

  s21::stack<double> s21_stack_ref_double{1.7, -4.3, 8.2, 274.3, 0.1};
  s21::stack<double> s21_stack_res_double{322.0};

  s21::stack<std::string> s21_stack_ref_string{"s", "21", "stack", "test",
                                               "!!"};
  s21::stack<std::string> s21_stack_res_string{"a", "b"};

  s21_stack_ref_int.swap(s21_stack_res_int);
  s21_stack_ref_double.swap(s21_stack_res_double);
  s21_stack_ref_string.swap(s21_stack_res_string);

  EXPECT_EQ(s21_stack_ref_int.size(), 3U);
  EXPECT_EQ(s21_stack_ref_int.top(), 14);
  EXPECT_EQ(s21_stack_res_int.size(), 5U);
  EXPECT_EQ(s21_stack_res_int.top(), 1);

  EXPECT_EQ(s21_stack_ref_double.size(), 1U);
  EXPECT_EQ(s21_stack_ref_double.top(), 322.0);
  EXPECT_EQ(s21_stack_res_double.size(), 5U);
  EXPECT_EQ(s21_stack_res_double.top(), 0.1);

  EXPECT_EQ(s21_stack_ref_string.size(), 2U);
  EXPECT_EQ(s21_stack_ref_string.top(), "b");
  EXPECT_EQ(s21_stack_res_string.size(), 5U);
  EXPECT_EQ(s21_stack_res_string.top(), "!!");
}

TEST(stack, insert_many_front) {
  s21::stack<int> my_stack{97};
  EXPECT_EQ(my_stack.top(), 97);
  my_stack.insert_many_front(23, 15);
  EXPECT_EQ(my_stack.top(), 15);
  my_stack.pop();
  EXPECT_EQ(my_stack.top(), 23);
}
