#include "s21_support.h"

int GetRandomNum(int min, int max) {
  std::random_device seed;
  std::mt19937 generator_eng(seed());
  std::uniform_int_distribution random_dist(min, max);
  return random_dist(generator_eng);
}
