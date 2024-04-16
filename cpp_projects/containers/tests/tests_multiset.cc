#include <set>

#include "test_main.h"

using namespace s21;

class MultisetFixture : public testing::Test {
 protected:
  s21::multiset<int> mySetInt;
  std::multiset<int> setInt;
  s21::multiset<double> mySetDouble;
  std::multiset<double> setDouble;
  s21::multiset<char> mySetChar;
  std::multiset<char> setChar;
  s21::multiset<std::string> mySetString;
  std::multiset<std::string> setString;

  void SetUp() override {
    mySetInt = {1, 2, 3, 4, 5, -271, -8, 0, 0, 0, -14, -271, 5};
    setInt = {1, 2, 3, 4, 5, -271, -8, 0, 0, 0, -14, -271, 5};
    mySetDouble = {0.0,   0.0, 4.34, -123456.7, -123456.8, 987.0,
                   987.0, 4,   341,  -268.86,   -268.86,   -268.86};
    setDouble = {0.0,   0.0, 4.34, -123456.7, -123456.8, 987.0,
                 987.0, 4,   341,  -268.86,   -268.86,   -268.86};
    mySetChar = {'a', 'a', 'a', 'a', '4', ',', ',', '~'};
    setChar = {'a', 'a', 'a', 'a', '4', ',', ',', '~'};
    mySetString = {"ieuhg", "a", "a", "2345t", "HFSD"};
    setString = {"ieuhg", "a", "a", "2345t", "HFSD"};
  }
};

TEST(MultiSet, Insert) {
  s21::multiset<int> myMultiset{1, 2, 3, 4, 5};
  std::multiset<int> mulitset{1, 2, 3, 4, 4, 5};
  myMultiset.insert(4);

  ASSERT_EQ(myMultiset.size(), mulitset.size());
  auto myIterator = myMultiset.begin();
  for (auto Iterator = mulitset.begin(); Iterator != mulitset.end();
       ++Iterator) {
    EXPECT_EQ(*myIterator, *Iterator);
    myIterator++;
  }
}

TEST(MultiSet, InsertManyInt) {
  s21::multiset<int> myMultiset{3, 45, -651, 0};
  std::multiset<int> mulitset{-651, -76, 0, 0, 3, 45, 45, 8567, 8923789};
  myMultiset.insert_many(45, 8567, -76, 0, 8923789);

  ASSERT_EQ(myMultiset.size(), mulitset.size());
  auto myIterator = myMultiset.begin();
  for (auto Iterator = mulitset.begin(); Iterator != mulitset.end();
       ++Iterator) {
    EXPECT_EQ(*myIterator, *Iterator);
    myIterator++;
  }
}

TEST(MultiSet, InsertManyDouble) {
  s21::multiset<double> myMultiset{3.456, 45.001, -651.3, 0};
  std::multiset<double> mulitset{-651.3, -76.0,  0.0,     0.0,      3.456,
                                 45.001, 45.001, 8567.02, 8923789.0};
  myMultiset.insert_many(45.001, 8567.02, -76.0, 0.0, 8923789.0);

  ASSERT_EQ(myMultiset.size(), mulitset.size());
  auto myIterator = myMultiset.begin();
  for (auto Iterator = mulitset.begin(); Iterator != mulitset.end();
       ++Iterator) {
    EXPECT_EQ(*myIterator, *Iterator);
    myIterator++;
  }
}

TEST(MultiSet, InsertManyString) {
  s21::multiset<std::string> myMultiset{"zjlgh", "abc", "(^&(&"};
  std::multiset<std::string> mulitset{"zjlgh", "abc",    "(^&(&", "rty",
                                      "abc",   "65s4df", "+_()*"};
  myMultiset.insert_many("rty", "abc", "65s4df", "+_()*");

  ASSERT_EQ(myMultiset.size(), mulitset.size());
  auto myIterator = myMultiset.begin();
  for (auto Iterator = mulitset.begin(); Iterator != mulitset.end();
       ++Iterator) {
    EXPECT_EQ(*myIterator, *Iterator);
    myIterator++;
  }
}

TEST_F(MultisetFixture, Count) {
  for (int i = -273; i <= 273; i++) {
    EXPECT_EQ(mySetInt.count(i), setInt.count(i));
  }
  for (double d = -273.0; d <= 273.0; d += 1.38) {
    EXPECT_EQ(mySetDouble.count(d), setDouble.count(d));
  }
  for (int c = 0; c <= 255; c++) {
    EXPECT_EQ(mySetChar.count(c), setChar.count(c));
  }
  EXPECT_EQ(mySetString.count("HFSD"), setString.count("HFSD"));
  EXPECT_EQ(mySetString.count("a"), setString.count("a"));
  EXPECT_EQ(mySetString.count("df;j"), setString.count("df;j"));
  EXPECT_EQ(mySetString.count(""), setString.count(""));
}

TEST_F(MultisetFixture, Upper_lower_bound) {
  for (int key = -271; key < 5; key++) {
    auto upperIt = setInt.upper_bound(key);
    auto myUpperIt = mySetInt.upper_bound(key);
    EXPECT_EQ(*upperIt, *myUpperIt);
    auto lowerIt = setInt.lower_bound(key);
    auto myLowerIt = mySetInt.lower_bound(key);
    EXPECT_EQ(*lowerIt, *myLowerIt);
  }
  for (double key = -273.0; key <= 273.0; key += 1.38) {
    auto upperIt = setDouble.upper_bound(key);
    auto myUpperIt = mySetDouble.upper_bound(key);
    EXPECT_EQ(*upperIt, *myUpperIt);
    auto lowerIt = setDouble.lower_bound(key);
    auto myLowerIt = mySetDouble.lower_bound(key);
    EXPECT_EQ(*lowerIt, *myLowerIt);
  }
  for (int key = 44; key < 126; key++) {
    auto upperIt = setChar.upper_bound(key);
    auto myUpperIt = mySetChar.upper_bound(key);
    EXPECT_EQ(*upperIt, *myUpperIt);
    auto lowerIt = setChar.lower_bound(key);
    auto myLowerIt = mySetChar.lower_bound(key);
    EXPECT_EQ(*lowerIt, *myLowerIt);
  }
  EXPECT_EQ(*mySetString.upper_bound("b"), *setString.upper_bound("b"));
  EXPECT_EQ(*mySetString.upper_bound("HFSD"), *setString.upper_bound("HFSD"));
  EXPECT_EQ(*(--mySetString.upper_bound("ieuhg")),
            *(--setString.upper_bound("ieuhg")));
  EXPECT_EQ(*mySetString.upper_bound(""), *setString.upper_bound(""));

  EXPECT_EQ(*mySetString.lower_bound("HFSD"), *setString.lower_bound("HFSD"));
  EXPECT_EQ(*mySetString.lower_bound("b"), *setString.lower_bound("b"));
  EXPECT_EQ(*mySetString.lower_bound("ieuhg"), *setString.lower_bound("ieuhg"));
  EXPECT_EQ(*mySetString.lower_bound(""), *setString.lower_bound(""));
}