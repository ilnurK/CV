#include "s21_3DViewer.h"

void MoveVertexes(vertices_t *vertices, double moveXValue, double moveYValue,
                  double moveZValue) {
  int condition = moveXValue || moveYValue || moveZValue;
  for (int i = 0; condition && i < vertices->rows; i++) {
    vertices->matrix[i][0] += moveXValue;
    vertices->matrix[i][1] += moveYValue;
    vertices->matrix[i][2] += moveZValue;
  }
}

void RotateVertexesZ(vertices_t *vertices, double rotateZValue) {
  double angleZ = rotateZValue * M_PI / 180.0;
  for (int i = 0; rotateZValue && i < vertices->rows; i++) {
    double x = vertices->matrix[i][0];
    double y = vertices->matrix[i][1];
    double z = vertices->matrix[i][2];

    vertices->matrix[i][0] = x * cos(angleZ) - y * sin(angleZ);
    vertices->matrix[i][1] = x * sin(angleZ) + y * cos(angleZ);
    vertices->matrix[i][2] = z;
  }
}

void RotateVertexesY(vertices_t *vertices, double rotateYValue) {
  double angleY = rotateYValue * M_PI / 180.0;
  for (int i = 0; rotateYValue && i < vertices->rows; i++) {
    double x = vertices->matrix[i][0];
    double y = vertices->matrix[i][1];
    double z = vertices->matrix[i][2];
    vertices->matrix[i][0] = x * cos(angleY) + z * sin(angleY);
    vertices->matrix[i][1] = y;
    vertices->matrix[i][2] = -x * sin(angleY) + z * cos(angleY);
  }
}

void RotateVertexesX(vertices_t *vertices, double rotateXValue) {
  double angleX = rotateXValue * M_PI / 180.0;
  for (int i = 0; rotateXValue && i < vertices->rows; i++) {
    double x = vertices->matrix[i][0];
    double y = vertices->matrix[i][1];
    double z = vertices->matrix[i][2];

    vertices->matrix[i][0] = x;
    vertices->matrix[i][1] = y * cos(angleX) - z * sin(angleX);
    vertices->matrix[i][2] = y * sin(angleX) + z * cos(angleX);
  }
}

void ScaleVertexes(vertices_t *vertices, double scaleX) {
  for (int i = 0; scaleX && i < vertices->rows; i++) {
    vertices->matrix[i][0] *= scaleX;
    vertices->matrix[i][1] *= scaleX;
    vertices->matrix[i][2] *= scaleX;
  }
}
