#include "s21_3DViewer.h"

void AddVertices(vertices_t *vertices, char *line, errors_e *err_e) {
  double x = 0, y = 0, z = 0;
  int i = vertices->cur_row;
  if (sscanf(line, "v %lf %lf %lf", &x, &y, &z) == 3) {
    vertices->matrix[i][0] = x;
    vertices->matrix[i][1] = y;
    vertices->matrix[i][2] = z;
    CheckEdgeVal(x, &vertices->max->x, &vertices->max->x_);
    CheckEdgeVal(y, &vertices->max->y, &vertices->max->y_);
    CheckEdgeVal(z, &vertices->max->z, &vertices->max->z_);
    vertices->cur_row += 1;
  } else {
    *err_e = VERTEX_INCORRECT;
  }
}

void CheckEdgeVal(double num, double *max, double *min) {
  if (num > *max) {
    *max = num;
  } else if (num < *min) {
    *min = num;
  }
}

void FreeVertices(vertices_t *vertices) {
  if (vertices->matrix) {
    free(vertices->matrix);
    vertices->matrix = NULL;
  }
  vertices->rows = vertices->cols = vertices->cur_row = 0;
  if (vertices->max) {
    vertices->max->x = vertices->max->x_ = 0;
    vertices->max->y = vertices->max->y_ = 0;
    vertices->max->z = vertices->max->z_ = 0;
  }
}
