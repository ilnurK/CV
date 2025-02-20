#include "s21_tetris_FSM.h"

S21TetrisStates SetFSMState(S21TetrisFSM *fsm, const S21TetrisStates state,
                            const dirs dir, S21TetrisError *error) {
  return StableFSM(fsm, state, dir, error);
}

S21TetrisStates StableFSM(S21TetrisFSM *fsm, const S21TetrisStates state,
                          const dirs dir_in, S21TetrisError *error) {
  bool stable = false;
  fsm->state = state;
  dirs dir = dir_in;
  while (!stable) {
    if (*error == NULL_ERROR) {
      stable = FSM(fsm, &dir, error);
    } else {
      fsm->state = GAME_OVER;
      stable = 1;
    }
  }
  return fsm->state;
}

bool FSM(S21TetrisFSM *fsm, dirs *dir, S21TetrisError *error) {
  bool stable = true;
  if (*dir && *dir > NULL_DIR && *dir <= ACTION) {
    fsm->state = SHIFTING;
  }

  if (fsm->state == SHIFTING) {
    stable = ShiftingHandler(fsm, *dir);
    *dir = NULL_DIR;
  } else if (fsm->state == MOVING) {
    stable = Moving(fsm);
  } else if (fsm->state == SPAWN) {
    stable = Spawn(fsm, error);
  } else if (fsm->state == ATTACHING) {
    stable = Attaching(fsm);
  } else if (fsm->state == START) {
    stable = Start(fsm);
  } else if (fsm->state == GAME_OVER) {
    stable = true;
    if (fsm->score > fsm->highscore) {
      fsm->highscore = fsm->score;
    }
  }
  return stable;
}

bool Moving(S21TetrisFSM *fsm) {
  fsm->shifts_counter = 0;
  bool stable = true;
  BackupFigure(fsm->cur_figure);
  if (IsAttachY(fsm)) {
    fsm->state = ATTACHING;
    stable = false;
  } else {
    bool attach = false;
    RemoveFigureLastPosFromField(fsm->cur_figure, fsm->field);
    PutFigureOnField(fsm->cur_figure, fsm->field, attach);
  }
  return stable;
}

bool IsAttachY(S21TetrisFSM *fsm) {
  bool touch = false;
  for (size_t i = 0; i < FIG_LEN; i++) {
    S21XYPair *xy = &fsm->cur_figure->data[i];
    xy->y += 1;
    char *find = FieldAt(fsm->field, *xy);
    if (xy->y == FIELD_HEIGHT || (find && *find == fsm->field->symbol_fill)) {
      touch = true;
    }
  }
  return touch;
}

bool ShiftingHandler(S21TetrisFSM *fsm, const dirs dir) {
  bool stable = true;
  if (fsm->shifts_counter++ < MAX_SHIFTS) {
    if (dir == LEFT || dir == RIGHT) {
      stable = Shifting(fsm, dir);

    } else if (dir == DOWN) {
      stable = Falling(fsm);
    } else if (dir == ACTION) {
      stable = Rotating(fsm);
    }
  } else {
    fsm->state = MOVING;
    stable = false;
  }
  return stable;
}

bool Shifting(S21TetrisFSM *fsm, const dirs dir) {
  bool stable = true;
  fsm->state = MOVING;
  BackupFigure(fsm->cur_figure);

  if (IsBorders(fsm, dir)) {
    RestoreFigure(fsm->cur_figure);
    stable = false;
  }

  bool attach = false;
  RemoveFigureLastPosFromField(fsm->cur_figure, fsm->field);
  PutFigureOnField(fsm->cur_figure, fsm->field, attach);
  return stable;
}

bool IsBorders(S21TetrisFSM *fsm, const dirs dir) {
  bool touch = false;
  for (size_t i = 0; i < FIG_LEN && !touch; i++) {
    S21XYPair *xy = &fsm->cur_figure->data[i];
    if (dir == RIGHT) {
      xy->x += 1;
    } else if (dir == LEFT) {
      xy->x -= 1;
    }
    char *find = FieldAt(fsm->field, *xy);
    if (xy->x > FIELD_WIDTH - 1 || xy->x < 0 ||
        (find && *find == FIELD_SYMBOL_FILLED)) {
      touch = true;
    }
  }
  return touch;
}

bool Falling(S21TetrisFSM *fsm) {
  bool stable = false, in_cycle = false;
  BackupFigure(fsm->cur_figure);
  RemoveFigureLastPosFromField(fsm->cur_figure, fsm->field);
  while (!IsAttachY(fsm)) {
    in_cycle = true;
  }
  if (in_cycle) {
    for (size_t i = 0; i < FIG_LEN; i++) {
      fsm->cur_figure->data[i].y -= 1;
    }
    BackupFigure(fsm->cur_figure);
  }
  fsm->state = ATTACHING;
  return stable;
}

bool Rotating(S21TetrisFSM *fsm) {
  bool stable = true;
  if (fsm->cur_figure->type != SQUARE) {
    BackupFigure(fsm->cur_figure);
    if (TryRotate(fsm)) {
      bool attach = false;
      RemoveFigureLastPosFromField(fsm->cur_figure, fsm->field);
      PutFigureOnField(fsm->cur_figure, fsm->field, attach);
    } else {
      RestoreFigure(fsm->cur_figure);
      stable = false;
    }
  }
  fsm->state = MOVING;
  return stable;
}

bool TryRotate(S21TetrisFSM *fsm) {
  bool rotated = true;
  S21XYPair axis = fsm->cur_figure->data[1];
  S21FigureTypes type = fsm->cur_figure->type;
  if (type == LLSHAPE || type == LZSHAPE) {
    axis = fsm->cur_figure->data[2];
  }
  S21XYPair axis_rotated = {-axis.y, axis.x};
  int offset_x = axis.x - axis_rotated.x;
  int offset_y = axis.y - axis_rotated.y;
  for (size_t i = 0; i < FIG_LEN && rotated; i++) {
    int temp_x = fsm->cur_figure->data[i].x;
    fsm->cur_figure->data[i].x = -fsm->cur_figure->data[i].y + offset_x;
    fsm->cur_figure->data[i].y = temp_x + offset_y;
    if (fsm->cur_figure->data[i].y > 0) {
      char *find = FieldAt(fsm->field, fsm->cur_figure->data[i]);
      if (!find || *find == fsm->field->symbol_fill) {
        rotated = false;
      }
    }
  }
  return rotated;
}

bool Spawn(S21TetrisFSM *fsm, S21TetrisError *error) {
  bool stable = false;
  free(fsm->cur_figure);
  fsm->cur_figure = fsm->next_figure;
  fsm->next_figure = InitFigure(error);
  fsm->state = MOVING;
  return stable;
}

bool Attaching(S21TetrisFSM *fsm) {
  bool stable = false, attach = true;
  if (PutFigureOnField(fsm->cur_figure, fsm->field, attach)) {
    fsm->score += CheckLines(fsm);
    if (fsm->level < MAX_LEVEL) {
      fsm->level = fsm->score / LEVEL_COEF + 1;
      fsm->level = (fsm->level > MAX_LEVEL) ? MAX_LEVEL : fsm->level;
    }
    fsm->state = SPAWN;
  } else {
    fsm->state = GAME_OVER;
  }
  return stable;
}

size_t CheckLines(S21TetrisFSM *fsm) {
  size_t score_type = 0, score_add = 0;
  for (size_t i = 0; i < FIG_LEN; i++) {
    const size_t cur_y = (size_t)fsm->cur_figure->old_data[i].y;
    if (CheckLine(fsm, cur_y)) {
      DeleteLine(fsm, cur_y);
      score_type++;
    }
  }

  if (score_type == 1) {
    score_add = 100;
  } else if (score_type == 2) {
    score_add = 300;
  } else if (score_type == 3) {
    score_add = 700;
  } else if (score_type == 4) {
    score_add = 1500;
  }
  return score_add;
}

bool CheckLine(S21TetrisFSM *fsm, const size_t y) {
  bool is_filled = true;
  int i = 0;
  while (i < FIELD_WIDTH && is_filled) {
    S21XYPair xy = {i, (int)y};
    char *find = FieldAt(fsm->field, xy);
    if (find && *find == fsm->field->symbol_empty) {
      is_filled = false;
    }
    i++;
  }
  return i == FIELD_WIDTH && is_filled;
}

void DeleteLine(S21TetrisFSM *fsm, const size_t y) {
  size_t i = y;
  S21Line *temp = fsm->field->data[y];
  while (i) {
    fsm->field->data[i] = fsm->field->data[i - 1];
    i--;
  }
  fsm->field->data[0] = temp;
  LineFill(fsm->field->data[0]);
}

bool Start(S21TetrisFSM *fsm) {
  srand((unsigned int)time(NULL) * 1e6);
  bool stable = true;
  fsm->shifts_counter = 0;
  fsm->state = MOVING;
  fsm->level = 1;
  fsm->score = 0;
  return stable;
}

size_t InitTetrisHighScore(S21TetrisError *error) {
  bool is_creating_error = false;
  size_t hscore = S21InitHighScore(tetris_log_file_name, &is_creating_error);
  if (is_creating_error) {
    *error = PATH_ERROR;
  }
  return hscore;
}

void WriteHighScore(S21TetrisFSM *fsm, S21TetrisError *error) {
  bool is_writing_error =
      S21WriteHighScore(tetris_log_file_name, fsm->highscore);
  if (is_writing_error) {
    *error = PATH_ERROR;
  }
}

void DeleteFSM(S21TetrisFSM *fsm) {
  if (fsm) {
    free(fsm->next_figure);
    free(fsm->cur_figure);
    DeleteField(fsm->field);
    free(fsm);
  }
}
