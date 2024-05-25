#ifndef S21_3DVIEWER_MODEL_H
#define S21_3DVIEWER_MODEL_H

#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {

enum class ViewerErrors;

class ViewerModel {
 private:
  std::vector<double> vertices_{};
  std::vector<double> indices_{};
  std::map<std::string, double> extreme_values_{};

 private:
  ViewerErrors error_;

 private:
  size_t len_vertices_{};
  size_t len_indices_{};
  size_t edges_{};

 public:
  ViewerModel();

 public:
  int TryOpenFile(const char *filename, std::ifstream &file);
  void FillMatrices(std::ifstream &file);

 public:
  const std::vector<double> &GetVertices() const { return vertices_; }
  const std::vector<double> &GetIndices() const { return indices_; }
  ViewerErrors GetError() const { return error_; }
  size_t GetVerticesQuantity() { return len_vertices_ / 3; }
  size_t GetIndicesQuantity() { return len_indices_; }
  size_t GetEdges() { return edges_; }

 private:
  void FileParse(std::ifstream &file);

  void AddVertices(const std::string &line);
  void CheckEdgeVal(double num, double &max, double &min);

  void AddIndices(const std::string &line);
  inline void RecordIndice(std::string &token);

  void MatrixCenteringAndNormalization();
  double GetEdgeMax();

 public:
  void MoveVertexes(double move_x, double move_y, double move_z);
  void RotateVertexesX(double rotate_x);
  void RotateVertexesY(double rotate_y);
  void RotateVertexesZ(double rotate_z);
  void ScaleVertexes(double scale);
  double &At(size_t y, size_t x);

  std::string ErrorHandle(ViewerErrors err_num);
};

enum class ViewerErrors {
  ALL_OK = 0,
  INVALID_FILE,
  VERTEX_INCORRECT,
  SURFACE_INCORRECT,
  EMPTY_FILE,
  MAX_IDX,
  MEMORY_NA,
  CONFIGFILE_ERR
};

}  // namespace s21

#endif
