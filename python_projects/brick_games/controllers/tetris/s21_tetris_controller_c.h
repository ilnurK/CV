#ifndef S21_BRICK_GAME_TETRIS_CONTROLLER_C_H
#define S21_BRICK_GAME_TETRIS_CONTROLLER_C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../brick_game/tetris/s21_tetris_FSM.h"

typedef struct {
  S21TetrisFSM *fsm;
  size_t height;
  size_t width;
  size_t fig_len;
  char fig_symb;
  char field_symb_fill;
  char field_symb_fig;
} S21TetrisCController;

S21TetrisCController *InitTetrisController(S21TetrisError *error);
S21TetrisStates SetTetrisState(S21TetrisCController *tetris_controller,
                               const S21TetrisStates state, const dirs dir,
                               S21TetrisError *error);
char *GetFieldAt(S21TetrisCController *tetris_ctrl, const S21XYPair xy);
size_t GetTetrisScore(S21TetrisCController *tetris_ctrl);
size_t GetTetrisHighScore(S21TetrisCController *tetris_ctrl);
size_t GetTetrisLevel(S21TetrisCController *tetris_ctrl);
S21XYPair GetExtraInfoAt(S21TetrisCController *tetris_ctrl, const int i);
void SetTetrisScore(S21TetrisCController *tetris_ctrl, size_t val);
void WriteTetrisHighScore(S21TetrisCController *tetris_ctrl,
                          S21TetrisError *error);
void DeleteController(S21TetrisCController *tetris_ctrl);

#ifdef __cplusplus
}
#endif

#endif
