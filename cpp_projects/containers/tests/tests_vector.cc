#include <vector>

#include "test_main.h"

TEST(vector, case1) {
  s21::vector<int> s21_vec_int;
  s21::vector<double> s21_vec_double;
  s21::vector<std::string> s21_vec_string;

  EXPECT_EQ(s21_vec_int.size(), 0U);
  EXPECT_EQ(s21_vec_int.capacity(), 0U);
  EXPECT_EQ(&s21_vec_int[0], nullptr);

  EXPECT_EQ(s21_vec_double.size(), 0U);
  EXPECT_EQ(s21_vec_double.capacity(), 0U);
  EXPECT_EQ(&s21_vec_double[0], nullptr);

  EXPECT_EQ(s21_vec_string.size(), 0U);
  EXPECT_EQ(s21_vec_string.capacity(), 0U);
  EXPECT_EQ(&s21_vec_string[0], nullptr);
}

TEST(vector, case2) {
  s21::vector<int> s21_vec_int(5);
  s21::vector<double> s21_vec_double(5);
  s21::vector<std::string> s21_vec_string(5);

  EXPECT_EQ(s21_vec_int.size(), 5U);
  EXPECT_EQ(s21_vec_int.capacity(), 5U);
  EXPECT_NE(&s21_vec_int[0], nullptr);

  EXPECT_EQ(s21_vec_double.size(), 5U);
  EXPECT_EQ(s21_vec_double.capacity(), 5U);
  EXPECT_NE(&s21_vec_double[0], nullptr);

  EXPECT_EQ(s21_vec_string.size(), 5U);
  EXPECT_EQ(s21_vec_string.capacity(), 5U);
  EXPECT_NE(&s21_vec_string[0], nullptr);
}

TEST(vector, case3) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.size(), 4U);
  EXPECT_EQ(s21_vec_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_int[0], 1);
  EXPECT_EQ(s21_vec_int[1], 4);
  EXPECT_EQ(s21_vec_int[2], 8);
  EXPECT_EQ(s21_vec_int[3], 9);

  EXPECT_EQ(s21_vec_double.size(), 4U);
  EXPECT_EQ(s21_vec_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_double[0], 1.4);
  EXPECT_EQ(s21_vec_double[1], 4.8);
  EXPECT_EQ(s21_vec_double[2], 8.9);
  EXPECT_EQ(s21_vec_double[3], 9.1);

  EXPECT_EQ(s21_vec_string.size(), 4U);
  EXPECT_EQ(s21_vec_string.capacity(), 4U);
  EXPECT_EQ(s21_vec_string[0], "Hello");
  EXPECT_EQ(s21_vec_string[1], ",");
  EXPECT_EQ(s21_vec_string[2], "world");
  EXPECT_EQ(s21_vec_string[3], "!");
}

TEST(vector, case4) {
  s21::vector<int> s21_vec_ref_int{1, 4, 8, 9};
  s21::vector<int> s21_vec_res_int(s21_vec_ref_int);

  s21::vector<double> s21_vec_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<double> s21_vec_res_double(s21_vec_ref_double);

  s21::vector<std::string> s21_vec_ref_string{"Hello", ",", "world", "!"};
  s21::vector<std::string> s21_vec_res_string(s21_vec_ref_string);

  EXPECT_EQ(s21_vec_ref_int.size(), s21_vec_res_int.size());
  EXPECT_EQ(s21_vec_ref_int.capacity(), s21_vec_res_int.capacity());
  EXPECT_EQ(s21_vec_ref_int[0], s21_vec_res_int[0]);
  EXPECT_EQ(s21_vec_ref_int[1], s21_vec_res_int[1]);
  EXPECT_EQ(s21_vec_ref_int[2], s21_vec_res_int[2]);
  EXPECT_EQ(s21_vec_ref_int[3], s21_vec_res_int[3]);

  EXPECT_EQ(s21_vec_ref_double.size(), s21_vec_res_double.size());
  EXPECT_EQ(s21_vec_ref_double.capacity(), s21_vec_res_double.capacity());
  EXPECT_EQ(s21_vec_ref_double[0], s21_vec_res_double[0]);
  EXPECT_EQ(s21_vec_ref_double[1], s21_vec_res_double[1]);
  EXPECT_EQ(s21_vec_ref_double[2], s21_vec_res_double[2]);
  EXPECT_EQ(s21_vec_ref_double[3], s21_vec_res_double[3]);

  EXPECT_EQ(s21_vec_ref_string.size(), s21_vec_res_string.size());
  EXPECT_EQ(s21_vec_ref_string.capacity(), s21_vec_res_string.capacity());
  EXPECT_EQ(s21_vec_ref_string[0], s21_vec_res_string[0]);
  EXPECT_EQ(s21_vec_ref_string[1], s21_vec_res_string[1]);
  EXPECT_EQ(s21_vec_ref_string[2], s21_vec_res_string[2]);
  EXPECT_EQ(s21_vec_ref_string[3], s21_vec_res_string[3]);
}

TEST(vector, case5) {
  s21::vector<int> s21_vec_ref_int{1, 4, 8, 9};
  s21::vector<int> s21_vec_res_int = std::move(s21_vec_ref_int);
  s21::vector<double> s21_vec_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<double> s21_vec_res_double = std::move(s21_vec_ref_double);
  s21::vector<std::string> s21_vec_ref_string{"Hello", ",", "world", "!"};
  s21::vector<std::string> s21_vec_res_string = std::move(s21_vec_ref_string);

  EXPECT_EQ(s21_vec_ref_int.size(), 0U);
  EXPECT_EQ(s21_vec_ref_int.capacity(), 0U);
  EXPECT_EQ(s21_vec_res_int.size(), 4U);
  EXPECT_EQ(s21_vec_res_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_int[0], 1);
  EXPECT_EQ(s21_vec_res_int[1], 4);
  EXPECT_EQ(s21_vec_res_int[2], 8);
  EXPECT_EQ(s21_vec_res_int[3], 9);

  EXPECT_EQ(s21_vec_ref_double.size(), 0U);
  EXPECT_EQ(s21_vec_ref_double.capacity(), 0U);
  EXPECT_EQ(s21_vec_res_double.size(), 4U);
  EXPECT_EQ(s21_vec_res_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_double[0], 1.4);
  EXPECT_EQ(s21_vec_res_double[1], 4.8);
  EXPECT_EQ(s21_vec_res_double[2], 8.9);
  EXPECT_EQ(s21_vec_res_double[3], 9.1);

  EXPECT_EQ(s21_vec_ref_string.size(), 0U);
  EXPECT_EQ(s21_vec_ref_string.capacity(), 0U);
  EXPECT_EQ(s21_vec_res_string.size(), 4U);
  EXPECT_EQ(s21_vec_res_string.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_string[0], "Hello");
  EXPECT_EQ(s21_vec_res_string[1], ",");
  EXPECT_EQ(s21_vec_res_string[2], "world");
  EXPECT_EQ(s21_vec_res_string[3], "!");
}

TEST(vector, case6) {
  s21::vector<int> s21_vec_ref_int{1, 4, 8, 9};
  s21::vector<int> s21_vec_res_int;
  s21_vec_res_int = std::move(s21_vec_ref_int);

  s21::vector<double> s21_vec_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<double> s21_vec_res_double;
  s21_vec_res_double = std::move(s21_vec_ref_double);

  s21::vector<std::string> s21_vec_ref_string{"Hello", ",", "world", "!"};
  s21::vector<std::string> s21_vec_res_string;
  s21_vec_res_string = std::move(s21_vec_ref_string);

  EXPECT_EQ(s21_vec_ref_int.size(), 0U);
  EXPECT_EQ(s21_vec_ref_int.capacity(), 0U);
  EXPECT_EQ(s21_vec_res_int.size(), 4U);
  EXPECT_EQ(s21_vec_res_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_int[0], 1);
  EXPECT_EQ(s21_vec_res_int[1], 4);
  EXPECT_EQ(s21_vec_res_int[2], 8);
  EXPECT_EQ(s21_vec_res_int[3], 9);

  EXPECT_EQ(s21_vec_ref_double.size(), 0U);
  EXPECT_EQ(s21_vec_ref_double.capacity(), 0U);
  EXPECT_EQ(s21_vec_res_double.size(), 4U);
  EXPECT_EQ(s21_vec_res_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_double[0], 1.4);
  EXPECT_EQ(s21_vec_res_double[1], 4.8);
  EXPECT_EQ(s21_vec_res_double[2], 8.9);
  EXPECT_EQ(s21_vec_res_double[3], 9.1);

  EXPECT_EQ(s21_vec_ref_string.size(), 0U);
  EXPECT_EQ(s21_vec_ref_string.capacity(), 0U);
  EXPECT_EQ(s21_vec_res_string.size(), 4U);
  EXPECT_EQ(s21_vec_res_string.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_string[0], "Hello");
  EXPECT_EQ(s21_vec_res_string[1], ",");
  EXPECT_EQ(s21_vec_res_string[2], "world");
  EXPECT_EQ(s21_vec_res_string[3], "!");
}

TEST(vector, case7) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.at(0), 1);
  EXPECT_EQ(s21_vec_double.at(0), 1.4);
  EXPECT_EQ(s21_vec_string.at(0), "Hello");
}

TEST(vector, case8) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_THROW(s21_vec_int.at(5), std::out_of_range);
  EXPECT_THROW(s21_vec_double.at(5), std::out_of_range);
  EXPECT_THROW(s21_vec_string.at(5), std::out_of_range);
}

TEST(vector, case9) {
  s21::vector<int> s21_vec_int;
  s21::vector<double> s21_vec_double;
  s21::vector<std::string> s21_vec_string;

  EXPECT_THROW(s21_vec_int.at(5), std::out_of_range);
  EXPECT_THROW(s21_vec_double.at(5), std::out_of_range);
  EXPECT_THROW(s21_vec_string.at(5), std::out_of_range);
}

TEST(vector, case10) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int[3], 9);
  EXPECT_EQ(s21_vec_double[0], 1.4);
  EXPECT_EQ(s21_vec_string[0], "Hello");
}

TEST(vector, case11) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.front(), 1);
  EXPECT_EQ(s21_vec_double.front(), 1.4);
  EXPECT_EQ(s21_vec_string.front(), "Hello");
}

TEST(vector, case12) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.back(), 9);
  EXPECT_EQ(s21_vec_double.back(), 9.1);
  EXPECT_EQ(s21_vec_string.back(), "!");
}

TEST(vector, case13) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.data(), &s21_vec_int[0]);
  EXPECT_EQ(s21_vec_double.data(), &s21_vec_double[0]);
  EXPECT_EQ(s21_vec_string.data(), &s21_vec_string[0]);
}

TEST(vector, case14) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.begin(), &s21_vec_int[0]);
  EXPECT_EQ(s21_vec_double.begin(), &s21_vec_double[0]);
  EXPECT_EQ(s21_vec_string.begin(), &s21_vec_string[0]);
}

TEST(vector, case15) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.end(), &s21_vec_int[0] + 4);
  EXPECT_EQ(s21_vec_double.end(), &s21_vec_double[0] + 4);
  EXPECT_EQ(s21_vec_string.end(), &s21_vec_string[0] + 4);
}

TEST(vector, case16) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.empty(), 0);
  EXPECT_EQ(s21_vec_double.empty(), 0);
  EXPECT_EQ(s21_vec_string.empty(), 0);
}

TEST(vector, case17) {
  s21::vector<int> s21_vec_int{};
  s21::vector<double> s21_vec_double{};
  s21::vector<std::string> s21_vec_string{};

  EXPECT_EQ(s21_vec_int.empty(), 1);
  EXPECT_EQ(s21_vec_double.empty(), 1);
  EXPECT_EQ(s21_vec_string.empty(), 1);
}

TEST(vector, case18) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.size(), 4U);
  EXPECT_EQ(s21_vec_double.size(), 4U);
  EXPECT_EQ(s21_vec_string.size(), 4U);
}

TEST(vector, case19) {
  s21::vector<int> s21_vec_int{};
  s21::vector<double> s21_vec_double{};
  s21::vector<std::string> s21_vec_string{};

  EXPECT_EQ(s21_vec_int.size(), 0U);
  EXPECT_EQ(s21_vec_double.size(), 0U);
  EXPECT_EQ(s21_vec_string.size(), 0U);
}

TEST(vector, case21) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.reserve(20);
  s21_vec_double.reserve(20);
  s21_vec_string.reserve(20);

  EXPECT_EQ(s21_vec_int.capacity(), 20U);
  EXPECT_EQ(s21_vec_double.capacity(), 20U);
  EXPECT_EQ(s21_vec_string.capacity(), 20U);
}

TEST(vector, case22) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.reserve(2);
  s21_vec_double.reserve(2);
  s21_vec_string.reserve(2);

  EXPECT_EQ(s21_vec_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_string.capacity(), 4U);
}

TEST(vector, case23) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_string.capacity(), 4U);
}

TEST(vector, case24) {
  s21::vector<int> s21_vec_int{};
  s21::vector<double> s21_vec_double{};
  s21::vector<std::string> s21_vec_string{};

  EXPECT_EQ(s21_vec_int.capacity(), 0U);
  EXPECT_EQ(s21_vec_double.capacity(), 0U);
  EXPECT_EQ(s21_vec_string.capacity(), 0U);
}

TEST(vector, case25) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.reserve(20);
  s21_vec_double.reserve(20);
  s21_vec_string.reserve(20);

  s21_vec_int.shrink_to_fit();
  s21_vec_double.shrink_to_fit();
  s21_vec_string.shrink_to_fit();

  EXPECT_EQ(s21_vec_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_string.capacity(), 4U);
}

TEST(vector, case26) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.shrink_to_fit();
  s21_vec_double.shrink_to_fit();
  s21_vec_string.shrink_to_fit();

  EXPECT_EQ(s21_vec_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_string.capacity(), 4U);
}

TEST(vector, case27) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.clear();
  s21_vec_double.clear();
  s21_vec_string.clear();

  EXPECT_EQ(&s21_vec_int[0], nullptr);
  EXPECT_EQ(&s21_vec_double[0], nullptr);
  EXPECT_EQ(&s21_vec_string[0], nullptr);
}

TEST(vector, case28) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.clear();
  s21_vec_double.clear();
  s21_vec_string.clear();

  EXPECT_EQ(&s21_vec_int[0], nullptr);
  EXPECT_EQ(&s21_vec_double[0], nullptr);
  EXPECT_EQ(&s21_vec_string[0], nullptr);
}

TEST(vector, case29) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "", "!"};

  auto pos_int = s21_vec_int.begin() + 2;
  auto pos_double = s21_vec_double.begin() + 2;
  auto pos_string = s21_vec_string.begin() + 2;

  s21_vec_int.insert(pos_int, 2);
  s21_vec_double.insert(pos_double, 2.0);
  s21_vec_string.insert(pos_string, "world");

  EXPECT_EQ(s21_vec_int[2], 2);
  EXPECT_EQ(s21_vec_double[2], 2.0);
  EXPECT_EQ(s21_vec_string[2], "world");
}

TEST(vector, case30) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "", "!"};

  auto pos_int = s21_vec_int.begin();
  auto pos_double = s21_vec_double.begin();
  auto pos_string = s21_vec_string.begin();

  s21_vec_int.insert(pos_int, 2);
  s21_vec_double.insert(pos_double, 2.0);
  s21_vec_string.insert(pos_string, "world");

  EXPECT_EQ(s21_vec_int[0], 2);
  EXPECT_EQ(s21_vec_double[0], 2.0);
  EXPECT_EQ(s21_vec_string[0], "world");
}

TEST(vector, case31) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "", "!"};

  auto pos_int = s21_vec_int.end();
  auto pos_double = s21_vec_double.end();
  auto pos_string = s21_vec_string.end();

  s21_vec_int.insert(pos_int, 2);
  s21_vec_double.insert(pos_double, 2.0);
  s21_vec_string.insert(pos_string, "world");

  EXPECT_EQ(s21_vec_int[4], 2);
  EXPECT_EQ(s21_vec_double[4], 2.0);
  EXPECT_EQ(s21_vec_string[4], "world");
}

TEST(vector, case32) {
  s21::vector<int> s21_vec_int{1, 4, 1, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 1.0, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "", "world", "!"};

  auto pos_int = s21_vec_int.begin() + 2;
  auto pos_double = s21_vec_double.begin() + 2;
  auto pos_string = s21_vec_string.begin() + 2;

  s21_vec_int.erase(pos_int);
  s21_vec_double.erase(pos_double);
  s21_vec_string.erase(pos_string);

  EXPECT_EQ(s21_vec_int[2], 8);
  EXPECT_EQ(s21_vec_double[2], 8.9);
  EXPECT_EQ(s21_vec_string[2], "world");
}

TEST(vector, case33) {
  s21::vector<int> s21_vec_int{1, 1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.0, 1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"", "Hello", ",", "world", "!"};

  auto pos_int = s21_vec_int.begin();
  auto pos_double = s21_vec_double.begin();
  auto pos_string = s21_vec_string.begin();

  s21_vec_int.erase(pos_int);
  s21_vec_double.erase(pos_double);
  s21_vec_string.erase(pos_string);

  EXPECT_EQ(s21_vec_int[0], 1);
  EXPECT_EQ(s21_vec_double[0], 1.4);
  EXPECT_EQ(s21_vec_string[0], "Hello");
}

TEST(vector, case34) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.push_back(10);
  s21_vec_double.push_back(10.0);
  s21_vec_string.push_back("!!");

  EXPECT_EQ(*(s21_vec_int.end() - 1), 10);
  EXPECT_EQ(*(s21_vec_double.end() - 1), 10.0);
  EXPECT_EQ(*(s21_vec_string.end() - 1), "!!");
}

TEST(vector, case35) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.reserve(20);
  s21_vec_double.reserve(20);
  s21_vec_string.reserve(20);

  s21_vec_int.push_back(10);
  s21_vec_double.push_back(10.0);
  s21_vec_string.push_back("!!");

  EXPECT_EQ(*(s21_vec_int.end() - 1), 10);
  EXPECT_EQ(*(s21_vec_double.end() - 1), 10.0);
  EXPECT_EQ(*(s21_vec_string.end() - 1), "!!");
}

TEST(vector, case36) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.pop_back();
  s21_vec_double.pop_back();
  s21_vec_string.pop_back();

  EXPECT_EQ(s21_vec_int.size(), 3U);
  EXPECT_EQ(s21_vec_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_double.size(), 3U);
  EXPECT_EQ(s21_vec_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_string.size(), 3U);
  EXPECT_EQ(s21_vec_string.capacity(), 4U);
}

TEST(vector, case37) {
  s21::vector<int> s21_vec_ref_int{1, 4, 8, 9};
  s21::vector<int> s21_vec_res_int{0, 0, 0};

  s21::vector<double> s21_vec_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<double> s21_vec_res_double{0.0, 0.0, 0.0};

  s21::vector<std::string> s21_vec_ref_string{"Hello", ",", "world", "!"};
  s21::vector<std::string> s21_vec_res_string{"", "", ""};

  s21_vec_ref_int.swap(s21_vec_res_int);
  s21_vec_ref_double.swap(s21_vec_res_double);
  s21_vec_ref_string.swap(s21_vec_res_string);

  EXPECT_EQ(s21_vec_res_int.size(), 4U);
  EXPECT_EQ(s21_vec_res_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_int[2], 8);

  EXPECT_EQ(s21_vec_res_double.size(), 4U);
  EXPECT_EQ(s21_vec_res_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_double[2], 8.9);

  EXPECT_EQ(s21_vec_res_string.size(), 4U);
  EXPECT_EQ(s21_vec_res_string.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_string[2], "world");
}

TEST(vector, case38) {
  s21::vector<int> s21_vec_int{1, 4};
  s21::vector<double> s21_vec_double{1.4, 4.8};
  s21::vector<std::string> s21_vec_string{"Hello", ","};

  auto pos_int = s21_vec_int.begin() + 1;
  auto pos_double = s21_vec_double.begin() + 1;
  auto pos_string = s21_vec_string.begin() + 1;

  s21_vec_int.insert_many(pos_int, 2, 3);
  s21_vec_double.insert_many(pos_double, 2.0, 3.56);
  s21_vec_string.insert_many(pos_string, "world", "!");

  EXPECT_EQ(s21_vec_int[1], 2);
  EXPECT_EQ(s21_vec_int[2], 3);

  EXPECT_EQ(s21_vec_double[1], 2.0);
  EXPECT_EQ(s21_vec_double[2], 3.56);

  EXPECT_EQ(s21_vec_string[1], "world");
  EXPECT_EQ(s21_vec_string[2], "!");
}

TEST(vector, case39) {
  s21::vector<int> s21_vec_int{1, 4};
  s21::vector<double> s21_vec_double{1.4, 4.8};
  s21::vector<std::string> s21_vec_string{"Hello", ","};

  auto pos_int = s21_vec_int.begin();
  auto pos_double = s21_vec_double.begin();
  auto pos_string = s21_vec_string.begin();

  s21_vec_int.insert_many(pos_int, 2, 3);
  s21_vec_double.insert_many(pos_double, 2.0, 3.56);
  s21_vec_string.insert_many(pos_string, "world", "!");

  EXPECT_EQ(s21_vec_int[0], 2);
  EXPECT_EQ(s21_vec_int[1], 3);

  EXPECT_EQ(s21_vec_double[0], 2.0);
  EXPECT_EQ(s21_vec_double[1], 3.56);

  EXPECT_EQ(s21_vec_string[0], "world");
  EXPECT_EQ(s21_vec_string[1], "!");
}

TEST(vector, case40) {
  s21::vector<int> s21_vec_int;
  s21::vector<double> s21_vec_double;
  s21::vector<std::string> s21_vec_string;

  auto pos_int = s21_vec_int.begin();
  auto pos_double = s21_vec_double.begin();
  auto pos_string = s21_vec_string.begin();

  s21_vec_int.insert_many(pos_int, 2, 3);
  s21_vec_double.insert_many(pos_double, 2.0, 3.56);
  s21_vec_string.insert_many(pos_string, "world", "!");

  EXPECT_EQ(s21_vec_int[0], 2);
  EXPECT_EQ(s21_vec_int[1], 3);

  EXPECT_EQ(s21_vec_double[0], 2.0);
  EXPECT_EQ(s21_vec_double[1], 3.56);

  EXPECT_EQ(s21_vec_string[0], "world");
  EXPECT_EQ(s21_vec_string[1], "!");
}

TEST(vector, case41) {
  s21::vector<int> s21_vec_int{1, 4};
  s21::vector<double> s21_vec_double{1.4, 4.8};
  s21::vector<std::string> s21_vec_string{"Hello", ","};

  s21_vec_int.insert_many_back(2, 3);
  s21_vec_double.insert_many_back(2.0, 3.56);
  s21_vec_string.insert_many_back("world", "!");

  EXPECT_EQ(s21_vec_int[2], 2);
  EXPECT_EQ(s21_vec_int[3], 3);

  EXPECT_EQ(s21_vec_double[2], 2.0);
  EXPECT_EQ(s21_vec_double[3], 3.56);

  EXPECT_EQ(s21_vec_string[2], "world");
  EXPECT_EQ(s21_vec_string[3], "!");
}
