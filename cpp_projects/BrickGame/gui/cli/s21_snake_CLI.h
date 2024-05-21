#ifndef S21_BRICK_GAME_VIEW_NCURSES_H
#define S21_BRICK_GAME_VIEW_NCURSES_H

#include <ncurses.h>

#include <chrono>
#include <list>
#include <map>
#include <thread>

#include "../../brick_game/snake/s21_snake_controller.h"
#include "s21_brick_game_CLI.h"

class SnakeViewCLI {
 private:
  s21::SnakeController sc_{};
  s21::GameStatus status_{};
  std::list<int> keys_list_{};
  int std_speed_{1000};
  size_t highscore_{sc_.GetHighScore()};

 private:
  std::map<int, s21::Keys> keys{
      {KEY_LEFT_, s21::Keys::LEFT},     {KEY_RIGHT_, s21::Keys::RIGHT},
      {KEY_UP_, s21::Keys::UP},         {KEY_DOWN_, s21::Keys::DOWN},
      {KEY_ACTION_, s21::Keys::ACTION}, {KEY_PAUSE_, s21::Keys::PAUSE},
      {KEY_QUIT_, s21::Keys::QUIT},     {KEY_NULL_, s21::Keys::NULL_KEY}};

 public:
  static void SnakeCLI(WINDOW* win);

 private:
  void Draw(WINDOW* win);
  void DrawCycle(WINDOW* win);
  void DrawHorizontalFrame(WINDOW* win);
  void DrawField(WINDOW* win);
  void DrawSideMenu(WINDOW* win);
};

#endif