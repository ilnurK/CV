#ifndef S21_BRICK_GAME_SNAKE_TESTS_H
#define S21_BRICK_GAME_SNAKE_TESTS_H

#include <gtest/gtest.h>

#include "../brick_game/snake/s21_snake_controller.h"

template <typename T, typename U>
void ExpectPairEq(const std::pair<T, U> &actual,
                  const std::pair<T, U> &expected) {
  EXPECT_EQ(actual.first, expected.first);
  EXPECT_EQ(actual.second, expected.second);
}

#endif