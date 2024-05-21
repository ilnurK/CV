#include "s21_tetris_controller.h"

S21TetrisController* InitTetrisController(S21TetrisError* error) {
  S21TetrisController* tetris_ctrl =
      (S21TetrisController*)calloc(1, sizeof(S21TetrisController));
  if (!tetris_ctrl) {
    *error = BAD_ALLOC;
  } else {
    tetris_ctrl->fsm = (S21TetrisFSM*)calloc(1, sizeof(S21TetrisFSM));
    if (!tetris_ctrl->fsm) {
      *error = BAD_ALLOC;
    } else {
      tetris_ctrl->height = FIELD_HEIGHT;
      tetris_ctrl->width = FIELD_WIDTH;
      tetris_ctrl->fig_len = FIG_LEN;
      tetris_ctrl->fig_symb = FIGURE_SYMBOL;
      tetris_ctrl->field_symb_empty = FIELD_SYMBOL_EMPTY;
      tetris_ctrl->field_symb_fill = FIELD_SYMBOL_FILLED;
      tetris_ctrl->fsm->highscore = InitTetrisHighScore(error);
    }
  }
  return tetris_ctrl;
}

S21TetrisStates SetTetrisState(S21TetrisController* tetris_ctrl,
                               const S21TetrisStates state, const S21Dirs dir,
                               S21TetrisError* error) {
  return SetFSMState(tetris_ctrl->fsm, state, dir, error);
}

size_t GetTetrisScore(S21TetrisController* tetris_ctrl) {
  return tetris_ctrl->fsm->score;
}

size_t GetTetrisHighScore(S21TetrisController* tetris_ctrl) {
  return tetris_ctrl->fsm->highscore;
}

size_t GetTetrisLevel(S21TetrisController* tetris_ctrl) {
  return tetris_ctrl->fsm->level;
}

char* GetFieldAt(S21TetrisController* tetris_ctrl, const S21XYPair xy) {
  return FieldAt(tetris_ctrl->fsm->field, xy);
}

void WriteTetrisHighScore(S21TetrisController* tetris_ctrl,
                          S21TetrisError* error) {
  WriteHighScore(tetris_ctrl->fsm, error);
}

void SetTetrisScore(S21TetrisController* tetris_ctrl, size_t val) {
  tetris_ctrl->fsm->score = val;
}

void DeleteController(S21TetrisController* tetris_ctrl) {
  DeleteFSM(tetris_ctrl->fsm);
  free(tetris_ctrl);
}
