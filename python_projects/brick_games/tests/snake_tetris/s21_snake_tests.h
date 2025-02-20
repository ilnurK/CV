#ifndef S21_BRICK_GAME_SNAKE_TESTS_H
#define S21_BRICK_GAME_SNAKE_TESTS_H

#include <gtest/gtest.h>

#include <fstream>

#include "../../brick_game/s21_brick_games_directions.h"
#include "../../brick_game/s21_brick_games_highscores.h"
#include "../../controllers/snake/s21_snake_controller.h"

using dirs = S21Directions;

template <typename T, typename U>
void ExpectPairEq(const std::pair<T, U> &actual,
                  const std::pair<T, U> &expected) {
  EXPECT_EQ(actual.first, expected.first);
  EXPECT_EQ(actual.second, expected.second);
}

#endif