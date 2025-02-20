#include "s21_tetris_controller_c.h"

S21TetrisCController *InitTetrisController(S21TetrisError *error) {
  S21TetrisCController *tetris_ctrl =
      (S21TetrisCController *)calloc(1, sizeof(S21TetrisCController));
  if (!tetris_ctrl) {
    *error = BAD_ALLOC;
  } else {
    S21TetrisFSM *fsm = (S21TetrisFSM *)calloc(1, sizeof(S21TetrisFSM));
    if (!fsm) {
      *error = BAD_ALLOC;
    } else {
      tetris_ctrl->height = FIELD_HEIGHT;
      tetris_ctrl->width = FIELD_WIDTH;
      tetris_ctrl->fig_len = FIG_LEN;
      tetris_ctrl->fig_symb = FIGURE_SYMBOL;
      tetris_ctrl->field_symb_fig = FIGURE_SYMBOL;
      tetris_ctrl->field_symb_fill = FIELD_SYMBOL_FILLED;
      fsm->highscore = InitTetrisHighScore(error);
      fsm->score = 0;
      fsm->level = 1;
      fsm->field = InitField(error);
      fsm->cur_figure = InitFigure(error);
      fsm->next_figure = InitFigure(error);
      tetris_ctrl->fsm = fsm;
    }
  }
  return tetris_ctrl;
}

S21TetrisStates SetTetrisState(S21TetrisCController *tetris_ctrl,
                               const S21TetrisStates state, const dirs dir,
                               S21TetrisError *error) {
  S21TetrisStates state_out = NULL_STATE;
  if (tetris_ctrl && tetris_ctrl->fsm) {
    state_out = SetFSMState(tetris_ctrl->fsm, state, dir, error);
  }
  return state_out;
}

size_t GetTetrisScore(S21TetrisCController *tetris_ctrl) {
  return tetris_ctrl->fsm->score;
}

size_t GetTetrisHighScore(S21TetrisCController *tetris_ctrl) {
  return tetris_ctrl->fsm->highscore;
}

size_t GetTetrisLevel(S21TetrisCController *tetris_ctrl) {
  return tetris_ctrl->fsm->level;
}

char *GetFieldAt(S21TetrisCController *tetris_ctrl, const S21XYPair xy) {
  return FieldAt(tetris_ctrl->fsm->field, xy);
}

S21XYPair GetExtraInfoAt(S21TetrisCController *tetris_ctrl, const int i) {
  S21XYPair p = {0, 0};
  if (tetris_ctrl && tetris_ctrl->fsm) {
    if (tetris_ctrl->fsm->next_figure) {
      p = tetris_ctrl->fsm->next_figure->data[i];
    }
  }
  return p;
}

void WriteTetrisHighScore(S21TetrisCController *tetris_ctrl,
                          S21TetrisError *error) {
  WriteHighScore(tetris_ctrl->fsm, error);
}

void SetTetrisScore(S21TetrisCController *tetris_ctrl, size_t val) {
  tetris_ctrl->fsm->score = val;
  if (val > tetris_ctrl->fsm->highscore) {
    tetris_ctrl->fsm->highscore = val;
  }
}

void DeleteController(S21TetrisCController *tetris_ctrl) {
  if (tetris_ctrl) {
    DeleteFSM(tetris_ctrl->fsm);
    free(tetris_ctrl);
  }
}
