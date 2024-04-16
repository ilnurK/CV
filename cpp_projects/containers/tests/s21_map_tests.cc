#include <map>

#include "test_main.h"

class S21MapTest : public testing::Test {
 protected:
  s21::map<int, int> m{};
  std::map<int, int> sm{};

 public:
  void SetUp() override {
    m.insert({41, 0});
    m.insert({30, 0});
    m.insert({38, 0});
    m.insert({36, 0});
    m.insert({40, 0});
    m.insert({37, 0});
    m.insert({45, 0});
    m.insert({42, 0});
    m.insert({43, 0});
    m.insert({44, 0});
    m.insert({46, 0});
    m.insert({47, 0});
    m.insert({48, 0});
    m.insert({49, 0});

    sm.insert({41, 0});
    sm.insert({30, 0});
    sm.insert({38, 0});
    sm.insert({36, 0});
    sm.insert({40, 0});
    sm.insert({37, 0});
    sm.insert({45, 0});
    sm.insert({42, 0});
    sm.insert({43, 0});
    sm.insert({44, 0});
    sm.insert({46, 0});
    sm.insert({47, 0});
    sm.insert({48, 0});
    sm.insert({49, 0});
  }
};

TEST_F(S21MapTest, TestSize) {
  EXPECT_TRUE(m.size() == sm.size());
  m.clear();
  sm.clear();
  EXPECT_TRUE(m.size() == sm.size());
}

TEST_F(S21MapTest, TestInsert) {
  auto it = m.begin(), ite = m.end();
  auto sit = sm.begin();
  for (; it != ite; ++it, ++sit) {
    EXPECT_TRUE((*it).first == (*sit).first);
  }
}

TEST_F(S21MapTest, TestCopyConstructor) {
  s21::map<int, int> copy_m(m);
  auto it = m.begin(), ite = m.end();
  auto sit = sm.begin();
  auto copy_it = copy_m.begin();
  for (; it != ite; ++it, ++sit, ++copy_it) {
    EXPECT_TRUE((*it).first == (*sit).first);
    EXPECT_TRUE((*it).first == (*copy_it).first);
  }
}

TEST_F(S21MapTest, TestCopyOperator) {
  s21::map<int, int> copy_m = m;
  auto it = m.begin(), ite = m.end();
  auto sit = sm.begin();
  auto copy_it = copy_m.begin();
  for (; it != ite; ++it, ++sit, ++copy_it) {
    EXPECT_TRUE((*it).first == (*sit).first);
    EXPECT_TRUE((*it).first == (*copy_it).first);
  }
}

TEST_F(S21MapTest, TestMoveConstructor) {
  s21::map<int, int> copy_m(std::move(m));
  auto it = m.begin(), ite = m.end();
  auto sit = sm.begin();
  auto copy_it = copy_m.begin();
  for (; it != ite; ++it, ++sit, ++copy_it) {
    EXPECT_TRUE((*it).first == (*sit).first);
    EXPECT_TRUE((*it).first == (*copy_it).first);
  }
}

TEST_F(S21MapTest, TestMoveOperator) {
  s21::map<int, int> move_m = std::move(m);
  auto it = m.begin(), ite = m.end();
  auto sit = sm.begin();
  auto move_it = move_m.begin();
  for (; it != ite; ++it, ++sit, ++move_it) {
    EXPECT_TRUE((*sit).first == (*move_it).first);
  }
}

TEST_F(S21MapTest, TestErase) {
  m.erase(m.begin());
  sm.erase(sm.begin());
  m.erase(m.begin());
  sm.erase(sm.begin());
  m.erase(m.begin());
  sm.erase(sm.begin());
  auto it = m.begin(), ite = m.end();
  auto sit = sm.begin();
  for (; it != ite; ++it, ++sit) {
    EXPECT_TRUE((*it).first == (*sit).first);
  }
  EXPECT_TRUE(m.size() == sm.size());
}

TEST_F(S21MapTest, TestAccess) {
  m.at(37) = 43;
  sm.at(37) = 43;
  m[46] = 11;
  sm[46] = 11;
  auto it = m.begin(), ite = m.end();
  auto sit = sm.begin();
  for (; it != ite; ++it, ++sit) {
    EXPECT_TRUE((*it).first == (*sit).first);
  }
}

TEST_F(S21MapTest, TestAccessException) {
  EXPECT_THROW(m.at(370), std::out_of_range);
}

TEST_F(S21MapTest, TestInsertCapacity) {
  size_t m_size = m.size();
  m.insert_or_assign(55, 11);
  sm.insert_or_assign(55, 11);
  EXPECT_TRUE(m_size + 1 == m.size());
  EXPECT_TRUE(m.size() == sm.size());
  m.insert_or_assign(55, 11);
  sm.insert_or_assign(55, 11);
  EXPECT_TRUE(m_size + 1 == m.size());
  EXPECT_TRUE(m.size() == sm.size());
}

TEST(S21MapTestAnotherConstructors, TestNullConstructor) {
  s21::map<std::string, char> m1;
  std::map<std::string, char> sm1;
  EXPECT_EQ(m1.empty(), sm1.empty());

  s21::map<std::string, std::string> m2;
  std::map<std::string, std::string> sm2;
  EXPECT_EQ(m2.empty(), sm2.empty());

  s21::map<double, int> m3;
  std::map<double, int> sm3;
  EXPECT_EQ(m3.empty(), sm3.empty());
}

TEST(S21MapTestSwap, TestSwap) {
  s21::map<std::string, double> m1 = {
      {"test", 1.1}, {"cpp", 0.8}, {"wow", 9.2}};
  s21::map<std::string, double> m2 = {{"program", 0.01}, {"compilator", 0.02}};

  m1.swap(m2);
  EXPECT_TRUE(m1.size() == 2);
  EXPECT_TRUE(m2.size() == 3);
  auto a = (*(m1.begin())).first;
  auto b = (*(m2.begin())).first;
  EXPECT_EQ(a, "compilator");
  EXPECT_EQ(b, "cpp");
}

TEST(S21MapTestMerge, TestMerge) {
  s21::map<char, char> m1 = {{'1', 'a'}, {'9', 'b'}, {'6', 'c'}};
  s21::map<char, char> m1_donor = {{'2', 'x'}, {'3', 'y'}};

  std::map<char, char> m2 = {{'1', 'a'}, {'9', 'b'}, {'6', 'c'}};
  std::map<char, char> m2_donor = {{'2', 'x'}, {'3', 'y'}};

  m1.merge(m1_donor);
  m2.merge(m2_donor);

  auto it1 = m1.begin(), ite1 = m1.end();
  auto it2 = m2.begin();
  for (; it1 != ite1; ++it1, ++it2) {
    EXPECT_TRUE((*it1).first == (*it2).first);
    EXPECT_TRUE((*it1).second == (*it2).second);
  }
  EXPECT_EQ(m1.contains('9'), 1);
  EXPECT_EQ(m1.contains('3'), 1);
  EXPECT_EQ(m1.contains('0'), 0);
}