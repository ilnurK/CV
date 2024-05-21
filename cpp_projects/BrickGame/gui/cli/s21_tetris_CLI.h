#ifndef S21_BRICK_GAME_TETRIS_NCURSES_H
#define S21_BRICK_GAME_TETRIS_NCURSES_H

#include "../../brick_game/tetris_c/s21_tetris_controller.h"
#include "s21_brick_game_CLI.h"

#define STANDART_SPEED 700

void TetrisCLI(WINDOW* tetris_win);
void DrawTetrisCycle(WINDOW* win, S21TetrisController* ctrl,
                     S21TetrisError* error);
S21TetrisStates KeyToState(int key, S21TetrisController* ctrl, int* key_counter,
                           S21TetrisError* error);
S21Dirs GetDir(int key, bool* flag_real_key);
void DrawHorizontalFrame(WINDOW* win, size_t y);
void DrawField(WINDOW* win, S21TetrisController* ctrl, size_t hscore,
               size_t level);
void DrawSideMenu(WINDOW* win, S21TetrisController* ctrl, size_t hscore,
                  size_t level);
void SetTimer(WINDOW* win, size_t level, size_t old_level, int* timer);
void ErrorHandler(WINDOW* win, S21TetrisError* error);

#endif