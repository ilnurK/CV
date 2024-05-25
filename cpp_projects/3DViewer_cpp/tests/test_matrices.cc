#include "test_main.h"

using namespace s21;

std::ifstream file{};
const char *fname{};

TEST(ViewerModel, open_file_test) {
  ViewerModel model;
  fname = "models/pyramid.obj";
  ASSERT_TRUE(model.TryOpenFile(fname, file));
  fname = "models/cube.obj";
  ASSERT_TRUE(model.TryOpenFile(fname, file));
  fname = "models/incorrect_path.obj";
  ASSERT_FALSE(model.TryOpenFile(fname, file));
}

TEST(ViewerModel, сount_test) {
  ViewerModel model1;
  fname = "models/pyramid.obj";
  if (model1.TryOpenFile(fname, file)) {
    model1.FillMatrices(file);
    int vertices = model1.GetVerticesQuantity();
    int edges = model1.GetEdges();
    EXPECT_EQ(vertices, 4);
    EXPECT_EQ(edges, 6);
  }

  fname = "models/cube.obj";
  ViewerModel model2;
  if (model2.TryOpenFile(fname, file)) {
    model2.FillMatrices(file);
    int vertices = model2.GetVerticesQuantity();
    int edges = model2.GetEdges();
    EXPECT_EQ(vertices, 8);
    EXPECT_EQ(edges, 16);
  }

  fname = "models/glass.obj";
  ViewerModel model3;
  if (model3.TryOpenFile(fname, file)) {
    model3.FillMatrices(file);
    int vertices = model3.GetVerticesQuantity();
    int edges = model3.GetEdges();
    EXPECT_EQ(vertices, 896);
    EXPECT_EQ(edges, 1760);
  }
}

TEST(ViewerModel, errors_test) {
  ViewerErrors error;
  fname = "models/incorrect_models/facet_that_not_exist.obj";
  ViewerModel model1;
  if (model1.TryOpenFile(fname, file)) {
    model1.FillMatrices(file);
    error = model1.GetError();
    EXPECT_EQ(error, ViewerErrors::MAX_IDX);
  }

  fname = "models/incorrect_models/glass_without_vertex.obj";
  ViewerModel model2;
  if (model2.TryOpenFile(fname, file)) {
    model2.FillMatrices(file);
    error = model2.GetError();
    EXPECT_EQ(error, ViewerErrors::VERTEX_INCORRECT);
  }

  fname = "models/incorrect_models/empty.obj";
  ViewerModel model3;
  if (model3.TryOpenFile(fname, file)) {
    model3.FillMatrices(file);
    error = model3.GetError();
    EXPECT_EQ(error, ViewerErrors::EMPTY_FILE);
  }

  fname = "models/incorrect_models/surface.obj";
  ViewerModel model4;
  if (model4.TryOpenFile(fname, file)) {
    model4.FillMatrices(file);
    error = model4.GetError();
    EXPECT_EQ(error, ViewerErrors::SURFACE_INCORRECT);
  }
}

TEST(ViewerModel, matrices_test) {
  const char *fname = "models/cubecarcas.obj";

  std::vector<double> vertices = {
      0.208333,  -0.473485, 0.397727,  0.208333,  -0.397727, -0.208333,
      0.208333,  -0.473485, -0.208333, 0.208333,  -0.397727, 0.397727,
      -0.397727, -0.397727, -0.208333, -0.397727, -0.473485, -0.208333,
      0.397727,  0.208333,  0.397727,  0.473485,  0.284091,  0.397727,
      0.473485,  -0.208333, 0.397727,  0.397727,  -0.208333, 0.397727,
      -0.208333, -0.397727, 0.397727,  -0.284091, -0.473485, 0.397727,
      -0.208333, 0.208333,  0.397727,  -0.284091, 0.284091,  0.397727,
      -0.397727, -0.473485, 0.284091,  -0.473485, -0.473485, 0.284091,
      -0.473485, -0.473485, -0.284091, 0.284091,  -0.473485, 0.473485,
      -0.284091, -0.473485, 0.473485,  0.284091,  -0.473485, -0.284091,
      -0.397727, -0.397727, 0.208333,  -0.397727, 0.208333,  0.208333,
      -0.397727, 0.284091,  0.284091,  -0.397727, 0.208333,  -0.397727,
      -0.397727, -0.208333, -0.397727, -0.397727, -0.208333, -0.473485,
      -0.397727, 0.284091,  -0.473485, -0.473485, 0.208333,  -0.397727,
      -0.473485, 0.208333,  0.208333,  -0.473485, -0.397727, 0.208333,
      0.284091,  -0.397727, -0.284091, -0.473485, -0.397727, -0.284091,
      -0.473485, 0.284091,  0.284091,  -0.473485, 0.284091,  -0.473485,
      -0.473485, -0.284091, -0.473485, -0.473485, -0.284091, -0.397727,
      0.208333,  -0.208333, -0.473485, 0.284091,  -0.284091, -0.473485,
      -0.284091, 0.473485,  -0.473485, 0.208333,  0.397727,  -0.473485,
      -0.284091, 0.397727,  -0.473485, 0.284091,  0.473485,  -0.473485,
      -0.208333, 0.208333,  0.473485,  -0.208333, -0.397727, 0.473485,
      0.284091,  -0.397727, 0.473485,  0.397727,  0.208333,  0.473485,
      -0.284091, 0.284091,  0.473485,  0.397727,  -0.208333, -0.208333,
      0.397727,  -0.284091, -0.284091, 0.397727,  0.397727,  -0.208333,
      0.397727,  0.473485,  -0.284091, 0.397727,  -0.284091, 0.473485,
      0.397727,  0.473485,  0.208333,  0.397727,  0.397727,  0.208333,
      0.473485,  -0.208333, -0.208333, 0.473485,  0.397727,  -0.208333,
      0.473485,  0.284091,  0.473485,  0.473485,  -0.284091, 0.473485,
      0.473485,  -0.284091, -0.284091, 0.473485,  0.473485,  0.284091,
      0.473485,  0.397727,  0.284091,  0.473485,  0.473485,  -0.284091,
      -0.208333, 0.473485,  -0.397727, 0.284091,  0.473485,  -0.397727,
      -0.284091, 0.473485,  0.284091,  -0.208333, 0.473485,  0.208333,
      -0.208333, 0.397727,  -0.397727, -0.208333, 0.397727,  0.208333,
      -0.284091, 0.397727,  0.284091,  0.208333,  0.397727,  -0.397727,
      0.208333,  -0.208333, -0.397727, 0.284091,  -0.284091, -0.397727};

  ViewerModel model;
  if (model.TryOpenFile(fname, file)) {
    model.FillMatrices(file);
    ViewerErrors error = model.GetError();

    if (error == ViewerErrors::ALL_OK) {
      std::vector<double> model_vertices = model.GetVertices();
      ASSERT_EQ(vertices.size(), model_vertices.size());
      for (size_t i = 0; i < vertices.size(); i++) {
        ASSERT_NEAR(vertices[i], model_vertices[i], 1e-6);
      }
    }
  }
}