#include "s21_snake_tests.h"

using namespace s21;

TEST(S21SnakeTestController1, Test1) {
  xy_pair xy_snake{Field::width / 2, Field::height / 2};
  xy_pair xy_apple{Field::width / 2, Field::height / 2 - 1};
  SnakeController sc = SnakeController(true, Dirs::UP, xy_snake, xy_apple);
  size_t old_snake_size = sc.GetSnakeSize();
  GameStatus status = sc.SetState(SnakeStates::MOVING);

  EXPECT_EQ(status, GameStatus::ON_AIR);
  size_t need_size{1};
  EXPECT_EQ(need_size, sc.GetSnakeSize() - old_snake_size);
}

TEST(S21SnakeTestController1, Test2) {
  xy_pair xy_snake{Field::width - 1, Field::height / 2};
  SnakeController sc = SnakeController(true, Dirs::RIGHT, xy_snake);
  GameStatus status = sc.SetState(SnakeStates::MOVING);

  EXPECT_EQ(status, GameStatus::GAME_OVER);
}

TEST(S21SnakeTestController1, Test3) {
  xy_pair xy_snake{Field::width - 4, Field::height / 2};
  xy_pair xy_apple{Field::width - 5, Field::height / 2};
  SnakeController sc = SnakeController(true, Dirs::LEFT, xy_snake, xy_apple);
  sc.SetScore(195);
  GameStatus status = sc.SetState(SnakeStates::MOVING);
  EXPECT_EQ(status, GameStatus::WIN);
}

TEST(S21SnakeTestController1, TestRandom1) {
  SnakeController sc = SnakeController();
  GameStatus status = sc.SetState(SnakeStates::START);
  EXPECT_EQ(status, GameStatus::ON_AIR);
}

TEST(S21SnakeTestController1, TestRandom2) {
  SnakeController sc = SnakeController();
  GameStatus status = sc.SetState(SnakeStates::MOVING);
  EXPECT_EQ(status, GameStatus::ON_AIR);
}

TEST(S21SnakeTestController1, TestRandom3) {
  SnakeController sc = SnakeController();
  GameStatus status = sc.SetState(SnakeStates::MOVING);
  EXPECT_EQ(status, GameStatus::ON_AIR);
}

TEST(S21SnakeTestController1, TestHighScore1) {
  SnakeController sc = SnakeController();
  sc.SetHighScore(0);
  sc.SetScore(100);
  GameStatus status = sc.SetState(SnakeStates::COLLIDED);
  EXPECT_EQ(status, GameStatus::GAME_OVER);
  sc.WriteScore();
  size_t need_score{100};

  EXPECT_EQ(sc.GetHighScore(), need_score);
}

TEST(S21SnakeTestController1, TestLevelUp1) {
  xy_pair xy_snake{Field::width - 4, Field::height / 2};
  xy_pair xy_apple{Field::width - 5, Field::height / 2};
  SnakeController sc = SnakeController(true, Dirs::LEFT, xy_snake, xy_apple);
  sc.SetScore(4);
  GameStatus status = sc.SetState(SnakeStates::MOVING);
  EXPECT_EQ(status, GameStatus::LEVEL_UP);
}

TEST(S21SnakeTestController1, TestShifting1) {
  xy_pair xy_snake{Field::width - 4, Field::height / 2};
  xy_pair xy_apple{Field::width - 5, Field::height / 2};
  SnakeController sc = SnakeController(true, Dirs::LEFT, xy_snake, xy_apple);
  sc.SetScore(4);
  GameStatus status = sc.SetState(SnakeStates::SHIFTING, Dirs::UP);
  EXPECT_EQ(status, GameStatus::ON_AIR);
}

TEST(S21SnakeTestController1, TestMoveColided1) {
  xy_pair xy_snake{Field::width - 4, Field::height / 2};
  xy_pair xy_apple{0, 0};
  SnakeController sc = SnakeController(true, Dirs::LEFT, xy_snake, xy_apple);
  sc.SetScore(4);
  sc.SetState(SnakeStates::SHIFTING, Dirs::UP);
  sc.SetState(SnakeStates::SHIFTING, Dirs::RIGHT);
  GameStatus status = sc.SetState(SnakeStates::SHIFTING, Dirs::DOWN);
  EXPECT_EQ(status, GameStatus::GAME_OVER);
}
