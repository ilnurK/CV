#include "s21_snake_tests.h"

using namespace s21;

class S21SnakeTest1 : public testing::Test {
 protected:
  Field field{};
  Snake snake = Snake(field, Dirs::UP, {0, 3});
};

TEST_F(S21SnakeTest1, TestMoveUp1) {
  snake.SetDirection(Dirs::UP);
  snake.Move(field);
  auto data = snake.GetData();
  ExpectPairEq(data[0], {0, 2});
  ExpectPairEq(data[1], {0, 3});
  ExpectPairEq(data[2], {0, 4});
  ExpectPairEq(data[3], {0, 5});
  // +----------+
  // |          |
  // |          |
  // |0         |
  // |O         |
  // |O         |
  // |o         |
  // |          |
  // ~          ~
  // |          |
  // +----------+
}

TEST_F(S21SnakeTest1, TestMoveRight1) {
  snake.SetDirection(Dirs::UP);
  snake.Move(field);
  snake.SetDirection(Dirs::RIGHT);
  snake.Move(field);
  auto data = snake.GetData();
  ExpectPairEq(data[0], {1, 2});
  ExpectPairEq(data[1], {0, 2});
  ExpectPairEq(data[2], {0, 3});
  ExpectPairEq(data[3], {0, 4});
  // +----------+
  // |          |
  // |          |
  // |O0        |
  // |O         |
  // |o         |
  // |          |
  // ~          ~
  // |          |
  // +----------+
}

TEST_F(S21SnakeTest1, TestMoveDown1) {
  snake.SetDirection(Dirs::UP);
  snake.Move(field);
  snake.SetDirection(Dirs::RIGHT);
  snake.Move(field);
  snake.SetDirection(Dirs::DOWN);
  snake.Move(field);
  auto data = snake.GetData();
  ExpectPairEq(data[0], {1, 3});
  ExpectPairEq(data[1], {1, 2});
  ExpectPairEq(data[2], {0, 2});
  ExpectPairEq(data[3], {0, 3});
  // +----------+
  // |          |
  // |          |
  // |          |
  // |OO        |
  // |o0        |
  // |          |
  // ~          ~
  // |          |
  // +----------+
}

TEST_F(S21SnakeTest1, TestMoveRight2) {
  snake.SetDirection(Dirs::UP);
  snake.Move(field);
  snake.SetDirection(Dirs::RIGHT);
  snake.Move(field);
  snake.SetDirection(Dirs::DOWN);
  snake.Move(field);
  snake.SetDirection(Dirs::RIGHT);
  snake.Move(field);
  auto data = snake.GetData();
  ExpectPairEq(data[0], {2, 3});
  ExpectPairEq(data[1], {1, 3});
  ExpectPairEq(data[2], {1, 2});
  ExpectPairEq(data[3], {0, 2});
  // +----------+
  // |          |
  // |          |
  // |          |
  // |oO        |
  // | O0       |
  // |          |
  // ~          ~
  // |          |
  // +----------+
}

TEST_F(S21SnakeTest1, TestMoveDown2) {
  snake.SetDirection(Dirs::UP);
  snake.Move(field);
  snake.SetDirection(Dirs::RIGHT);
  snake.Move(field);
  snake.SetDirection(Dirs::DOWN);
  snake.Move(field);
  snake.SetDirection(Dirs::RIGHT);
  snake.Move(field);
  snake.SetDirection(Dirs::DOWN);
  snake.Move(field);
  auto data = snake.GetData();
  ExpectPairEq(data[0], {2, 4});
  ExpectPairEq(data[1], {2, 3});
  ExpectPairEq(data[2], {1, 3});
  ExpectPairEq(data[3], {1, 2});
  // +----------+
  // |          |
  // |          |
  // | o        |
  // | OO       |
  // |  0       |
  // |          |
  // ~          ~
  // |          |
  // +----------+
}

TEST_F(S21SnakeTest1, TestMoveLeft1) {
  snake.SetDirection(Dirs::UP);
  snake.Move(field);
  snake.SetDirection(Dirs::RIGHT);
  snake.Move(field);
  snake.SetDirection(Dirs::DOWN);
  snake.Move(field);
  snake.SetDirection(Dirs::RIGHT);
  snake.Move(field);
  snake.SetDirection(Dirs::DOWN);
  snake.Move(field);
  snake.SetDirection(Dirs::LEFT);
  snake.Move(field);
  auto data = snake.GetData();
  ExpectPairEq(data[0], {1, 4});
  ExpectPairEq(data[1], {2, 4});
  ExpectPairEq(data[2], {2, 3});
  ExpectPairEq(data[3], {1, 3});
  // +----------+
  // |          |
  // |          |
  // |          |
  // | oO       |
  // | 0O       |
  // |          |
  // ~          ~
  // |          |
  // +----------+
}

class S21SnakeTest2 : public testing::Test {
 protected:
  Field field{};
  Snake snake = Snake(field, Dirs::LEFT, {0, 3});
};

TEST_F(S21SnakeTest2, TestMoveDown1) {
  snake.SetDirection(Dirs::DOWN);
  snake.Move(field);
  auto data = snake.GetData();
  ExpectPairEq(data[0], {0, 4});
  ExpectPairEq(data[1], {0, 3});
  ExpectPairEq(data[2], {1, 3});
  ExpectPairEq(data[3], {2, 3});
  // +----------+
  // |          |
  // |          |
  // |          |
  // |OOo       |
  // |0         |
  // |          |
  // ~          ~
  // |          |
  // +----------+
}

TEST_F(S21SnakeTest2, TestMoveRight1) {
  snake.SetDirection(Dirs::DOWN);
  snake.Move(field);
  snake.SetDirection(Dirs::RIGHT);
  snake.Move(field);
  auto data = snake.GetData();
  ExpectPairEq(data[0], {1, 4});
  ExpectPairEq(data[1], {0, 4});
  ExpectPairEq(data[2], {0, 3});
  ExpectPairEq(data[3], {1, 3});
  // +----------+
  // |          |
  // |          |
  // |          |
  // |Oo        |
  // |O0        |
  // |          |
  // ~          ~
  // |          |
  // +----------+
}

TEST_F(S21SnakeTest2, TestMoveDown2) {
  snake.SetDirection(Dirs::DOWN);
  snake.Move(field);
  snake.SetDirection(Dirs::RIGHT);
  snake.Move(field);
  snake.SetDirection(Dirs::DOWN);
  snake.Move(field);
  auto data = snake.GetData();
  ExpectPairEq(data[0], {1, 5});
  ExpectPairEq(data[1], {1, 4});
  ExpectPairEq(data[2], {0, 4});
  ExpectPairEq(data[3], {0, 3});
  // +----------+
  // |          |
  // |          |
  // |          |
  // |o         |
  // |OO        |
  // | 0        |
  // |          |
  // ~          ~
  // |          |
  // +----------+
}

TEST(S21FieldTest1, Exception1) {
  Field field{};
  EXPECT_THROW(Snake(field, Dirs::DOWN, {0, 1}), std::out_of_range);
}

TEST(S21FieldTest1, Exception2) {
  Field field{};
  EXPECT_THROW(Snake(field, Dirs::UP, {0, Field::height - 1}),
               std::out_of_range);
}

TEST(S21FieldTest1, Exception3) {
  Field field{};
  EXPECT_THROW(Snake(field, Dirs::LEFT, {Field::width - 3, 1}),
               std::out_of_range);
}

TEST(S21FieldTest1, Exception4) {
  Field field{};
  EXPECT_THROW(Snake(field, Dirs::RIGHT, {2, 1}), std::out_of_range);
}

TEST(S21FieldTest1, Const1) {
  const Field field{};
  EXPECT_EQ(field.At({Field::width - 1, Field::height - 1}), field.GetSymbol());
}

TEST(S21FieldTest1, ConstException1) {
  const Field field{};
  EXPECT_THROW(field.At({Field::width + 1, Field::height + 1}),
               std::out_of_range);
}