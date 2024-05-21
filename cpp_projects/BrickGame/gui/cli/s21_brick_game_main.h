#ifndef S21_BRICK_GAME_MAIN_CLI_H
#define S21_BRICK_GAME_MAIN_CLI_H

#define MENU_SNAKE 1
#define MENU_TETRIS 2
#define MENU_EXIT 3

#include "s21_brick_game_CLI.h"

extern "C" {
#include "s21_tetris_CLI.h"
}

#include "s21_snake_CLI.h"

void MenuDisplay(WINDOW *menu_win, int highlight);
void ChooseChoice(int choice, int *highlight, bool *flag_not_quit);

#endif