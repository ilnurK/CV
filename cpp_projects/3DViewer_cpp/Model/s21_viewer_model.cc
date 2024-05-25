#include "s21_viewer_model.h"

#include <iostream>

namespace s21 {

ViewerModel::ViewerModel() {
  double min{-1e8}, max{1e8};
  extreme_values_["xmax"] = min;
  extreme_values_["ymax"] = min;
  extreme_values_["zmax"] = min;
  extreme_values_["xmin"] = max;
  extreme_values_["ymin"] = max;
  extreme_values_["zmin"] = max;

  error_ = ViewerErrors::ALL_OK;
}

int ViewerModel::TryOpenFile(const char *filename, std::ifstream &file) {
  file = std::ifstream{filename, std::ios::in};
  return file.is_open();
}

void ViewerModel::FillMatrices(std::ifstream &file) {
  FileParse(file);
  file.close();

  len_vertices_ = vertices_.size();
  edges_ = len_indices_ + GetVerticesQuantity() - 2;

  if (error_ == ViewerErrors::ALL_OK) {
    MatrixCenteringAndNormalization();
  }
  if (error_ == ViewerErrors::ALL_OK && (!len_vertices_ || !len_indices_)) {
    error_ = ViewerErrors::EMPTY_FILE;
  }
}

void ViewerModel::FileParse(std::ifstream &file) {
  std::string line{};
  char space = ' ';
  while (std::getline(file, line) && error_ == ViewerErrors::ALL_OK) {
    size_t idx{0}, len = line.length();
    bool is_starts_space{false};
    while (idx < len && std::isspace(line[idx])) {
      idx++;
      is_starts_space = true;
    }

    if (is_starts_space) {
      line = line.substr(idx);
    }

    if (line.length() > 1 && line[1] == space) {
      if (line[0] == 'v') {
        AddVertices(line);
      } else if (line[0] == 'f') {
        AddIndices(line);
        len_indices_++;
      }
    }
  }
}

void ViewerModel::AddVertices(const std::string &line) {
  double x{0}, y{0}, z{0};
  char v{0};
  std::istringstream iss(line);
  if (iss >> v >> x >> y >> z && v == 'v') {
    vertices_.push_back(x);
    vertices_.push_back(y);
    vertices_.push_back(z);
    CheckEdgeVal(x, extreme_values_["xmax"], extreme_values_["xmin"]);
    CheckEdgeVal(y, extreme_values_["ymax"], extreme_values_["ymin"]);
    CheckEdgeVal(z, extreme_values_["zmax"], extreme_values_["zmin"]);
  } else {
    error_ = ViewerErrors::VERTEX_INCORRECT;
  }
}

void ViewerModel::CheckEdgeVal(double num, double &max, double &min) {
  if (num > max) {
    max = num;
  } else if (num < min) {
    min = num;
  }
}

void ViewerModel::AddIndices(const std::string &line) {
  size_t cr{0}, len = indices_.size();
  size_t last_idx = (len) ? len : 0;
  // to record the number of vertices on surface
  indices_.push_back(-1);
  auto it = line.begin(), ite = line.end();
  bool need_record{false};
  char space = ' ', minus = '-', delim = '/';
  std::string token{};
  while (it != ite) {
    if (std::isdigit(*it) || (*it == minus && !token.size())) {
      need_record = true;
      token += *it;
      it++;
    } else if (need_record && (*it == space || *it == delim)) {
      need_record = false;
      cr++;
      RecordIndice(token);
      if (*it == delim) {
        // go to the next required vertex
        while (it != ite && *it != space) {
          it++;
        }
      }
    } else if (*it == 'f' || !std::isalpha(*it)) {
      it++;
    } else {
      error_ = ViewerErrors::SURFACE_INCORRECT;
      it = ite;
    }
  }
  if (need_record) {
    RecordIndice(token);
    cr++;
  }
  indices_[last_idx] = cr;
}

void ViewerModel::RecordIndice(std::string &token) {
  int num{0}, vertices_row = vertices_.size() / 3;
  if (token[0] == '-' && token.size() > 1) {
    // relative method of vertex numeration;
    num = vertices_row + stoi(token) + 1;
  } else {
    num = stoi(token);
  }
  if (num < 1 || num > vertices_row) {
    error_ = ViewerErrors::MAX_IDX;
  }
  indices_.push_back(num);
  token.clear();
}

void ViewerModel::MatrixCenteringAndNormalization() {
  double x_shift =
      0 - (extreme_values_["xmax"] - fabs(extreme_values_["xmin"])) / 2;
  double y_shift =
      0 - (extreme_values_["ymax"] - fabs(extreme_values_["ymin"])) / 2;
  double z_shift =
      0 - (extreme_values_["zmax"] - fabs(extreme_values_["zmin"])) / 2;
  double max = GetEdgeMax();
  double coef = (max > 1) ? max * 1.1 : 1;
  for (size_t i = 0; i < len_vertices_; i += 3) {
    vertices_[i] = (vertices_[i] + x_shift) / coef;
    vertices_[i + 1] = (vertices_[i + 1] + y_shift) / coef;
    vertices_[i + 2] = (vertices_[i + 2] + z_shift) / coef;
  }
}

double ViewerModel::GetEdgeMax() {
  double max = 0;
  auto it = extreme_values_.begin(), ite = extreme_values_.end();
  for (; it != ite; it++) {
    max = (fabs(it->second) > max) ? fabs(it->second) : max;
  }
  return max;
}

void ViewerModel::MoveVertexes(double move_x, double move_y, double move_z) {
  int condition = move_x || move_y || move_z;
  for (size_t i = 0; condition && i < len_vertices_; i += 3) {
    vertices_[i] += move_x;
    vertices_[i + 1] += move_y;
    vertices_[i + 2] += move_z;
  }
}

void ViewerModel::RotateVertexesX(double rotate_x) {
  double angle_x = rotate_x * M_PI / 180.0;
  for (size_t i = 0; rotate_x && i < len_vertices_; i += 3) {
    double x = vertices_[i];
    double y = vertices_[i + 1];
    double z = vertices_[i + 2];

    vertices_[i] = x;
    vertices_[i + 1] = y * cos(angle_x) - z * sin(angle_x);
    vertices_[i + 2] = y * sin(angle_x) + z * cos(angle_x);
  }
}

void ViewerModel::RotateVertexesY(double rotate_y) {
  double angle_y = rotate_y * M_PI / 180.0;
  for (size_t i = 0; rotate_y && i < len_vertices_; i += 3) {
    double x = vertices_[i];
    double y = vertices_[i + 1];
    double z = vertices_[i + 2];
    vertices_[i] = x * cos(angle_y) + z * sin(angle_y);
    vertices_[i + 1] = y;
    vertices_[i + 2] = -x * sin(angle_y) + z * cos(angle_y);
  }
}

void ViewerModel::RotateVertexesZ(double rotate_z) {
  double angle_z = rotate_z * M_PI / 180.0;
  for (size_t i = 0; rotate_z && i < len_vertices_; i += 3) {
    double x = vertices_[i];
    double y = vertices_[i + 1];
    double z = vertices_[i + 2];

    vertices_[i] = x * cos(angle_z) - y * sin(angle_z);
    vertices_[i + 1] = x * sin(angle_z) + y * cos(angle_z);
    vertices_[i + 2] = z;
  }
}

void ViewerModel::ScaleVertexes(double scale) {
  for (size_t i = 0; scale && i < len_vertices_; i += 3) {
    vertices_[i] *= scale;
    vertices_[i + 1] *= scale;
    vertices_[i + 2] *= scale;
  }
}

double &ViewerModel::At(size_t y, size_t x) {
  size_t idx = y * 3 + x;
  if (idx > len_vertices_) {
    idx = 0;
    error_ = ViewerErrors::SURFACE_INCORRECT;
  }
  return vertices_[idx];
}

std::string ViewerModel::ErrorHandle(ViewerErrors err_num) {
  std::string error{};
  if (err_num == ViewerErrors::VERTEX_INCORRECT) {
    error = "Неверная вершина модели";
  } else if (err_num == ViewerErrors::SURFACE_INCORRECT) {
    error = "Неверная поверхность модели";
  } else if (err_num == ViewerErrors::EMPTY_FILE) {
    error = "Файл не содержит вершин и/или поверхностей";
  } else if (err_num == ViewerErrors::MAX_IDX) {
    error = "Поверхность ссылается на несуществующую вершину";
  } else if (err_num == ViewerErrors::MEMORY_NA) {
    error = "Ошибка выделения памяти";
  } else if (err_num == ViewerErrors::CONFIGFILE_ERR) {
    error = "Ошибка файла настроек";
  }
  return error;
}

}  // namespace s21
