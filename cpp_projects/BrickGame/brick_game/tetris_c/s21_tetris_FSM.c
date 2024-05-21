#include "s21_tetris_FSM.h"

#include "s21_tetris_support.h"

S21TetrisStates SetFSMState(S21TetrisFSM* fsm, const S21TetrisStates state,
                            const S21Dirs dir, S21TetrisError* error) {
  return StableFSM(fsm, state, dir, error);
}

S21TetrisStates StableFSM(S21TetrisFSM* fsm, const S21TetrisStates state,
                          const S21Dirs dir, S21TetrisError* error) {
  bool stable = false;
  S21TetrisStates cur_state = state;
  while (!stable) {
    if (*error == NULL_ERROR) {
      stable = FSM(fsm, &cur_state, dir, error);
    } else {
      stable = 1;
    }
  }
  return cur_state;
}

bool FSM(S21TetrisFSM* fsm, S21TetrisStates* cur_state, const S21Dirs dir,
         S21TetrisError* error) {
  bool stable = true;
  if (*cur_state == MOVING) {
    stable = Moving(fsm, cur_state);
  } else if (*cur_state == SHIFTING) {
    stable = ShiftingHandler(fsm, cur_state, dir);
  } else if (*cur_state == SPAWN) {
    stable = Spawn(fsm, cur_state, error);
  } else if (*cur_state == ATTACHING) {
    stable = Attaching(fsm, cur_state);
  } else if (*cur_state == START) {
    stable = Start(fsm, cur_state, error);
  } else if (*cur_state == GAME_OVER) {
    stable = true;
  }
  return stable;
}

bool Moving(S21TetrisFSM* fsm, S21TetrisStates* cur_state) {
  fsm->shifts_counter = 0;
  bool stable = true;
  BackupFigure(fsm->cur_figure);
  if (IsAttachY(fsm)) {
    *cur_state = ATTACHING;
    stable = false;
  } else {
    bool attach = false;
    RemoveFigureLastPosFromField(fsm->cur_figure, fsm->field);
    PutFigureOnField(fsm->cur_figure, fsm->field, attach);
  }
  return stable;
}

bool IsAttachY(S21TetrisFSM* fsm) {
  bool touch = false;
  for (size_t i = 0; i < FIG_LEN; i++) {
    S21XYPair* xy = &fsm->cur_figure->data[i];
    xy->y += 1;
    char* find = FieldAt(fsm->field, *xy);
    if (xy->y == FIELD_HEIGHT || (find && *find == fsm->field->symbol_fill)) {
      touch = true;
    }
  }
  return touch;
}

bool ShiftingHandler(S21TetrisFSM* fsm, S21TetrisStates* cur_state,
                     const S21Dirs dir) {
  bool stable = true;
  if (fsm->shifts_counter++ < MAX_SHIFTS) {
    if (dir == LEFT || dir == RIGHT) {
      stable = Shifting(fsm, cur_state, dir);

    } else if (dir == DOWN) {
      stable = Falling(fsm, cur_state);
    } else if (dir == ACTION) {
      stable = Rotating(fsm, cur_state);
    }
  } else {
    *cur_state = MOVING;
    stable = false;
  }
  return stable;
}

bool Shifting(S21TetrisFSM* fsm, S21TetrisStates* cur_state,
              const S21Dirs dir) {
  bool stable = true;
  *cur_state = MOVING;
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

bool IsBorders(S21TetrisFSM* fsm, const S21Dirs dir) {
  bool touch = false;
  for (size_t i = 0; i < FIG_LEN && !touch; i++) {
    S21XYPair* xy = &fsm->cur_figure->data[i];
    if (dir == RIGHT) {
      xy->x += 1;
    } else if (dir == LEFT) {
      xy->x -= 1;
    }
    char* find = FieldAt(fsm->field, *xy);
    if (xy->x > FIELD_WIDTH - 1 || xy->x < 0 ||
        (find && *find == FIELD_SYMBOL_FILLED)) {
      touch = true;
    }
  }
  return touch;
}

bool Falling(S21TetrisFSM* fsm, S21TetrisStates* cur_state) {
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
  *cur_state = ATTACHING;
  return stable;
}

bool Rotating(S21TetrisFSM* fsm, S21TetrisStates* cur_state) {
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
  *cur_state = MOVING;
  return stable;
}

bool TryRotate(S21TetrisFSM* fsm) {
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
      char* find = FieldAt(fsm->field, fsm->cur_figure->data[i]);
      if (!find || *find == fsm->field->symbol_fill) {
        rotated = false;
      }
    }
  }
  return rotated;
}

bool Spawn(S21TetrisFSM* fsm, S21TetrisStates* cur_state,
           S21TetrisError* error) {
  bool stable = true;
  free(fsm->cur_figure);
  fsm->cur_figure = fsm->next_figure;
  fsm->next_figure = InitFigure(error);
  *cur_state = MOVING;
  stable = false;
  return stable;
}

bool Attaching(S21TetrisFSM* fsm, S21TetrisStates* cur_state) {
  bool stable = false, attach = true;
  if (PutFigureOnField(fsm->cur_figure, fsm->field, attach)) {
    fsm->score += CheckLines(fsm);
    if (fsm->level < MAX_LEVEL) {
      fsm->level = fsm->score / LEVEL_COEF + 1;
      fsm->level = (fsm->level > MAX_LEVEL) ? MAX_LEVEL : fsm->level;
    }
    *cur_state = SPAWN;
  } else {
    *cur_state = GAME_OVER;
  }
  return stable;
}

size_t CheckLines(S21TetrisFSM* fsm) {
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

bool CheckLine(S21TetrisFSM* fsm, const size_t y) {
  bool is_filled = true;
  int i = 0;
  while (i < FIELD_WIDTH && is_filled) {
    S21XYPair xy = {i, (int)y};
    char* find = FieldAt(fsm->field, xy);
    if (find && *find == fsm->field->symbol_empty) {
      is_filled = false;
    }
    i++;
  }
  return i == FIELD_WIDTH && is_filled;
}

void DeleteLine(S21TetrisFSM* fsm, const size_t y) {
  size_t i = y;
  S21Line* temp = fsm->field->data[y];
  while (i) {
    fsm->field->data[i] = fsm->field->data[i - 1];
    i--;
  }
  fsm->field->data[0] = temp;
  LineFill(fsm->field->data[0]);
}

bool Start(S21TetrisFSM* fsm, S21TetrisStates* cur_state,
           S21TetrisError* error) {
  bool stable = true;
  fsm->field = InitField(error);
  fsm->cur_figure = InitFigure(error);
  fsm->next_figure = InitFigure(error);
  fsm->shifts_counter = 0;
  if (*error == NULL_ERROR) {
    *cur_state = MOVING;
    stable = false;
  }
  return stable;
}

size_t InitTetrisHighScore(S21TetrisError* error) {
  size_t highscore = 0;
  FILE* file = NULL;
  char* path = GetHighscorePath(error);
  if (*error == NULL_ERROR) {
    file = fopen(path, "r");
    if (file) {
      char text[128];
      while (fgets(text, 128, file)) {
        ;
      }
      fclose(file);
      highscore = (size_t)atoi(text);
    }
  }
  free(path);
  return highscore;
}

void WriteHighScore(S21TetrisFSM* fsm, S21TetrisError* error) {
  size_t score = fsm->score;
  if (score > fsm->highscore) {
    fsm->highscore = score;
    FILE* file = NULL;
    char* path = GetHighscorePath(error);
    if (path && *error == NULL_ERROR) {
      file = fopen(path, "w");
    }
    if (file && path) {
      fprintf(file, "%lu", fsm->highscore);
      fclose(file);
    } else {
      *error = PATH_ERROR;
    }
    free(path);
  }
}

void DeleteFSM(S21TetrisFSM* fsm) {
  free(fsm->next_figure);
  free(fsm->cur_figure);
  DeleteField(fsm->field);
  free(fsm);
}
