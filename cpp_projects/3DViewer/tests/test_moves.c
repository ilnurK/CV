
#include "tests.h"

START_TEST(Rotate_X) {
  FILE *f = NULL;
  const char *fname = "models/pyramid.obj";
  if (TryOpenFile(fname, &f)) {
    double res_arr[4][3] = {{-0.5000000, -0.1830127, -0.6830127},
                            {0.5000000, -0.1830127, -0.6830127},
                            {0.0000000, 0.4330127, 0.2500000},
                            {0.0000000, -0.6830127, 0.1830127}};

    vertices_t vertices = {};
    indices_t indices = {};
    errors_e err = 0;
    GetMatrices(f, &vertices, &indices, &err);
    RotateVertexesX(&vertices, 30);

    for (int i = 0; i < vertices.rows; i++) {
      for (int j = 0; j < vertices.cols; j++) {
        ck_assert_double_eq_tol(vertices.matrix[j][i], res_arr[j][i], 1e-07);
      }
    }

    FreeVertices(&vertices);
    FreeIndices(&indices);
  }
}
END_TEST

START_TEST(Rotate_X_2) {
  FILE *f = NULL;
  const char *fname = "models/pyramid.obj";
  if (TryOpenFile(fname, &f)) {
    double res_arr[4][3] = {{-0.5000000, -0.6830127, -0.1830127},
                            {0.5000000, -0.6830127, -0.1830127},
                            {0.0000000, 0.4330127, -0.2500000},
                            {0.0000000, -0.1830127, 0.6830127}};

    vertices_t vertices = {};
    indices_t indices = {};
    errors_e err = 0;
    GetMatrices(f, &vertices, &indices, &err);
    RotateVertexesX(&vertices, -30);

    for (int i = 0; i < vertices.rows; i++) {
      for (int j = 0; j < vertices.cols; j++) {
        ck_assert_double_eq_tol(vertices.matrix[j][i], res_arr[j][i], 1e-07);
      }
    }

    FreeVertices(&vertices);
    FreeIndices(&indices);
  }
}
END_TEST

START_TEST(Rotate_Y) {
  FILE *f = NULL;
  const char *fname = "models/pyramid.obj";
  if (TryOpenFile(fname, &f)) {
    double res_arr[4][3] = {{-0.7071068, -0.5000000, -0.0000000},
                            {0.0000000, -0.5000000, -0.7071068},
                            {0.0000000, 0.5000000, 0.0000000},
                            {0.3535534, -0.5000000, 0.3535534}};

    vertices_t vertices = {};
    indices_t indices = {};
    errors_e err = 0;
    GetMatrices(f, &vertices, &indices, &err);
    RotateVertexesY(&vertices, 45);

    for (int i = 0; i < vertices.rows; i++) {
      for (int j = 0; j < vertices.cols; j++) {
        ck_assert_double_eq_tol(vertices.matrix[j][i], res_arr[j][i], 1e-07);
      }
    }

    FreeVertices(&vertices);
    FreeIndices(&indices);
  }
}
END_TEST

START_TEST(Rotate_Z) {
  FILE *f = NULL;
  const char *fname = "models/pyramid.obj";
  if (TryOpenFile(fname, &f)) {
    double res_arr[4][3] = {{-0.2534044, -0.6601411, -0.5000000},
                            {0.6601411, -0.2534044, -0.5000000},
                            {-0.2033683, 0.4567727, 0.0000000},
                            {0.2033683, -0.4567727, 0.5000000}};

    vertices_t vertices = {};
    indices_t indices = {};
    errors_e err = 0;
    GetMatrices(f, &vertices, &indices, &err);
    RotateVertexesZ(&vertices, 24);

    for (int i = 0; i < vertices.rows; i++) {
      for (int j = 0; j < vertices.cols; j++) {
        ck_assert_double_eq_tol(vertices.matrix[j][i], res_arr[j][i], 1e-07);
      }
    }

    FreeVertices(&vertices);
    FreeIndices(&indices);
  }
}
END_TEST

START_TEST(Move) {
  FILE *f = NULL;
  const char *fname = "models/pyramid.obj";
  if (TryOpenFile(fname, &f)) {
    double res_arr[4][3] = {{4.5000000, 0.5000000, -4.5000000},
                            {5.5000000, 0.5000000, -4.5000000},
                            {5.0000000, 1.5000000, -4.0000000},
                            {5.0000000, 0.5000000, -3.5000000}};

    vertices_t vertices = {};
    indices_t indices = {};
    errors_e err = 0;
    GetMatrices(f, &vertices, &indices, &err);
    MoveVertexes(&vertices, 5, 1, -4);

    for (int i = 0; i < vertices.rows; i++) {
      for (int j = 0; j < vertices.cols; j++) {
        ck_assert_double_eq_tol(vertices.matrix[j][i], res_arr[j][i], 1e-07);
      }
    }

    FreeVertices(&vertices);
    FreeIndices(&indices);
  }
}
END_TEST

START_TEST(Scale) {
  FILE *f = NULL;
  const char *fname = "models/pyramid.obj";
  if (TryOpenFile(fname, &f)) {
    double res_arr[4][3] = {{-0.7350000, -0.7350000, -0.7350000},
                            {0.7350000, -0.7350000, -0.7350000},
                            {0.0000000, 0.7350000, 0.0000000},
                            {0.0000000, -0.7350000, 0.7350000}};

    vertices_t vertices = {};
    indices_t indices = {};
    errors_e err = 0;
    GetMatrices(f, &vertices, &indices, &err);
    ScaleVertexes(&vertices, 1.47);

    for (int i = 0; i < vertices.rows; i++) {
      for (int j = 0; j < vertices.cols; j++) {
        ck_assert_double_eq_tol(vertices.matrix[j][i], res_arr[j][i], 1e-07);
      }
    }

    FreeVertices(&vertices);
    FreeIndices(&indices);
  }
}
END_TEST

START_TEST(Scale_2) {
  FILE *f = NULL;
  const char *fname = "models/pyramid.obj";
  if (TryOpenFile(fname, &f)) {
    double res_arr[4][3] = {{-0.2000000, -0.2000000, -0.2000000},
                            {0.2000000, -0.2000000, -0.2000000},
                            {0.0000000, 0.2000000, 0.0000000},
                            {0.0000000, -0.2000000, 0.2000000}};

    vertices_t vertices = {};
    indices_t indices = {};
    errors_e err = 0;
    GetMatrices(f, &vertices, &indices, &err);
    ScaleVertexes(&vertices, 0.4);

    for (int i = 0; i < vertices.rows; i++) {
      for (int j = 0; j < vertices.cols; j++) {
        ck_assert_double_eq_tol(vertices.matrix[j][i], res_arr[j][i], 1e-07);
      }
    }

    FreeVertices(&vertices);
    FreeIndices(&indices);
  }
}
END_TEST

TCase *moves_tcase(void) {
  TCase *tc;
  tc = tcase_create("main");
  tcase_add_test(tc, Rotate_X);
  tcase_add_test(tc, Rotate_X_2);
  tcase_add_test(tc, Rotate_Y);
  tcase_add_test(tc, Rotate_Z);
  tcase_add_test(tc, Move);
  tcase_add_test(tc, Scale);
  tcase_add_test(tc, Scale_2);
  return tc;
}
