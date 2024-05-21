#ifndef S21_BRICK_GAME_TETRIS_CONTROLLER_H
#define S21_BRICK_GAME_TETRIS_CONTROLLER_H

#include "s21_tetris_FSM.h"

typedef struct S21TetrisController {
  S21TetrisFSM* fsm;
  size_t height;
  size_t width;
  size_t fig_len;
  char fig_symb;
  char field_symb_empty;
  char field_symb_fill;
} S21TetrisController;

S21TetrisController* InitTetrisController(S21TetrisError* error);
S21TetrisStates SetTetrisState(S21TetrisController* tetris_controller,
                               const S21TetrisStates state, const S21Dirs dir,
                               S21TetrisError* error);
char* GetFieldAt(S21TetrisController* tetris_ctrl, const S21XYPair xy);
size_t GetTetrisScore(S21TetrisController* tetris_ctrl);
size_t GetTetrisHighScore(S21TetrisController* tetris_ctrl);
size_t GetTetrisLevel(S21TetrisController* tetris_ctrl);
void SetTetrisScore(S21TetrisController* tetris_ctrl, size_t val);
void WriteTetrisHighScore(S21TetrisController* tetris_ctrl,
                          S21TetrisError* error);
void DeleteController(S21TetrisController* tetris_ctrl);

#endif
