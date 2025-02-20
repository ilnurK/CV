#ifndef S21_BRICK_GAME_MAIN_CLI_H
#define S21_BRICK_GAME_MAIN_CLI_H

#define MENU_SNAKE 1
#define MENU_TETRIS 2
#define MENU_RACE 3
#define MENU_EXIT 4

#include <memory>
#include <string>

#include "s21_cli_view.h"

namespace s21 {

class BrickGamesNcurses {
 private:
  WINDOW *menu_win_;
  int win_y_{22};
  int win_x_{25};
  int sub_y_{5};
  int sub_x_{5};
  int choice_{1};
  int highlight_{1};
  bool is_quit_{false};

 private:
  void ShowMenu();
  void ChooseGame();

 public:
  void Menu();
};
}  // namespace s21

#endif