#ifndef S21_BRICK_GAME_TETRIS_FIELD_H
#define S21_BRICK_GAME_TETRIS_FIELD_H

#include <stdbool.h>
#include <stdlib.h>

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

#define FIELD_SYMBOL_EMPTY ' '
#define FIELD_SYMBOL_FILLED '$'

typedef enum { NULL_ERROR, BAD_ALLOC, PATH_ERROR } S21TetrisError;

typedef struct {
  int x;
  int y;
} S21XYPair;

typedef struct S21Line {
  char data[FIELD_WIDTH];
} S21Line;

typedef struct S21Field {
  S21Line* data[FIELD_HEIGHT];
  char symbol_empty;
  char symbol_fill;
} S21Field;

S21Field* InitField(S21TetrisError* error);
void LineFill(S21Line* line);
char* FieldAt(S21Field* field, const S21XYPair xy);
void DeleteField(S21Field* field);

#endif