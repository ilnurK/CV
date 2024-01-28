#include "s21_3DViewer.h"

int TryOpenFile(const char *filename, FILE **file) {
  *file = fopen(filename, "r");
  return (*file != NULL) ? 1 : 0;
}

void GetMatrices(FILE *file, vertices_t *vertices, indices_t *indices,
                 errors_e *err_e) {
  CountElems(file, &vertices->rows, &indices->rows, &indices->total, err_e);
  if (!*err_e) {
    vertices->cols = 3, indices->max = 0;
    vertices->cur_row = indices->cur_row = indices->recorded = 0;

    vertices->matrix = InitVertices(vertices->rows, vertices->cols, err_e);
    indices->matrix = InitIndices(indices->rows, indices->total, err_e);
    values_t max_values = {};
    vertices->max = &max_values;
  }
  FILE *f = fopen("../models/one_million.obj", "r");
#pragma omp parallel sections
  {
#pragma omp section
      {if (!*err_e){FileParseV(f, vertices, err_e);
}
}

#pragma omp section
{
  if (!*err_e) {
    FileParseI(file, indices, err_e);
  }
}
}

(file) ? fclose(file) : 0;

if (!*err_e) {
  MatrixCenteringAndNormalization(vertices);
} else {
  FreeVertices(vertices);
  FreeIndices(indices);
}
}

void CountElems(FILE *file, int *rows_v, int *rows_i, int *total_v,
                errors_e *err_e) {
  char *line = NULL;
  char space = ' ';
  size_t len = 0;
  while (getline(&line, &len, file) != EOF) {
    char *ptr = line;
    while (*ptr == space) {
      ptr++;
    }
    if (ptr[0] == 'v' && ptr[1] == space) {
      *rows_v += 1;
    } else if (ptr[0] == 'f' && ptr[1] == space) {
      *total_v += CountVerticesInSurface(ptr, space);
      *rows_i += 1;
    }
  }
  (line) ? free(line) : 0;
  *err_e = (!*rows_v || !*rows_i) ? EMPTY_FILE : *err_e;
  fseek(file, 0, SEEK_SET);
}

double **InitVertices(int rows, int cols, errors_e *err_e) {
  double **M = NULL;
  if (rows) {
    M = (double **)malloc(rows * sizeof(double *) +
                          rows * cols * sizeof(double));
  }
  if (M) {
    double *first_cell = (double *)(M + rows);
    for (int i = 0; i < rows; i++) {
      M[i] = first_cell + i * cols;
    }
  } else {
    *err_e = MEMORY_NA;
  }
  return M;
}

int **InitIndices(int rows, int total, errors_e *err_e) {
  int **M = NULL;
  if (rows) {
    M = (int **)malloc(rows * sizeof(int *) + (total + rows) * sizeof(int));
  }
  if (!M) {
    *err_e = MEMORY_NA;
  }
  return M;
}

void FileParseV(FILE *file, vertices_t *vertices, errors_e *err_e) {
  char *line = NULL;
  size_t len = 0;
  char space = ' ';
  while (getline(&line, &len, file) != EOF && !*err_e) {
    char *ptr = line;
    while (*ptr == space) {
      ptr++;
    }
    if (ptr && len > 1) {
      if (ptr[0] == 'v' && ptr[1] == space) {
        AddVertices(vertices, ptr, err_e);
      }
    }
  }
  (line) ? free(line) : 0;
  // *err_e = (indices->max > vertices->cur_row) ? MAX_IDX : *err_e;
}

void FileParseI(FILE *file, indices_t *indices, errors_e *err_e) {
  char *line = NULL;
  size_t len = 0;
  char space = ' ';
  while (getline(&line, &len, file) != EOF && !*err_e) {
    char *ptr = line;
    while (*ptr == space) {
      ptr++;
    }
    if (ptr && len > 1) {
      if (ptr[0] == 'f' && ptr[1] == space) {
        AddIndices(indices, 0, ptr, err_e);
      }
    }
  }
  (line) ? free(line) : 0;
  // *err_e = (indices->max > vertices->cur_row) ? MAX_IDX : *err_e;
}

void MatrixCenteringAndNormalization(vertices_t *vertices) {
  double x_shift = 0 - (vertices->max->x - fabs(vertices->max->x_)) / 2;
  double y_shift = 0 - (vertices->max->y - fabs(vertices->max->y_)) / 2;
  double z_shift = 0 - (vertices->max->z - fabs(vertices->max->z_)) / 2;
  double max = GetEdgeMax(vertices->max);
  double coef = max * 1.1;
  for (int i = 0; i < vertices->rows; i++) {
    for (int j = 0; j < vertices->cols; j++) {
      if (j == 0) {
        vertices->matrix[i][j] += x_shift;
      } else if (j == 1) {
        vertices->matrix[i][j] += y_shift;
      } else if (j == 2) {
        vertices->matrix[i][j] += z_shift;
      }
      vertices->matrix[i][j] /= (max > 1) ? coef : 1;
    }
  }
}

double GetEdgeMax(values_t *max_values) {
  double max = 0;
  double values[] = {max_values->x_, max_values->x,  max_values->y_,
                     max_values->y,  max_values->z_, max_values->z};
  for (int i = 0; i < 6; i++) {
    max = (fabs(values[i]) > max) ? fabs(values[i]) : max;
  }
  return max;
}

// /*
int main() {
  FILE *f = NULL;
  // const char *fname = "../models/cube.obj";
  // const char *fname = "../models/Kalashnikov.obj";

  // const char *fname = "../models/cubecarcas.obj";
  // const char *fname = "../models/trumpet.obj";
  // const char *fname = "../models/glass.obj";

  // const char *fname = "../models/facet_that_not_exist.obj";
  // const char *fname = "../models/pyramid.obj";
  // const char *fname = "../models/bicycle.obj";
  // const char *fname = "../models/City.obj";
  const char *fname = "../models/one_million.obj";
  // const char *fname = "../models/invert_pyramid.obj";
  // const char *fname = "../models/skull.obj";

  if (TryOpenFile(fname, &f)) {
    vertices_t vertices = {};
    indices_t indices = {};
    errors_e err = 0;
    GetMatrices(f, &vertices, &indices, &err);
    printf("%s\n", ErrorHandle(err));
    printf("%d ", indices.max);
    printf("%d \n", vertices.rows);

    // for (int i = 0; i < vertices.rows; i++) {
    //   for (int j = 0; j < vertices.cols; j++) {
    //     printf("%10lf ", vertices.matrix[i][j]);
    //   }
    //   putchar('\n');
    // }
    // for (int i = 0; i < indices.rows; i++) {
    //   indices.cols = indices.matrix[i][0];
    //   for (int j = 1; j <= indices.cols; j++) {
    //     printf("%d ", indices.matrix[i][j]);
    //   }
    //   putchar('\n');
    // }

    // for (int i = 0; i < indices.rows; i++) {
    //   indices.cols = indices.matrix[i][0];
    //   for (int j = 1; j <= indices.cols; j++) {
    //     printf("%lf ", vertices.matrix[indices.matrix[i][j] - 1][0]);
    //     printf("%lf ", vertices.matrix[indices.matrix[i][j] - 1][1]);
    //     printf("%lf ", vertices.matrix[indices.matrix[i][j] - 1][2]);
    //     putchar('\n');
    //   }
    // }

    FreeVertices(&vertices);
    FreeIndices(&indices);
  }
  return 0;
}
// */