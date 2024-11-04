#ifndef CPP4_3DVIEWER_V2_0_1_SRC_MODEL_AFFINE_H_
#define CPP4_3DVIEWER_V2_0_1_SRC_MODEL_AFFINE_H_

#include <cmath>

#include "parser.h"

namespace s21 {
/**
 * @brief Класс для афинных преобразований объекта
 */
class Affine {
 public:
  Affine();
  ~Affine() = default;
  void MovingX(float m);
  void MovingY(float m);
  void MovingZ(float m);
  void RotationX(float a);
  void RotationY(float a);
  void RotationZ(float a);
  void Scaling(float a);
  void ScalingBack(float a);
  void ResetPosition();
  //  Getters:
  const std::vector<Vertex> &GetArrayVertexes();
  float GetPositionX();
  float GetPositionY();
  float GetPositionZ();
  float GetRotateX();
  float GetRotateY();
  float GetRotateZ();
  float GetScaleRatio();
  //  Setters:
  void SetPositionX(float px);
  void SetPositionY(float py);
  void SetPositionZ(float pz);
  void SetRotateX(float rx);
  void SetRotateY(float ry);
  void SetRotateZ(float rz);
  void SetScaleRatio(float scale);
  void SetArrayVertexes(std::vector<Vertex> other);

 private:
  std::vector<Vertex> vertexes_;
  float posX_;
  float posY_;
  float posZ_;
  float rotateX_;
  float rotateY_;
  float rotateZ_;
  float scale_ratio_;
};
}  // namespace s21

#endif  //  CPP4_3DVIEWER_V2_0_1_SRC_MODEL_AFFINE_H_
