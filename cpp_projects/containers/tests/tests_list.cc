#include <list>

#include "test_main.h"

TEST(List_test, case1) {
  s21::List<int> s21_list_int;
  s21::List<double> s21_list_double;
  s21::List<std::string> s21_list_string;

  EXPECT_EQ(s21_list_int.size(), 0U);
  EXPECT_EQ(s21_list_double.size(), 0U);
  EXPECT_EQ(s21_list_string.size(), 0U);
}

TEST(List_test, case2) {
  s21::List<int> s21_list_int(5);
  s21::List<double> s21_list_double(5);

  EXPECT_EQ(s21_list_int.size(), 5U);
  EXPECT_EQ(s21_list_double.size(), 5U);
}

TEST(List_test, case3) {
  EXPECT_THROW(s21::List<int> s21_list_int(0), std::out_of_range);
  EXPECT_THROW(s21::List<double> s21_list_double(0), std::out_of_range);
}

TEST(List_test, case4) {
  s21::List<int> s21_list_int{1, 45, 8, 97};
  s21::List<double> s21_list_double{1.4, 4.854, 8.95, 9.1};
  s21::List<std::string> s21_list_string{"Hello", ",", "s21", "!"};

  EXPECT_EQ(s21_list_int.size(), 4U);
  EXPECT_EQ(s21_list_int.front(), 1);

  EXPECT_EQ(s21_list_double.size(), 4U);
  EXPECT_EQ(s21_list_double.front(), 1.4);

  EXPECT_EQ(s21_list_string.size(), 4U);
  EXPECT_EQ(s21_list_string.front(), "Hello");
}

TEST(List_test, case5) {
  s21::List<int> s21_list_ref_int{1, 45, 8, 97};
  s21::List<int> s21_list_res_int(s21_list_ref_int);

  s21::List<double> s21_list_ref_double{1.4, 4.854, 8.95, 9.1};
  s21::List<double> s21_list_res_double(s21_list_ref_double);

  s21::List<std::string> s21_list_ref_string{"Hello", ",", "s21", "!"};
  s21::List<std::string> s21_list_res_string(s21_list_ref_string);

  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(List_test, case6) {
  s21::List<int> s21_list_ref_int;
  s21::List<int> s21_list_res_int = s21_list_ref_int;

  s21::List<double> s21_list_ref_double;
  s21::List<double> s21_list_res_double = s21_list_ref_double;

  s21::List<std::string> s21_list_ref_string;
  s21::List<std::string> s21_list_res_string = s21_list_ref_string;

  EXPECT_EQ(s21_list_res_int.size(), 0U);
  EXPECT_EQ(s21_list_res_double.size(), 0U);
  EXPECT_EQ(s21_list_res_string.size(), 0U);
}

TEST(List_test, case7) {
  s21::List<int> s21_list_ref_int{1, 45, 8, 97};
  s21::List<int> s21_list_res_int = std::move(s21_list_ref_int);

  s21::List<double> s21_list_ref_double{1.4, 4.854, 8.95, 9.1};
  s21::List<double> s21_list_res_double = std::move(s21_list_ref_double);

  s21::List<std::string> s21_list_ref_string{"Hello", ",", "s21", "!"};
  s21::List<std::string> s21_list_res_string = std::move(s21_list_ref_string);

  EXPECT_EQ(s21_list_ref_int.size(), 0U);
  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_ref_double.size(), 0U);
  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_ref_string.size(), 0U);
  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(List_test, case8) {
  s21::List<int> s21_list_ref_int{1, 45, 8, 97};
  s21::List<int> s21_list_res_int;
  s21_list_res_int = std::move(s21_list_ref_int);

  s21::List<double> s21_list_ref_double{1.4, 4.854, 8.95, 9.1};
  s21::List<double> s21_list_res_double;
  s21_list_res_double = std::move(s21_list_ref_double);

  s21::List<std::string> s21_list_ref_string{"Hello", ",", "s21", "!"};
  s21::List<std::string> s21_list_res_string;
  s21_list_res_string = std::move(s21_list_ref_string);

  EXPECT_EQ(s21_list_ref_int.size(), 0U);
  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_ref_double.size(), 0U);
  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_ref_string.size(), 0U);
  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(List_test, case9) {
  s21::List<int> a = {43, 43, 43, 5};
  s21::List<int> b = {1};
  a = std::move(b);
  EXPECT_EQ(a.back(), 1);
}

TEST(List_test, case10) {
  size_t n = 1e4;
  s21::List<int> lst(n);
  EXPECT_EQ(lst.size(), n);
  EXPECT_TRUE(lst.max_size() != 0);
  lst.pop_back();
  lst.pop_front();
  EXPECT_EQ(lst.size(), (n - 2));
  int back = lst.back();
  int front = lst.front();
  EXPECT_EQ(back, 0);
  EXPECT_EQ(front, 0);
}

TEST(List_test, case11) {
  s21::List<double> my = {1.032, 2.320,    3.0,   4.0,   5.0,
                          6.0,   7.000043, 8.324, 9.343, 10.0};
  EXPECT_EQ(my.size(), 10U);
  double front = my.front();
  EXPECT_DOUBLE_EQ(front, 1.032);
  my.pop_front();
  double new_front = my.front();
  EXPECT_DOUBLE_EQ(new_front, 2.320);
  my.pop_back();
  double back = my.back();
  EXPECT_DOUBLE_EQ(back, 9.343);
  EXPECT_EQ(my.size(), 8U);
  my.clear();
  EXPECT_EQ(my.size(), 0U);
}

TEST(List_test, case12) {
  s21::List<double> my = {1.032, 2.32,     3.0,   4.0,   5.0,
                          6.0,   7.000043, 8.324, 9.343, 10.0};
  s21::List<double> my_cpy(my);
  EXPECT_EQ(my_cpy.size(), 10U);
  double front = my_cpy.front();
  EXPECT_DOUBLE_EQ(front, 1.032);
  my_cpy.pop_front();
  double new_front = my_cpy.front();
  EXPECT_DOUBLE_EQ(new_front, 2.320);
  double back = my_cpy.back();
  EXPECT_DOUBLE_EQ(back, 10.0);
  my_cpy.pop_back();
  back = my_cpy.back();
  EXPECT_DOUBLE_EQ(back, 9.343);
  EXPECT_EQ(my_cpy.size(), 8U);
}

TEST(List_test, case13) {
  s21::List<int> s21_list_int{1, 45, 8, 97};
  s21::List<double> s21_list_double{1.4, 4.854, 8.95, 9.1};
  s21::List<std::string> s21_list_string{"Hello", ",", "s21", "!"};

  s21_list_int.push_front(21);
  s21_list_double.push_front(21.0);
  s21_list_string.push_front("21");

  EXPECT_EQ(s21_list_int.size(), 5U);
  EXPECT_EQ(s21_list_int.front(), 21);

  EXPECT_EQ(s21_list_double.size(), 5U);
  EXPECT_EQ(s21_list_double.front(), 21.0);

  EXPECT_EQ(s21_list_string.size(), 5U);
  EXPECT_EQ(s21_list_string.front(), "21");
}

TEST(List_test, case14) {
  s21::List<int> s21_list_int;
  s21::List<double> s21_list_double;
  s21::List<std::string> s21_list_string;

  s21_list_int.push_front(33);
  s21_list_double.push_front(33.0);
  s21_list_string.push_front("33");

  EXPECT_EQ(s21_list_int.size(), 1U);
  EXPECT_EQ(s21_list_int.front(), 33);

  EXPECT_EQ(s21_list_double.size(), 1U);
  EXPECT_EQ(s21_list_double.front(), 33.0);

  EXPECT_EQ(s21_list_string.size(), 1U);
  EXPECT_EQ(s21_list_string.front(), "33");
}

TEST(List_test, case15) {
  s21::List<int> my = {1, 2, 10, 3, 4, 6, 43};
  std::list<int> orig = {1, 2, 10, 3, 4, 6, 43};
  my.push_front(21);
  orig.push_front(21);
  auto itr_orig = orig.begin();
  for (auto itr = my.begin(); itr != my.end(); itr++) {
    EXPECT_EQ(*itr, *itr_orig);
    itr_orig++;
  }

  s21::List<int> my1;
  std::list<int> orig1;
  my1.push_front(21);
  orig1.push_front(21);
  auto itr_orig1 = orig1.begin();
  for (auto itr1 = my1.begin(); itr1 != my1.end(); itr1++) {
    EXPECT_EQ(*itr1, *itr_orig1);
    itr_orig1++;
  }
}

TEST(List_test, case16) {
  s21::List<int> s21_list_int{1, 4, 8, 9};
  s21::List<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::List<std::string> s21_list_string{"Hello", ",", "world", "!"};

  s21_list_int.pop_front();
  s21_list_double.pop_front();
  s21_list_string.pop_front();

  EXPECT_EQ(s21_list_int.size(), 3U);
  EXPECT_EQ(s21_list_int.front(), 4);

  EXPECT_EQ(s21_list_double.size(), 3U);
  EXPECT_EQ(s21_list_double.front(), 4.8);

  EXPECT_EQ(s21_list_string.size(), 3U);
  EXPECT_EQ(s21_list_string.front(), ",");
}

TEST(List_test, case17) {
  s21::List<int> s21_list_int{1};
  s21::List<double> s21_list_double{1.0};
  s21::List<std::string> s21_list_string{"1"};

  s21_list_int.pop_front();
  s21_list_double.pop_front();
  s21_list_string.pop_front();

  EXPECT_EQ(s21_list_int.size(), 0U);
  EXPECT_EQ(s21_list_double.size(), 0U);
  EXPECT_EQ(s21_list_string.size(), 0U);
}

TEST(List_test, case18) {
  s21::List<int> my = {1, 2, 10, 3, 4, 6, 43};
  std::list<int> orig = {1, 2, 10, 3, 4, 6, 43};
  my.pop_front();
  orig.pop_front();
  auto itr_orig = orig.begin();
  for (auto itr = my.begin(); itr != my.end(); itr++) {
    EXPECT_EQ(*itr, *itr_orig);
    itr_orig++;
  }
}

TEST(List_test, case19) {
  s21::List<int> s21_list_int{1, 4, -8, 9};
  s21::List<double> s21_list_double{1.4, 4.8, -8.9, 9.1};
  s21::List<std::string> s21_list_string{"Hello", ",", "s21", "!"};

  s21_list_int.pop_back();
  s21_list_double.pop_back();
  s21_list_string.pop_back();

  EXPECT_EQ(s21_list_int.size(), 3U);
  EXPECT_EQ(s21_list_int.back(), -8);

  EXPECT_EQ(s21_list_double.size(), 3U);
  EXPECT_EQ(s21_list_double.back(), -8.9);

  EXPECT_EQ(s21_list_string.size(), 3U);
  EXPECT_EQ(s21_list_string.back(), "s21");
}

TEST(List_test, case20) {
  s21::List<int> s21_list_int{-1, 4, 8, 9};
  s21::List<double> s21_list_double{-1.4, 4.8, 8.9, 9.1};
  s21::List<std::string> s21_list_string{"Hello", ",", "s21", "!"};

  EXPECT_EQ(s21_list_int.front(), -1);
  EXPECT_EQ(s21_list_double.front(), -1.4);
  EXPECT_EQ(s21_list_string.front(), "Hello");
}

TEST(List_test, case21) {
  s21::List<char> my = {'l', 'i', 's', 't'};
  std::list<char> orig = {'l', 'i', 's', 't'};
  EXPECT_EQ(my.front(), orig.front());
}

TEST(List_test, case22) {
  s21::List<int> s21_list_int{1, 4, 8, 9};
  s21::List<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::List<std::string> s21_list_string{"Hello", ",", "s21", "!"};

  EXPECT_EQ(s21_list_int.back(), 9);
  EXPECT_EQ(s21_list_double.back(), 9.1);
  EXPECT_EQ(s21_list_string.back(), "!");
}

TEST(List_test, case23) {
  s21::List<int> s21_list_ref_int{1, 4, 8, 9};
  s21::List<int> s21_list_res_int{12, 13};

  s21::List<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::List<double> s21_list_res_double{11.0, 12.0, 13.0};

  s21::List<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::List<std::string> s21_list_res_string{"12", "13", "14", "15"};

  s21_list_ref_int.swap(s21_list_res_int);
  s21_list_ref_double.swap(s21_list_res_double);
  s21_list_ref_string.swap(s21_list_res_string);

  EXPECT_EQ(s21_list_ref_int.size(), 2U);
  EXPECT_EQ(s21_list_ref_int.front(), 12);
  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_ref_double.size(), 3U);
  EXPECT_EQ(s21_list_ref_double.front(), 11.0);
  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_ref_string.size(), 4U);
  EXPECT_EQ(s21_list_ref_string.front(), "12");
  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(List_test, case24) {
  s21::List<int> s21_list_int{8, 1, 4, 9};
  s21::List<double> s21_list_double{9.1, 1.4, 4.8, 8.9};
  s21::List<std::string> s21_list_string{"hello", "world", "21", "school"};

  s21_list_int.sort();
  s21_list_double.sort();
  s21_list_string.sort();

  EXPECT_EQ(s21_list_int.front(), 1);
  EXPECT_EQ(s21_list_double.front(), 1.4);
  EXPECT_EQ(s21_list_string.front(), "21");
}

TEST(List_test, case25) {
  s21::List<int> s21_list_int{8};
  s21::List<double> s21_list_double{9.1};
  s21::List<std::string> s21_list_string{"hello"};

  s21_list_int.sort();
  s21_list_double.sort();
  s21_list_string.sort();

  EXPECT_EQ(s21_list_int.front(), 8);
  EXPECT_EQ(s21_list_double.front(), 9.1);
  EXPECT_EQ(s21_list_string.front(), "hello");
}

TEST(List_test, case26) {
  s21::List<int> s21_list_ref_int{1, 4, 8, 9};
  s21::List<int> s21_list_res_int{12, 13};

  s21::List<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::List<double> s21_list_res_double{11.0, 12.0, 13.0};

  s21::List<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::List<std::string> s21_list_res_string{"12", "13", "14", "15"};

  s21_list_res_int.merge(s21_list_ref_int);
  s21_list_res_double.merge(s21_list_ref_double);
  s21_list_res_string.merge(s21_list_ref_string);

  EXPECT_EQ(s21_list_res_int.size(), 6U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_res_double.size(), 7U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_res_string.size(), 8U);
  EXPECT_EQ(s21_list_res_string.front(), "12");
}

TEST(List_test, case27) {
  s21::List<int> my = {1, 2, 10, 3, 4, 6, 43};
  std::list<int> orig = {1, 2, 10, 3, 4, 6, 43};
  s21::List<int> list_merge = {2, 5, 7, 9};
  std::list<int> list_merge_orig = {2, 5, 7, 9};
  my.sort();
  orig.sort();
  my.merge(list_merge);
  orig.merge(list_merge_orig);
  auto itr_orig = orig.begin();
  for (auto itr = my.begin(); itr != my.end(); itr++) {
    EXPECT_EQ(*itr, *itr_orig);
    itr_orig++;
  }
}

TEST(List_test, case28) {
  s21::List<int> s21_list_int{1, 4, 8, 9};
  s21::List<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::List<std::string> s21_list_string{"Hello", ",", "world", "!"};

  s21_list_int.reverse();
  s21_list_double.reverse();
  s21_list_string.reverse();

  EXPECT_EQ(s21_list_int.front(), 9);
  EXPECT_EQ(s21_list_double.front(), 9.1);
  EXPECT_EQ(s21_list_string.front(), "!");
}

TEST(List_test, case29) {
  s21::List<int> s21_list_int{1};
  s21::List<double> s21_list_double{1.4};
  s21::List<std::string> s21_list_string{"Hello"};

  s21_list_int.reverse();
  s21_list_double.reverse();
  s21_list_string.reverse();

  EXPECT_EQ(s21_list_int.front(), 1);
  EXPECT_EQ(s21_list_double.front(), 1.4);
  EXPECT_EQ(s21_list_string.front(), "Hello");
}

TEST(List_test, case30) {
  s21::List<int> s21_list_int{1, 1, 4, 4, 8, 8, 8, 9, 9, 9, 9, 9};
  s21::List<double> s21_list_double{1.4, 4.8, 1.4, 4.8, 8.9, 9.1,
                                    1.4, 4.8, 8.9, 8.9, 9.1};
  s21::List<std::string> s21_list_string{"Hello", ",",     "Hello", ",",
                                         "world", ",",     "world", "!",
                                         "!",     "world", "!"};

  s21_list_int.unique();
  s21_list_double.unique();
  s21_list_string.unique();

  EXPECT_EQ(s21_list_int.size(), 4U);
  EXPECT_EQ(s21_list_double.size(), 10U);
  EXPECT_EQ(s21_list_string.size(), 10U);
}

TEST(List_test, case31) {
  s21::List<int> s21_list_int{1, 4, 8, 9};
  s21::List<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::List<std::string> s21_list_string{"Hello", ",", "s21", "!"};

  s21_list_int.unique();
  s21_list_double.unique();
  s21_list_string.unique();

  EXPECT_EQ(s21_list_int.size(), 4U);
  EXPECT_EQ(s21_list_double.size(), 4U);
  EXPECT_EQ(s21_list_string.size(), 4U);
}

TEST(List_test, case32) {
  s21::List<int> s21_list_int;
  s21::List<double> s21_list_double;
  s21::List<std::string> s21_list_string;

  s21_list_int.unique();
  s21_list_double.unique();
  s21_list_string.unique();

  EXPECT_EQ(s21_list_int.size(), 0U);
  EXPECT_EQ(s21_list_double.size(), 0U);
  EXPECT_EQ(s21_list_string.size(), 0U);
}

TEST(List_test, case34) {
  s21::List<int> s21_list_int{1, 4, 8, 9};
  s21::List<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::List<std::string> s21_list_string{"Hello", ",", "s21", "!"};

  EXPECT_EQ(s21_list_int.empty(), 0);
  EXPECT_EQ(s21_list_double.empty(), 0);
  EXPECT_EQ(s21_list_string.empty(), 0);
}

TEST(List_test, case35) {
  s21::List<int> s21_list_int;
  s21::List<double> s21_list_double;
  s21::List<std::string> s21_list_string;

  auto it_int = s21_list_int.begin();
  it_int = s21_list_int.insert(it_int, 13);
  EXPECT_EQ(s21_list_int.front(), 13);

  auto it_double = s21_list_double.begin();
  it_double = s21_list_double.insert(it_double, 21.0);
  EXPECT_EQ(s21_list_double.front(), 21.0);

  auto it_string = s21_list_string.begin();
  it_string = s21_list_string.insert(it_string, "HI");
  EXPECT_EQ(s21_list_string.front(), "HI");
}

TEST(List_test, case36) {
  s21::List<int> s21_list_int{1};
  s21::List<double> s21_list_double{1.0};
  s21::List<std::string> s21_list_string{"1"};

  auto it_int = s21_list_int.begin();
  it_int = s21_list_int.insert(it_int, 13);
  EXPECT_EQ(s21_list_int.front(), 13);

  auto it_double = s21_list_double.begin();
  it_double = s21_list_double.insert(it_double, 21.0);
  EXPECT_EQ(s21_list_double.front(), 21.0);

  auto it_string = s21_list_string.begin();
  it_string = s21_list_string.insert(it_string, "HI");
  EXPECT_EQ(s21_list_string.front(), "HI");
}

TEST(List_test, case37) {
  s21::List<int> my;
  std::list<int> orig;
  auto itr = my.begin();
  auto itr_orig = orig.begin();
  itr = my.insert(itr, 21);
  itr_orig = orig.insert(itr_orig, 21);
  EXPECT_EQ(*itr, *itr_orig);

  s21::List<int> my1 = {1, 2, 3, 4, 6, 43};
  std::list<int> orig1 = {1, 2, 3, 4, 6, 43};
  auto itr1 = my1.begin();
  auto itr_orig1 = orig1.begin();
  itr1 = my1.insert(itr1, 21);
  itr_orig1 = orig1.insert(itr_orig1, 21);
  auto end1 = my1.end();
  auto end_orig1 = orig1.end();
  while (itr1 != end1 && itr_orig1 != end_orig1) {
    EXPECT_EQ(*itr1, *itr_orig1);
    itr1++;
    itr_orig1++;
  }

  s21::List<int> my2 = {1, 2, 3, 4, 6, 44};
  std::list<int> orig2 = {1, 2, 3, 4, 6, 44};
  auto itr2 = my2.end();
  auto itr_orig2 = orig2.end();
  itr2 = my2.insert(itr2, 21);
  itr_orig2 = orig2.insert(itr_orig2, 21);
  while (itr2 != my2.begin() && itr_orig2 != orig2.begin()) {
    EXPECT_EQ(*itr2, *itr_orig2);
    itr2--;
    itr_orig2--;
  }
}

TEST(List_test, case38) {
  s21::List<int> s21_list_ref_int{2};
  s21::List<int> s21_list_res_int{1, 4, 8, 9};

  s21::List<double> s21_list_ref_double{2.3};
  s21::List<double> s21_list_res_double{1.4, 4.8, 8.9, 9.1};

  s21::List<std::string> s21_list_ref_string{"s22"};
  s21::List<std::string> s21_list_res_string{"Hello", ",", "s21", "!"};

  auto it_int = s21_list_res_int.begin();
  s21_list_res_int.splice(it_int, s21_list_ref_int);
  EXPECT_EQ(*(s21_list_res_int.begin()), 2);

  auto it_double = s21_list_res_double.begin();
  s21_list_res_double.splice(it_double, s21_list_ref_double);
  EXPECT_EQ(*(s21_list_res_double.begin()), 2.3);

  auto it_string = s21_list_res_string.begin();
  s21_list_res_string.splice(it_string, s21_list_ref_string);
  EXPECT_EQ(*(s21_list_res_string.begin()), "s22");
}

TEST(List_test, case39) {
  s21::List<int> my = {1, 2, 7, 8, 9};
  my.insert_many_back(4, 5, 6);
  EXPECT_EQ(my.back(), 6);
}

TEST(List_test, case40) {
  s21::List<int> my;
  my.insert_many_back(4, 5, 6);
  EXPECT_EQ(my.back(), 6);
  EXPECT_EQ(my.front(), 4);
}

TEST(List_test, case41) {
  s21::List<int> my = {1, 2, 7, 8, 9};
  my.insert_many_front(4, 5, 6);
  EXPECT_EQ(my.front(), 6);
}

TEST(List_test, case42) {
  s21::List<int> my;
  my.insert_many_front(4, 5, 6);
  EXPECT_EQ(my.front(), 6);
  EXPECT_EQ(my.back(), 4);
}

TEST(List_test, case43) {
  s21::List<int> my = {1, 2, 3, 4, 6, 43};
  std::list<int> orig = {1, 2, 3, 4, 6, 43};
  unsigned int n = my.size();
  unsigned int n_orig = orig.size();
  EXPECT_EQ(n, n_orig);
  auto itr = my.begin();
  auto itr_orig = orig.begin();
  auto end = my.end();
  auto end_orig = orig.end();
  while (itr != end && itr_orig != end_orig) {
    EXPECT_EQ(*itr, *itr_orig);
    itr++;
    itr_orig++;
  }
}
