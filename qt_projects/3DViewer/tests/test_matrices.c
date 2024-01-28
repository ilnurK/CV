
#include "tests.h"

START_TEST(open_test) {
  FILE *f = NULL;
  const char *fname = "models/pyramid.obj";
  int res = 0;
  res = TryOpenFile(fname, &f);
  (f) ? fclose(f) : 0;
  ck_assert_int_eq(res, 1);

  res = 0;
  fname = "models/cube.obj";
  res = TryOpenFile(fname, &f);
  (f) ? fclose(f) : 0;
  ck_assert_int_eq(res, 1);

  res = 0;
  fname = "models/incorrect_path.obj";
  res = TryOpenFile(fname, &f);
  (f) ? fclose(f) : 0;
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(сount_test) {
  FILE *f = NULL;
  const char *fname = "models/pyramid.obj";
  int rows_v = 0, rows_i = 0, total_v = 0, res = 0;
  errors_e err_e = 0;
  res = TryOpenFile(fname, &f);
  if (res) {
    CountElems(f, &rows_v, &rows_i, &total_v, &err_e);
    if (!err_e) {
      ck_assert(rows_v == 4 && rows_i == 4 && total_v == 12);
    }
  }
  (f) ? fclose(f) : 0;

  fname = "models/cube.obj";
  rows_v = 0, rows_i = 0, total_v = 0, res = 0;
  res = TryOpenFile(fname, &f);
  if (res) {
    CountElems(f, &rows_v, &rows_i, &total_v, &err_e);
    if (!err_e) {
      ck_assert(rows_v == 8 && rows_i == 10 && total_v == 30);
    }
  }
  (f) ? fclose(f) : 0;

  fname = "models/glass.obj";
  rows_v = 0, rows_i = 0, total_v = 0, res = 0;
  res = TryOpenFile(fname, &f);
  if (res) {
    CountElems(f, &rows_v, &rows_i, &total_v, &err_e);
    if (!err_e) {
      ck_assert(rows_v == 896 && rows_i == 866 && total_v == 3520);
    }
  }
  (f) ? fclose(f) : 0;
}
END_TEST

START_TEST(errors_test) {
  FILE *f = NULL;
  const char *fname = "models/incorrect_models/facet_that_not_exist.obj";
  vertices_t vertices = {};
  indices_t indices = {};
  errors_e err_e = 0;
  int res = TryOpenFile(fname, &f);
  if (res) {
    GetMatrices(f, &vertices, &indices, &err_e);
    ErrorHandle(err_e);
    ck_assert(err_e == MAX_IDX);
  } else {
    fclose(f);
  }
  FreeVertices(&vertices);
  FreeIndices(&indices);

  fname = "models/incorrect_models/glass_without_vertex.obj";
  err_e = 0;
  res = TryOpenFile(fname, &f);
  if (res) {
    GetMatrices(f, &vertices, &indices, &err_e);
    ErrorHandle(err_e);
    ck_assert(err_e == VERTEX_INCORRECT);
  } else {
    fclose(f);
  }
  FreeVertices(&vertices);
  FreeIndices(&indices);

  fname = "models/incorrect_models/empty.obj";
  err_e = 0;
  res = TryOpenFile(fname, &f);
  if (res) {
    GetMatrices(f, &vertices, &indices, &err_e);
    ErrorHandle(err_e);
    ck_assert(err_e == EMPTY_FILE);
  } else {
    fclose(f);
  }
  FreeVertices(&vertices);
  FreeIndices(&indices);

  fname = "models/incorrect_models/surface.obj";
  err_e = 0;
  res = TryOpenFile(fname, &f);
  if (res) {
    GetMatrices(f, &vertices, &indices, &err_e);
    ErrorHandle(err_e);
    ck_assert(err_e == SURFACE_INCORRECT);
  } else {
    fclose(f);
  }
  FreeVertices(&vertices);
  FreeIndices(&indices);

  ErrorHandle(MEMORY_NA);
  ErrorHandle(CONFIGFILE_ERR);
}
END_TEST

START_TEST(matrices_test) {
  FILE *f = NULL;
  const char *fname = "models/cubecarcas.obj";
  vertices_t vertices = {};
  indices_t indices = {};
  double matrix[72][3] = {
      {0.208333, -0.473485, 0.397727},   {0.208333, -0.397727, -0.208333},
      {0.208333, -0.473485, -0.208333},  {0.208333, -0.397727, 0.397727},
      {-0.397727, -0.397727, -0.208333}, {-0.397727, -0.473485, -0.208333},
      {0.397727, 0.208333, 0.397727},    {0.473485, 0.284091, 0.397727},
      {0.473485, -0.208333, 0.397727},   {0.397727, -0.208333, 0.397727},
      {-0.208333, -0.397727, 0.397727},  {-0.284091, -0.473485, 0.397727},
      {-0.208333, 0.208333, 0.397727},   {-0.284091, 0.284091, 0.397727},
      {-0.397727, -0.473485, 0.284091},  {-0.473485, -0.473485, 0.284091},
      {-0.473485, -0.473485, -0.284091}, {0.284091, -0.473485, 0.473485},
      {-0.284091, -0.473485, 0.473485},  {0.284091, -0.473485, -0.284091},
      {-0.397727, -0.397727, 0.208333},  {-0.397727, 0.208333, 0.208333},
      {-0.397727, 0.284091, 0.284091},   {-0.397727, 0.208333, -0.397727},
      {-0.397727, -0.208333, -0.397727}, {-0.397727, -0.208333, -0.473485},
      {-0.397727, 0.284091, -0.473485},  {-0.473485, 0.208333, -0.397727},
      {-0.473485, 0.208333, 0.208333},   {-0.473485, -0.397727, 0.208333},
      {0.284091, -0.397727, -0.284091},  {-0.473485, -0.397727, -0.284091},
      {-0.473485, 0.284091, 0.284091},   {-0.473485, 0.284091, -0.473485},
      {-0.473485, -0.284091, -0.473485}, {-0.473485, -0.284091, -0.397727},
      {0.208333, -0.208333, -0.473485},  {0.284091, -0.284091, -0.473485},
      {-0.284091, 0.473485, -0.473485},  {0.208333, 0.397727, -0.473485},
      {-0.284091, 0.397727, -0.473485},  {0.284091, 0.473485, -0.473485},
      {-0.208333, 0.208333, 0.473485},   {-0.208333, -0.397727, 0.473485},
      {0.284091, -0.397727, 0.473485},   {0.397727, 0.208333, 0.473485},
      {-0.284091, 0.284091, 0.473485},   {0.397727, -0.208333, -0.208333},
      {0.397727, -0.284091, -0.284091},  {0.397727, 0.397727, -0.208333},
      {0.397727, 0.473485, -0.284091},   {0.397727, -0.284091, 0.473485},
      {0.397727, 0.473485, 0.208333},    {0.397727, 0.397727, 0.208333},
      {0.473485, -0.208333, -0.208333},  {0.473485, 0.397727, -0.208333},
      {0.473485, 0.284091, 0.473485},    {0.473485, -0.284091, 0.473485},
      {0.473485, -0.284091, -0.284091},  {0.473485, 0.473485, 0.284091},
      {0.473485, 0.397727, 0.284091},    {0.473485, 0.473485, -0.284091},
      {-0.208333, 0.473485, -0.397727},  {0.284091, 0.473485, -0.397727},
      {-0.284091, 0.473485, 0.284091},   {-0.208333, 0.473485, 0.208333},
      {-0.208333, 0.397727, -0.397727},  {-0.208333, 0.397727, 0.208333},
      {-0.284091, 0.397727, 0.284091},   {0.208333, 0.397727, -0.397727},
      {0.208333, -0.208333, -0.397727},  {0.284091, -0.284091, -0.397727}};
  errors_e err_e = 0;
  int res = TryOpenFile(fname, &f);
  if (res) {
    GetMatrices(f, &vertices, &indices, &err_e);
    if (!err_e) {
      for (int i = 0; i < vertices.rows; i++) {
        for (int j = 0; j < vertices.cols; j++) {
          ck_assert_double_eq_tol(vertices.matrix[j][i], matrix[j][i], 1e-06);
        }
      }
    }
  }
}
END_TEST

TCase *matrices_tcase(void) {
  TCase *tc;
  tc = tcase_create("main");
  tcase_add_test(tc, open_test);
  tcase_add_test(tc, сount_test);
  tcase_add_test(tc, errors_test);
  tcase_add_test(tc, matrices_test);

  return tc;
}