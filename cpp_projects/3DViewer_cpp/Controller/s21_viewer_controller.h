#ifndef S21_3DVIEWER_CONTROLLER_H
#define S21_3DVIEWER_CONTROLLER_H

#include <memory>

#include "../Model/s21_viewer_model.h"

namespace s21 {

class ViewerController {
 private:
  std::unique_ptr<ViewerModel> model_;

 public:
  ViewerController() : model_(std::make_unique<ViewerModel>()) {}

 public:
  int TryOpenFile(const char *filename, std::ifstream &file) {
    return model_->TryOpenFile(filename, file);
  }
  void FillMatrices(std::ifstream &file) { model_->FillMatrices(file); }
  void MoveVertexes(double move_x, double move_y, double move_z) {
    model_->MoveVertexes(move_x, move_y, move_z);
  }
  void RotateVertexesX(double rotate_x) { model_->RotateVertexesX(rotate_x); }
  void RotateVertexesY(double rotate_y) { model_->RotateVertexesY(rotate_y); }
  void RotateVertexesZ(double rotate_z) { model_->RotateVertexesZ(rotate_z); }
  void ScaleVertexes(double scale) { model_->ScaleVertexes(scale); }
  double &At(size_t y, size_t x) { return model_->At(y, x); }

 public:
  const std::vector<double> &GetVertices() const {
    return model_->GetVertices();
  }
  const std::vector<double> &GetIndices() const { return model_->GetIndices(); }
  ViewerErrors GetError() const { return model_->GetError(); }
  size_t GetVerticesQuantity() { return model_->GetVerticesQuantity(); }
  size_t GetIndicesQuantity() { return model_->GetIndicesQuantity(); }
  size_t GetEdges() { return model_->GetEdges(); }
  std::string ErrorHandle(ViewerErrors er) { return model_->ErrorHandle(er); }
};

}  // namespace s21

#endif
