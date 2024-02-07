#include "s21_3DViewer.h"

void AddIndices(indices_t *indices, int vertices_row, char *line,
                errors_e *err_e) {
  char *line_cor = LineCorrecter(line);

  char delim[] = " ";
  int indices_N = CountVerticesInSurface(line_cor, delim[0]);

  int *indices_row = NULL;
  int *first_cell = (int *)(indices->matrix + indices->rows);
  indices_row = first_cell + indices->recorded;

  int j = 0;
  if (indices_row) {
    indices_row[0] = indices_N;
    indices->recorded += indices_N + 1;
    char *token = strtok(line_cor, delim);
    while (!*err_e && token != NULL && j <= indices_N) {
      if (j == 0) {
        ;  // 'f'
      } else {
        int num = atoi(token);
        indices->max = (num > indices->max) ? num : indices->max;
        indices_row[j] = (num > 0) ? num : vertices_row + num + 1;

        *err_e = (num == 0)             ? SURFACE_INCORRECT
                 : (indices_row[j] < 1) ? MAX_IDX
                                        : *err_e;
      }
      token = strtok(NULL, delim);
      j++;
    }
    if (!*err_e) {
      indices->matrix[indices->cur_row++] = indices_row;
    }
  } else {
    *err_e = MEMORY_NA;
  }
}

char *LineCorrecter(char *line) {
  size_t len = strlen(line);
  int flag_find_num = 0, i = len - 1;
  while (!flag_find_num && i) {
    if (line[i] >= '0' && line[i] <= '9') {
      flag_find_num = 1;
    } else {
      i--;
    }
  }
  line[i + 1] = '\0';
  return line;
}

int CountVerticesInSurface(char *line, char delim) {
  int i = 1, count = 0, len = (int)strlen(line);
  while (i < len - 1) {
    if (line[i] == delim) {
      count++;
      if (line[i + 1] == delim) {
        i++;
      }
    }
    i++;
  }
  return count;
}

void FreeIndices(indices_t *indices) {
  if (indices->matrix) {
    free(indices->matrix);
    indices->matrix = NULL;
  }
  indices->rows = indices->cols = indices->cur_row = 0;
  indices->total = indices->max = indices->recorded = 0;
}
