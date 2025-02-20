#ifndef S21_BRICK_GAME_TETRIS_FIGURES_H
#define S21_BRICK_GAME_TETRIS_FIGURES_H

#ifdef __cplusplus
extern "C" {
#endif

#define FIG_LEN 4
#define FIGURE_SYMBOL '#'

#include "../s21_brick_games_directions.h"
#include "s21_tetris_field.h"

typedef enum {
  NULL_TYPE,
  BAR = 1,      // _ _ _ _
  LLSHAPE = 2,  // | _ _
  RLSHAPE = 3,  // _ _ |
  SQUARE = 4,   // =
  LZSHAPE = 5,  // - = _
  RZSHAPE = 6,  // _ = -
  TSHAPE = 7,   // _ | _
  LAST_FIGURE_TYPE
} S21FigureTypes;

typedef S21Directions dirs;

typedef struct {
  S21XYPair old_data[FIG_LEN];
  S21XYPair data[FIG_LEN];
  S21FigureTypes type;
  char symbol;
  dirs position;
} S21Figure;

S21Figure *InitFigure(S21TetrisError *error);
S21Figure *InitNeedFigure(S21FigureTypes type, int x, int y,
                          S21TetrisError *error);
S21FigureTypes GetRandomType();
int GetRandomX(S21FigureTypes type);
void DataCopy(S21Figure *figure, S21XYPair *data);

void InitShape(S21Figure *figure, int x, int y);
void InitBar(S21Figure *figure, int x, int y);
void InitLLShape(S21Figure *figure, int x, int y);
void InitRLShape(S21Figure *figure, int x, int y);
void InitSquare(S21Figure *figure, int x, int y);
void InitLZShape(S21Figure *figure, int x, int y);
void InitRZShape(S21Figure *figure, int x, int y);
void InitTShape(S21Figure *figure, int x, int y);

bool PutFigureOnField(S21Figure *figure, S21Field *field, bool attach);
void RemoveFigureLastPosFromField(S21Figure *figure, S21Field *field);
void BackupFigure(S21Figure *figure);
void RestoreFigure(S21Figure *figure);

#ifdef __cplusplus
}
#endif

#endif
