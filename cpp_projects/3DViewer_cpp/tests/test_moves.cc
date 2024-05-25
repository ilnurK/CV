#include "test_main.h"

namespace s21 {

TEST(ViewerModelMoveTest, RotateVertexesX) {
  const char* fname = "models/pyramid.obj";
  ViewerModel model;
  std::ifstream file;
  if (model.TryOpenFile(fname, file)) {
    model.FillMatrices(file);
    model.RotateVertexesX(30);
    const std::vector<double> vertices = model.GetVertices();
    std::vector<double> res_vec = {-0.25,     -0.183013, -0.683013, 0.75,
                                   -0.183013, -0.683013, 0.25,      0.433013,
                                   0.25,      0.25,      -0.683013, 0.183013};

    for (size_t i = 0; i < vertices.size(); i++) {
      ASSERT_NEAR(res_vec[i], vertices[i], 1e-6);
    }
  }
}

TEST(ViewerModelMoveTest, RotateVertexesX_2) {
  const char* fname = "models/pyramid.obj";
  ViewerModel model;
  std::ifstream file;
  if (model.TryOpenFile(fname, file)) {
    model.FillMatrices(file);
    model.RotateVertexesX(-30);
    const std::vector<double> vertices = model.GetVertices();
    std::vector<double> res_vec = {-0.25,     -0.683013, -0.183013, 0.75,
                                   -0.683013, -0.183013, 0.25,      0.433013,
                                   -0.25,     0.25,      -0.183013, 0.683013};
    for (size_t i = 0; i < vertices.size(); i++) {
      ASSERT_NEAR(res_vec[i], vertices[i], 1e-6);
    }
  }
}

TEST(ViewerModelMoveTest, RotateVertexesY) {
  const char* fname = "models/pyramid.obj";
  ViewerModel model;
  std::ifstream file;
  if (model.TryOpenFile(fname, file)) {
    model.FillMatrices(file);
    model.RotateVertexesY(45);
    const std::vector<double> vertices = model.GetVertices();
    std::vector<double> res_vec = {-0.53033,  -0.5,      -0.176777, 0.176777,
                                   -0.5,      -0.883883, 0.176777,  0.5,
                                   -0.176777, 0.53033,   -0.5,      0.176777};
    for (size_t i = 0; i < vertices.size(); i++) {
      ASSERT_NEAR(res_vec[i], vertices[i], 1e-6);
    }
  }
}

TEST(ViewerModelMoveTest, RotateVertexesZ) {
  const char* fname = "models/pyramid.obj";
  ViewerModel model;
  std::ifstream file;
  if (model.TryOpenFile(fname, file)) {
    model.FillMatrices(file);
    model.RotateVertexesZ(24);
    const std::vector<double> vertices = model.GetVertices();
    std::vector<double> res_vec = {-0.025018, -0.558457, -0.5,      0.888527,
                                   -0.15172,  -0.5,      0.025018,  0.558457,
                                   0,         0.431755,  -0.355089, 0.5};
    for (size_t i = 0; i < vertices.size(); i++) {
      ASSERT_NEAR(res_vec[i], vertices[i], 1e-6);
    }
  }
}

TEST(ViewerModelMoveTest, MoveVertexes) {
  const char* fname = "models/pyramid.obj";
  ViewerModel model;
  std::ifstream file;
  if (model.TryOpenFile(fname, file)) {
    model.FillMatrices(file);
    model.MoveVertexes(5, 1, -4);
    const std::vector<double> vertices = model.GetVertices();
    std::vector<double> res_vec = {4.75, 0.5, -4.5, 5.75, 0.5, -4.5,
                                   5.25, 1.5, -4,   5.25, 0.5, -3.5};
    for (size_t i = 0; i < vertices.size(); i++) {
      ASSERT_NEAR(res_vec[i], vertices[i], 1e-6);
    }
  }
}

TEST(ViewerModelMoveTest, ScaleVertexes_1) {
  const char* fname = "models/pyramid.obj";
  ViewerModel model;
  std::ifstream file;
  if (model.TryOpenFile(fname, file)) {
    model.FillMatrices(file);
    model.ScaleVertexes(1.47);
    const std::vector<double> vertices = model.GetVertices();
    std::vector<double> res_vec = {-0.3675, -0.735, -0.735, 1.1025,
                                   -0.735,  -0.735, 0.3675, 0.735,
                                   0,       0.3675, -0.735, 0.735};
    for (size_t i = 0; i < vertices.size(); i++) {
      ASSERT_NEAR(res_vec[i], vertices[i], 1e-6);
    }
  }
}

TEST(ViewerModelMoveTest, ScaleVertexes_2) {
  const char* fname = "models/pyramid.obj";
  ViewerModel model;
  std::ifstream file;
  if (model.TryOpenFile(fname, file)) {
    model.FillMatrices(file);
    model.ScaleVertexes(0.4);
    const std::vector<double> vertices = model.GetVertices();
    std::vector<double> res_vec = {-0.1, -0.2, -0.2, 0.3, -0.2, -0.2,
                                   0.1,  0.2,  0,    0.1, -0.2, 0.2};
    for (size_t i = 0; i < vertices.size(); i++) {
      ASSERT_NEAR(res_vec[i], vertices[i], 1e-6);
    }
  }
}

}  // namespace s21
