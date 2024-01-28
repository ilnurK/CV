#ifndef S21_3DVIEWER
#define S21_3DVIEWER

#define DIVIDER 1000
#define _GNU_SOURCE

#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  ALL_OK = 0,
  INVALID_FILE,
  VERTEX_INCORRECT,
  SURFACE_INCORRECT,
  EMPTY_FILE,
  MAX_IDX,
  MEMORY_NA,
  CONFIGFILE_ERR
} errors_e;

typedef struct {
  double moveX;
  double moveY;
  double moveZ;
  double rotateX;
  double rotateY;
  double rotateZ;
  double scale;
} sliders_t;

typedef struct {
  double x_;
  double x;
  double y_;
  double y;
  double z_;
  double z;
} values_t;

typedef struct {
  double **matrix;
  int rows;
  int cols;
  int cur_row;
  values_t *max;
} vertices_t;

typedef struct {
  int **matrix;
  int rows;
  int cols;
  int cur_row;
  int max;
  int total;
  int recorded;
} indices_t;

int TryOpenFile(const char *filename, FILE **file);

void GetMatrices(FILE *file, vertices_t *vertices, indices_t *indices,
                 errors_e *err_e);
void CountElems(FILE *file, int *rows_v, int *rows_i, int *total_v,
                errors_e *err_e);
double **InitVertices(int rows, int cols, errors_e *err_e);
int **InitIndices(int rows, int total, errors_e *err_e);
void FileParseV(FILE *file, vertices_t *vertices, errors_e *err_e);
void FileParseI(FILE *file, indices_t *indices, errors_e *err_e);
void MatrixCenteringAndNormalization(vertices_t *vertices);
double GetEdgeMax(values_t *max_values);

void AddVertices(vertices_t *vertices, char *line, errors_e *err_e);
void CheckEdgeVal(double num, double *max, double *min);
void FreeVertices(vertices_t *vertices);

void AddIndices(indices_t *indices, int vertices_row, char *line,
                errors_e *err_e);
char *LineCorrecter(char *line);
int CountVerticesInSurface(char *line, char delim);
void FreeIndices(indices_t *indices);

void MoveVertexes(vertices_t *vertices, double moveXValue, double moveYValue,
                  double moveZValue);
void RotateVertexesX(vertices_t *vertices, double rotateXValue);
void RotateVertexesY(vertices_t *vertices, double rotateYValue);
void RotateVertexesZ(vertices_t *vertices, double rotateZValue);
void ScaleVertexes(vertices_t *vertices, double scaleX);

char *ErrorHandle(errors_e err_e);

#endif
