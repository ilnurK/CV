#include "s21_snake_tests.h"

using namespace s21;

TEST(S21SnakeTestController1, Test1) {
  xy_pair xy_snake{Field::width / 2, Field::height / 2};
  xy_pair xy_apple{Field::width / 2, Field::height / 2 - 1};
  SnakeController sc = SnakeController(true, dirs::UP, xy_snake, xy_apple);
  const auto f = sc.GetField();
  EXPECT_EQ(sc.IsFilledCell(f[xy_apple.second * Field::width + xy_apple.first]),
            true);
  size_t old_snake_size = sc.GetSnakeSize();
  SnakeStates state = sc.SetState(SnakeStates::MOVING, dirs::NULL_DIR);

  EXPECT_EQ(state, SnakeStates::MOVING);
  size_t need_size{1};
  EXPECT_EQ(need_size, sc.GetSnakeSize() - old_snake_size);
}

TEST(S21SnakeTestController1, Test2) {
  xy_pair xy_snake{Field::width - 1, Field::height / 2};
  SnakeController sc = SnakeController(true, dirs::RIGHT, xy_snake);
  SnakeStates state = sc.SetState(SnakeStates::MOVING, dirs::NULL_DIR);

  EXPECT_EQ(state, SnakeStates::GAME_OVER);
}

TEST(S21SnakeTestController1, Test3) {
  xy_pair xy_snake{Field::width - 4, Field::height / 2};
  xy_pair xy_apple{Field::width - 5, Field::height / 2};
  SnakeController sc = SnakeController(true, dirs::LEFT, xy_snake, xy_apple);
  sc.SetScore(195);
  SnakeStates state = sc.SetState(SnakeStates::MOVING, dirs::NULL_DIR);
  EXPECT_EQ(state, SnakeStates::WIN);
}

TEST(S21SnakeTestController1, TestRandom1) {
  SnakeController sc = SnakeController();
  sc.SetState(SnakeStates::START, dirs::NULL_DIR);
  EXPECT_EQ(sc.GetState(), SnakeStates::MOVING);
}

TEST(S21SnakeTestController1, TestRandom2) {
  SnakeController sc = SnakeController();
  SnakeStates state = sc.SetState(SnakeStates::MOVING, dirs::NULL_DIR);
  EXPECT_EQ(state, SnakeStates::MOVING);
}

TEST(S21SnakeTestController1, TestRandom3) {
  SnakeController sc = SnakeController();
  SnakeStates state = sc.SetState(SnakeStates::MOVING, dirs::NULL_DIR);
  EXPECT_EQ(state, SnakeStates::MOVING);
}

TEST(S21SnakeTestController1, TestHighScore1) {
  SnakeController sc = SnakeController();
  sc.SetHighScore(100);
  sc.WriteHighScore();
  bool error{};
  char *path = S21GetLogFilePath(snake_log_file_name, &error);
  if (error) {
    throw std::runtime_error("snake log path error");
  }
  std::ifstream file(path, std::ios::in);
  free(path);
  std::string line{};
  if (file.is_open()) {
    std::getline(file, line);
    try {
      int score = std::stoi(line);
      size_t need_score{100};
      EXPECT_EQ(score, need_score);
      EXPECT_EQ(score, sc.GetHighScore());
    } catch (const std::invalid_argument &e) {
      throw std::runtime_error("incorrect highscore file");
    }
  }
}

TEST(S21SnakeTestController1, TestLevelUp1) {
  xy_pair xy_snake{Field::width - 4, Field::height / 2};
  xy_pair xy_apple{Field::width - 5, Field::height / 2};
  SnakeController sc = SnakeController(true, dirs::LEFT, xy_snake, xy_apple);
  int N = 4;
  sc.SetScore(N);
  size_t level = sc.GetLevel();
  sc.SetState(SnakeStates::MOVING, dirs::NULL_DIR);
  EXPECT_EQ(1, sc.GetLevel() - level);
  EXPECT_EQ(N + 1, sc.GetScore());
}

TEST(S21SnakeTestController1, TestShifting1) {
  xy_pair xy_snake{Field::width - 4, Field::height / 2};
  xy_pair xy_apple{Field::width - 5, Field::height / 2};
  SnakeController sc = SnakeController(true, dirs::LEFT, xy_snake, xy_apple);
  sc.SetScore(4);
  SnakeStates state = sc.SetState(SnakeStates::SHIFTING, dirs::UP);
  EXPECT_EQ(state, SnakeStates::MOVING);
}

TEST(S21SnakeTestController1, TestMoveColided1) {
  xy_pair xy_snake{Field::width - 4, Field::height / 2};
  xy_pair xy_apple{0, 0};
  SnakeController sc = SnakeController(true, dirs::LEFT, xy_snake, xy_apple);
  sc.SetScore(4);
  sc.SetState(SnakeStates::SHIFTING, dirs::UP);
  sc.SetState(SnakeStates::SHIFTING, dirs::RIGHT);
  SnakeStates state = sc.SetState(SnakeStates::SHIFTING, dirs::DOWN);
  EXPECT_EQ(state, SnakeStates::GAME_OVER);
}
