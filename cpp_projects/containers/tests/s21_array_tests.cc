#include <array>

#include "test_main.h"

TEST(S21ContainerArraySizeTest, Test1) {
  const s21::array<int, 0> a{};
  EXPECT_TRUE(!a.size());
}

TEST(S21ContainerArraySizeTest, Test2) {
  s21::array<int, 5> arr;
  EXPECT_TRUE(arr.size() == 5);
  EXPECT_TRUE(arr.max_size() == 5);
}

TEST(S21ContainerArrayConstructorTest, Test1) {
  const s21::array<int, 3> a{{1, 4, 5}};
  const std::array<int, 3> b{{1, 4, 5}};
  auto ait = a.begin(), aite = a.end();
  auto bit = b.begin();
  for (; ait != aite; ++ait, ++bit) {
    EXPECT_TRUE(*ait == *bit);
  }
}

TEST(S21ContainerArrayConstructorTest, Test2) {
  s21::array<int, 7> a = {11, 24, 35, 41, 50, 69, 13};
  s21::array<int, 7> b(a);

  EXPECT_TRUE(a.size() == 7);

  for (size_t i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a[i], b[i]);
  }
}

TEST(S21ContainerArrayConstructorTest, Test3) {
  s21::array<int, 7> a = {11, 24, 35, 41, 50, 69, 13};
  s21::array<int, 7> b(std::move(a));

  EXPECT_TRUE(a.size() == 7);
  EXPECT_TRUE(a[0] == 11 && a[1] == 24 && a[2] == 35 && a[3] == 41);
  EXPECT_TRUE(a[4] == 50 && a[5] == 69 && a[6] == 13);
  for (size_t i = 0; i < 7; i++) {
    b[i] = 0;
  }
}

TEST(S21ContainerArrayConstructorTest, Test4) {
  s21::array<int, 7> a = {11, 24, 35, 41, 50, 69, 13};
  s21::array<int, 7> b = a;

  EXPECT_TRUE(b.size() == 7);

  for (size_t i = 0; i < b.size(); ++i) {
    EXPECT_EQ(a[i], b[i]);
  }
}

TEST(S21ContainerArrayConstructorTest, Test5) {
  s21::array<int, 7> a = {11, 24, 35, 41, 50, 69, 13};
  s21::array<int, 7> b = std::move(a);

  EXPECT_TRUE(a.size() == 7);
  EXPECT_TRUE(a[0] == 11 && a[1] == 24 && a[2] == 35 && a[3] == 41);
  EXPECT_TRUE(a[4] == 50 && a[5] == 69 && a[6] == 13);
  for (size_t i = 0; i < 7; i++) {
    b[i] = 0;
  }
}

TEST(S21ContainerArrayIteratorTest, Test1) {
  s21::array<int, 7> a = {11, 24, 35, 41, 50, 69, 13};
  auto it = a.begin();
  EXPECT_TRUE(*it == 11);
  *it = 21;
  EXPECT_TRUE(*it == 21);
  it += 3;
  EXPECT_TRUE(*it == 41);
}

TEST(S21ContainerArrayIteratorTest, Test2) {
  s21::array<int, 7> a = {11, 24, 35, 41, 50, 69, 13};
  auto it = a.begin();
  auto ite = a.end();
  it += 7;
  EXPECT_TRUE(ite == it);
}

TEST(S21ContainerArrayIteratorTest, Test3) {
  const s21::array<int, 7> a = {11, 24, 35, 41, 50, 69, 13};
  auto it = a.begin();
  const auto cit = a.begin();

  EXPECT_TRUE(*it == 11);
  EXPECT_TRUE(*cit == 11);
}

TEST(S21ContainerArrayIndexingTest, Test1) {
  const s21::array<int, 7> a = {11, 24, 35, 41, 50, 69, 13};
  int res = a.at(3);
  EXPECT_TRUE(res = 41);
  res = a[3];
  EXPECT_TRUE(res = 41);
}

TEST(S21ContainerArrayIndexingTest, Test2) {
  const s21::array<int, 7> a = {11, 24, 35, 41, 50, 69, 13};
  int res = a.at(5);
  EXPECT_TRUE(res = 69);
  res = a[3];
  EXPECT_TRUE(res = 69);
}

TEST(S21ContainerArrayIndexingTest, Test3) {
  const s21::array<int, 7> a = {11, 24, 35, 41, 50, 69, 13};
  EXPECT_THROW(a.at(15), std::out_of_range);
}

TEST(S21ContainerArrayIndexingTest, Test4) {
  const s21::array<int, 7> a = {11, 24, 35, 41, 50, 69, 13};
  EXPECT_THROW(a.at(-1), std::out_of_range);
}

TEST(S21ContainerArrayMethodsTest, Test1) {
  const s21::array<int, 7> a = {11, 24, 35, 41, 50, 69, 13};
  int res_front = a.front();
  int res_back = a.back();
  EXPECT_TRUE(res_front == 11);
  EXPECT_TRUE(res_back == 13);
}

TEST(S21ContainerArrayMethodsTest, Test2) {
  s21::array<int, 7> a = {11, 24, 35, 41, 50, 69, 13};
  int res_front = a.front();
  int res_back = a.back();
  EXPECT_TRUE(res_front == 11);
  EXPECT_TRUE(res_back == 13);
}

TEST(S21ContainerArrayMethodsTest, Test3) {
  s21::array<int, 7> a = {11, 24, 35, 41, 50, 69, 13};
  EXPECT_FALSE(a.empty());
}

TEST(S21ContainerArrayMethodsTest, Test4) {
  s21::array<int, 7> a = {11, 24, 35, 41, 50, 69, 13};
  a.fill(4);
  for (auto it : a) {
    EXPECT_TRUE(it == 4);
  }
}

TEST(S21ContainerArrayMethodsTest, Test5) {
  s21::array<std::string, 4> a = {"hello", "world", "cpp", "h"};
  a.fill("filler");
  for (auto it : a) {
    EXPECT_TRUE(it == "filler");
  }
}

TEST(S21ContainerArrayMethodsTest, Test6) {
  s21::array<std::string, 4> a = {"hello", "world", "cpp", "h"};
  s21::array<std::string, 4> b = {"goodbuy", "program", "c", "h"};

  a.swap(b);
  EXPECT_TRUE(a[0] == "goodbuy" && b[0] == "hello");
  EXPECT_TRUE(a[1] == "program" && b[1] == "world");
  EXPECT_TRUE(a[2] == "c" && b[2] == "cpp");
  EXPECT_TRUE(a[3] == "h" && b[3] == "h");
}
