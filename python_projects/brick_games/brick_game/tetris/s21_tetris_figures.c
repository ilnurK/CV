#include "s21_tetris_figures.h"

S21Figure *InitFigure(S21TetrisError *error) {
  S21FigureTypes type = GetRandomType();
  int x = GetRandomX(type), y = -1;
  return InitNeedFigure(type, x, y, error);
}

S21Figure *InitNeedFigure(S21FigureTypes type, int x, int y,
                          S21TetrisError *error) {
  S21Figure *figure = (S21Figure *)calloc(1, sizeof(S21Figure));
  if (figure) {
    figure->symbol = FIGURE_SYMBOL;
    figure->position = UP;
    figure->type = type;
    InitShape(figure, x, y);
  } else {
    *error = BAD_ALLOC;
  }
  return figure;
}

S21FigureTypes GetRandomType() {
  int rand_type = rand() % (LAST_FIGURE_TYPE - 1);
  S21FigureTypes type = (S21FigureTypes)(rand_type + 1);
  return type;
}

int GetRandomX(S21FigureTypes type) {
  int offset = 3;
  if (type == BAR) {
    offset = 4;
  } else if (type == SQUARE) {
    offset = 2;
  }
  return rand() % (FIELD_WIDTH + 1 - offset);
}

void InitShape(S21Figure *figure, int x, int y) {
  S21FigureTypes ftype = figure->type;
  if (ftype == BAR) {
    InitBar(figure, x, y);
  } else if (ftype == LLSHAPE) {
    InitLLShape(figure, x, y);
  } else if (ftype == RLSHAPE) {
    InitRLShape(figure, x, y);
  } else if (ftype == SQUARE) {
    InitSquare(figure, x, y);
  } else if (ftype == LZSHAPE) {
    InitLZShape(figure, x, y);
  } else if (ftype == RZSHAPE) {
    InitRZShape(figure, x, y);
  } else if (ftype == TSHAPE) {
    InitTShape(figure, x, y);
  }
}

void InitBar(S21Figure *figure, int x, int y) {
  for (int i = 0; i < FIG_LEN; i++) {
    S21XYPair xy = {x + i, y};
    figure->data[i] = xy;
  }
}

void DataCopy(S21Figure *figure, S21XYPair *data) {
  for (size_t i = 0; i < FIG_LEN; i++) {
    figure->data[i] = data[i];
  }
}

void InitLLShape(S21Figure *figure, int x, int y) {
  S21XYPair data[FIG_LEN] = {{x, y - 1}, {x, y}, {x + 1, y}, {x + 2, y}};
  DataCopy(figure, data);
}

void InitRLShape(S21Figure *figure, int x, int y) {
  S21XYPair data[FIG_LEN] = {{x, y}, {x + 1, y}, {x + 2, y}, {x + 2, y - 1}};
  DataCopy(figure, data);
}

void InitSquare(S21Figure *figure, int x, int y) {
  S21XYPair data[FIG_LEN] = {{x, y}, {x, y - 1}, {x + 1, y - 1}, {x + 1, y}};
  DataCopy(figure, data);
}

void InitLZShape(S21Figure *figure, int x, int y) {
  S21XYPair data[FIG_LEN] = {
      {x, y - 1}, {x + 1, y - 1}, {x + 1, y}, {x + 2, y}};
  DataCopy(figure, data);
}

void InitRZShape(S21Figure *figure, int x, int y) {
  S21XYPair data[FIG_LEN] = {
      {x, y}, {x + 1, y}, {x + 1, y - 1}, {x + 2, y - 1}};

  DataCopy(figure, data);
}

void InitTShape(S21Figure *figure, int x, int y) {
  S21XYPair data[FIG_LEN] = {{x, y}, {x + 1, y}, {x + 1, y - 1}, {x + 2, y}};
  DataCopy(figure, data);
}

bool PutFigureOnField(S21Figure *figure, S21Field *field, bool attach) {
  size_t part_putted = 0;
  for (size_t i = 0; i < FIG_LEN; i++) {
    char *find =
        FieldAt(field, (attach) ? figure->old_data[i] : figure->data[i]);
    if (find) {
      *find = (attach) ? FIELD_SYMBOL_FILLED : FIGURE_SYMBOL;
      part_putted++;
    }
  }
  return part_putted == FIG_LEN;
}

void RemoveFigureLastPosFromField(S21Figure *figure, S21Field *field) {
  for (size_t i = 0; i < FIG_LEN; i++) {
    char *find = FieldAt(field, figure->old_data[i]);
    if (find && *find != field->symbol_fill) {
      *find = FIELD_SYMBOL_EMPTY;
    }
  }
}

void BackupFigure(S21Figure *figure) {
  for (size_t i = 0; i < FIG_LEN; i++) {
    figure->old_data[i] = figure->data[i];
  }
}

void RestoreFigure(S21Figure *figure) {
  for (size_t i = 0; i < FIG_LEN; i++) {
    figure->data[i] = figure->old_data[i];
  }
}
