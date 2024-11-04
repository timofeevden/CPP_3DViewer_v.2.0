#ifndef CPP4_3DVIEWER_V2_SRC_CONTROLLER_CONTROLLER_OBJECT_H_
#define CPP4_3DVIEWER_V2_SRC_CONTROLLER_CONTROLLER_OBJECT_H_

#include <iostream>

#include "../model/model.h"

namespace s21 {
/**
 * @brief Класс ControllerObject является частью паттерна MVC
 */
class ControllerObject {
 public:
  ControllerObject(Model*);
  ~ControllerObject() = default;

  float* GetVertexCoords();
  const std::vector<Polygon>& GetArrayPolygons() const;
  void OpenFile(std::string path_file);
  void ResetPosition();

  int GetCntVertexes();
  int GetCntPolygons();

  void Moving(float mx, float my, float mz);
  void Rotate(float rx, float ry, float rz);
  void Zoom(float zoom);

 private:
  Model* model_;
};

};  // namespace s21

#endif  //  CPP4_3DVIEWER_V2_SRC_CONTROLLER_CONTROLLER_OBJECT_H_
