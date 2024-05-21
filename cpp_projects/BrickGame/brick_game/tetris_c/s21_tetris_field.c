#include "s21_tetris_field.h"

S21Field* InitField(S21TetrisError* error) {
  S21Field* field = (S21Field*)calloc(1, sizeof(S21Field));
  if (!field) {
    *error = BAD_ALLOC;
  }
  for (size_t i = 0; i < FIELD_HEIGHT && *error == NULL_ERROR; i++) {
    S21Line* line = (S21Line*)calloc(1, sizeof(S21Line));
    if (line) {
      for (size_t j = 0; j < FIELD_WIDTH; j++) {
        line->data[j] = FIELD_SYMBOL_EMPTY;
      }
      field->data[i] = line;
    } else {
      *error = BAD_ALLOC;
      for (size_t k = 0; k < i; k++) {
        free(field->data[k]);
      }
      free(field);
      field = NULL;
    }
  }

  if (*error == NULL_ERROR) {
    field->symbol_empty = FIELD_SYMBOL_EMPTY;
    field->symbol_fill = FIELD_SYMBOL_FILLED;
  }
  return field;
}

void LineFill(S21Line* line) {
  for (size_t i = 0; i < FIELD_WIDTH; i++) {
    line->data[i] = FIELD_SYMBOL_EMPTY;
  }
}

char* FieldAt(S21Field* field, const S21XYPair xy) {
  char* find = NULL;
  bool x_state = xy.x < FIELD_WIDTH && xy.x >= 0;
  bool y_state = xy.y < FIELD_HEIGHT && xy.y >= 0;
  if (x_state && y_state && field) {
    find = &field->data[xy.y]->data[xy.x];
  }
  return find;
}

void DeleteField(S21Field* field) {
  for (size_t i = 0; i < FIELD_HEIGHT; i++) {
    free(field->data[i]);
  }
  free(field);
}
