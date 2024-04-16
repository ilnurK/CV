#include <time.h>

#include <set>

#include "test_main.h"

using namespace s21;

int get_rand(int min, int max) { return min + rand() % (max - min + 1); }

class SetFixture : public testing::Test {
 protected:
  int size;

  s21::set<int> mySetInt;
  std::set<int> setInt;
  s21::set<double> mySetDouble;
  std::set<double> setDouble;
  s21::set<char> mySetChar;
  std::set<char> setChar;
  s21::set<std::string> mySetString;
  std::set<std::string> setString;

  static void SetUpTestSuite() {
    // Настройка тестового окружения перед набором тестов
    srand(time(NULL));
  }

  void SetUp() override {
    // Подготовка тестового окружения перед каждым тестом
    size = get_rand(1, 100);

    mySetInt = s21::set<int>();
    setInt = std::set<int>();
    mySetDouble = s21::set<double>();
    setDouble = std::set<double>();
    mySetChar = s21::set<char>();
    setChar = std::set<char>();
    mySetString = s21::set<std::string>();
    setString = std::set<std::string>();
  }
};

TEST_F(SetFixture, IsEmpty) {
  EXPECT_TRUE(mySetInt.empty());
  EXPECT_TRUE(mySetDouble.empty());
  EXPECT_TRUE(mySetChar.empty());
  EXPECT_TRUE(mySetString.empty());
}

TEST_F(SetFixture, InsertIntAndDouble) {
  for (int i = 0; i < size; i++) {
    int item = get_rand(1, 100);
    double dItem = (double)item / (double)get_rand(1, 100);
    EXPECT_EQ(mySetInt.insert(item).second, setInt.insert(item).second);
    EXPECT_EQ(mySetDouble.insert(dItem).second, setDouble.insert(dItem).second);
  }
  ASSERT_EQ(mySetInt.size(), setInt.size());
  ASSERT_EQ(mySetDouble.size(), setDouble.size());

  auto mySetIterator = mySetInt.begin();
  for (auto setIterator = setInt.begin(); setIterator != setInt.end();
       ++setIterator) {
    EXPECT_EQ(*mySetIterator, *setIterator);
    mySetIterator++;
  }

  const s21::set<int> mySet{1, 2, 3};
  auto it = mySet.begin();
  auto ite = mySet.end();
  for (; it != ite; ++it)
    ;
  --it;
  EXPECT_EQ(*it, 3);

  auto mySetIteratorDouble = mySetDouble.begin();
  for (auto setIteratorDouble = setDouble.begin();
       setIteratorDouble != setDouble.end(); ++setIteratorDouble) {
    EXPECT_EQ(*mySetIteratorDouble, *setIteratorDouble);
    mySetIteratorDouble++;
  }
}

TEST_F(SetFixture, InsertString) {
  std::string str1 = "§1234567890-=[]poiuytrewq";
  mySetString.insert(str1);
  setString.insert(str1);

  std::string str2 = "asdfghjkl;'.,mnbvcxz`";
  mySetString.insert(str2);
  setString.insert(str2);

  std::string str3 = "±!@#$%^&*()_+}{POIUYTREWQ}";
  mySetString.insert(str3);
  setString.insert(str3);

  std::string str4 = "ASDFGHJKL:|?><MNBVCXZ~";
  mySetString.insert(str4);
  setString.insert(str4);

  ASSERT_EQ(mySetString.size(), setString.size());
  auto mySetIterator = mySetString.begin();
  for (auto setIterator = setString.begin(); setIterator != setString.end();
       ++setIterator) {
    EXPECT_EQ(*mySetIterator, *setIterator);
    mySetIterator++;
  }
}

TEST_F(SetFixture, Erase) {
  mySetInt.insert_many(1, 2, 3, 4, 5);
  mySetDouble.insert_many(5.4, 345.7, -12.5, 0.00001);
  mySetChar.insert_many('c', 'u', '#', '0');
  mySetString.insert_many("4rf", "9j3", "R@#GET");

  mySetInt.erase(mySetInt.find(4));
  mySetDouble.erase(mySetDouble.find(-12.5));
  mySetChar.erase(mySetChar.find('c'));
  mySetString.erase(mySetString.find("R@#GET"));

  EXPECT_FALSE(mySetInt.contains(4));
  EXPECT_FALSE(mySetDouble.contains(-12.5));
  EXPECT_FALSE(mySetChar.contains('c'));
  EXPECT_FALSE(mySetString.contains("R@#GET"));
}

TEST_F(SetFixture, Swap) {
  mySetInt = {1, 2, 3, 4, 5};
  setInt = {1, 2, 3, 4, 5};
  mySetDouble = {-3.51, 0.79};
  setDouble = {-3.51, 0.79};
  mySetChar = {};
  setChar = {};
  mySetString = {"abc", "def"};
  setString = {"abc", "def"};

  s21::set<int> mySetInt2{6, 7, 8, 9, 0, -1};
  std::set<int> setInt2{6, 7, 8, 9, 0, -1};
  s21::set<double> mySetDouble2{4.2, 7.54, -0.51};
  std::set<double> setDouble2{4.2, 7.54, -0.51};
  s21::set<char> mySetChar2{'h', 'e', 'l', 'l', 'o'};
  std::set<char> setChar2{'h', 'e', 'l', 'l', 'o'};
  s21::set<std::string> mySetString2{"ghi", "jkl", "mnop"};
  std::set<std::string> setString2{"ghi", "jkl", "mnop"};

  mySetInt.swap(mySetInt2);
  mySetDouble.swap(mySetDouble2);
  mySetChar.swap(mySetChar2);
  mySetString.swap(mySetString2);

  setInt.swap(setInt2);
  setDouble.swap(setDouble2);
  setChar.swap(setChar2);
  setString.swap(setString2);

  ASSERT_EQ(mySetInt.size(), setInt.size());
  auto myIntIterator = mySetInt.begin();
  for (auto setIterator = setInt.begin(); setIterator != setInt.end();
       ++setIterator) {
    EXPECT_EQ(*myIntIterator, *setIterator);
    ++myIntIterator;
  }

  ASSERT_EQ(mySetInt2.size(), setInt2.size());
  auto myIntIterator2 = mySetInt2.begin();
  for (auto setIterator = setInt2.begin(); setIterator != setInt2.end();
       ++setIterator) {
    EXPECT_EQ(*myIntIterator2, *setIterator);
    myIntIterator2++;
  }

  ASSERT_EQ(mySetDouble.size(), setDouble.size());
  auto myDoubleIterator = mySetDouble.begin();
  for (auto setIterator = setDouble.begin(); setIterator != setDouble.end();
       ++setIterator) {
    EXPECT_EQ(*myDoubleIterator, *setIterator);
    myDoubleIterator++;
  }

  ASSERT_EQ(mySetDouble2.size(), setDouble2.size());
  auto myDoubleIterator2 = mySetDouble2.begin();
  for (auto setIterator = setDouble2.begin(); setIterator != setDouble2.end();
       ++setIterator) {
    EXPECT_EQ(*myDoubleIterator2, *setIterator);
    myDoubleIterator2++;
  }

  ASSERT_EQ(mySetChar.size(), setChar.size());
  auto myCharIterator = mySetChar.begin();
  for (auto setIterator = setChar.begin(); setIterator != setChar.end();
       ++setIterator) {
    EXPECT_EQ(*myCharIterator, *setIterator);
    myCharIterator++;
  }

  ASSERT_EQ(mySetChar2.size(), setChar2.size());
  auto myCharIterator2 = mySetChar2.begin();
  for (auto setIterator = setChar2.begin(); setIterator != setChar2.end();
       ++setIterator) {
    EXPECT_EQ(*myCharIterator2, *setIterator);
    myCharIterator2++;
  }

  ASSERT_EQ(mySetString.size(), setString.size());
  auto myStringIterator = mySetString.begin();
  for (auto setIterator = setString.begin(); setIterator != setString.end();
       ++setIterator) {
    EXPECT_EQ(*myStringIterator, *setIterator);
    myStringIterator++;
  }

  ASSERT_EQ(mySetString2.size(), setString2.size());
  auto myStringIterator2 = mySetString2.begin();
  for (auto setIterator = setString2.begin(); setIterator != setString2.end();
       ++setIterator) {
    EXPECT_EQ(*myStringIterator2, *setIterator);
    myStringIterator2++;
  }
}

TEST_F(SetFixture, Merge) {
  mySetInt = {1, 2, 3, 4, 5};
  setInt = {1, 2, 3, 4, 5};
  mySetDouble = {-3.51, 0.79};
  setDouble = {-3.51, 0.79};
  mySetChar = {};
  setChar = {};
  mySetString = {"abc", "def"};
  setString = {"abc", "def"};

  s21::set<int> mySetInt2{6, 7, 8, 9, 0, -1};
  std::set<int> setInt2{6, 7, 8, 9, 0, -1};
  s21::set<double> mySetDouble2{4.2, 7.54, -0.51};
  std::set<double> setDouble2{4.2, 7.54, -0.51};
  s21::set<char> mySetChar2{'h', 'e', 'l', 'l', 'o'};
  std::set<char> setChar2{'h', 'e', 'l', 'l', 'o'};
  s21::set<std::string> mySetString2{"ghi", "jkl", "mnop"};
  std::set<std::string> setString2{"ghi", "jkl", "mnop"};

  mySetInt.merge(mySetInt2);
  mySetDouble.merge(mySetDouble2);
  mySetChar.merge(mySetChar2);
  mySetString.merge(mySetString2);

  setInt.merge(setInt2);
  setDouble.merge(setDouble2);
  setChar.merge(setChar2);
  setString.merge(setString2);

  ASSERT_EQ(mySetInt.size(), setInt.size());
  auto myIntIterator = mySetInt.begin();
  for (auto setIterator = setInt.begin(); setIterator != setInt.end();
       ++setIterator) {
    EXPECT_EQ(*myIntIterator, *setIterator);
    ++myIntIterator;
  }

  ASSERT_EQ(mySetInt2.size(), setInt2.size());
  auto myIntIterator2 = mySetInt2.begin();
  for (auto setIterator = setInt2.begin(); setIterator != setInt2.end();
       ++setIterator) {
    EXPECT_EQ(*myIntIterator2, *setIterator);
    myIntIterator2++;
  }

  ASSERT_EQ(mySetDouble.size(), setDouble.size());
  auto myDoubleIterator = mySetDouble.begin();
  for (auto setIterator = setDouble.begin(); setIterator != setDouble.end();
       ++setIterator) {
    EXPECT_EQ(*myDoubleIterator, *setIterator);
    myDoubleIterator++;
  }

  ASSERT_EQ(mySetDouble2.size(), setDouble2.size());
  auto myDoubleIterator2 = mySetDouble2.begin();
  for (auto setIterator = setDouble2.begin(); setIterator != setDouble2.end();
       ++setIterator) {
    EXPECT_EQ(*myDoubleIterator2, *setIterator);
    myDoubleIterator2++;
  }

  ASSERT_EQ(mySetChar.size(), setChar.size());
  auto myCharIterator = mySetChar.begin();
  for (auto setIterator = setChar.begin(); setIterator != setChar.end();
       ++setIterator) {
    EXPECT_EQ(*myCharIterator, *setIterator);
    myCharIterator++;
  }

  ASSERT_EQ(mySetChar2.size(), setChar2.size());
  auto myCharIterator2 = mySetChar2.begin();
  for (auto setIterator = setChar2.begin(); setIterator != setChar2.end();
       ++setIterator) {
    EXPECT_EQ(*myCharIterator2, *setIterator);
    myCharIterator2++;
  }

  ASSERT_EQ(mySetString.size(), setString.size());
  auto myStringIterator = mySetString.begin();
  for (auto setIterator = setString.begin(); setIterator != setString.end();
       ++setIterator) {
    EXPECT_EQ(*myStringIterator, *setIterator);
    myStringIterator++;
  }

  ASSERT_EQ(mySetString2.size(), setString2.size());
  auto myStringIterator2 = mySetString2.begin();
  for (auto setIterator = setString2.begin(); setIterator != setString2.end();
       ++setIterator) {
    EXPECT_EQ(*myStringIterator2, *setIterator);
    myStringIterator2++;
  }
}

TEST(Set, InitializerList) {
  s21::set<int> mySet{45, 578, 23, -56, 0, -18};
  std::set<int> set{45, 578, 23, -56, 0, -18};

  ASSERT_EQ(mySet.size(), set.size());
  auto mySetIterator = mySet.begin();
  for (auto setIterator = set.begin(); setIterator != set.end();
       ++setIterator) {
    EXPECT_EQ(*mySetIterator, *setIterator);
    mySetIterator++;
  }
}