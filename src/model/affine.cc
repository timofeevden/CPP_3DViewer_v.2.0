#include "affine.h"

namespace s21 {
/**
 * @brief Конструктор по-умолчанию
 */
Affine::Affine() { ResetPosition(); }

/**
 * @brief Смещение объекта по оси Х
 * * @param m величина смещения
 */
void Affine::MovingX(float m) {
  for (size_t i = 0; i < vertexes_.size(); ++i) {
    vertexes_[i].x += m;
  }
}

/**
 * @brief Смещение объекта по оси Y
 * * @param m величина смещения
 */
void Affine::MovingY(float m) {
  for (size_t i = 0; i < vertexes_.size(); ++i) {
    vertexes_[i].y += m;
  }
}

/**
 * @brief Смещение объекта по оси Z
 * * @param m величина смещения
 */
void Affine::MovingZ(float m) {
  for (size_t i = 0; i < vertexes_.size(); ++i) {
    vertexes_[i].z += m;
  }
}

/**
 * @brief Поворот объекта относительно оси Х
 * * @param a угол поворота
 */
void Affine::RotationX(float a) {
  float cos = std::cos(a);
  float sin = std::sin(a);
  for (size_t i = 0; i < vertexes_.size(); ++i) {
    float temp_y = vertexes_[i].y;
    float temp_z = vertexes_[i].z;
    vertexes_[i].y = cos * temp_y - sin * temp_z;
    vertexes_[i].z = sin * temp_y + cos * temp_z;
  }
}

/**
 * @brief Поворот объекта относительно оси Y
 * * @param a угол поворота
 */
void Affine::RotationY(float a) {
  float cos = std::cos(a);
  float sin = std::sin(a);
  for (size_t i = 0; i < vertexes_.size(); ++i) {
    float temp_x = vertexes_[i].x;
    float temp_z = vertexes_[i].z;
    vertexes_[i].x = cos * temp_x + sin * temp_z;
    vertexes_[i].z = -sin * temp_x + cos * temp_z;
  }
}

/**
 * @brief Поворот объекта относительно оси Z
 * * @param a угол поворота
 */
void Affine::RotationZ(float a) {
  float cos = std::cos(a);
  float sin = std::sin(a);
  for (size_t i = 0; i < vertexes_.size(); ++i) {
    float temp_x = vertexes_[i].x;
    float temp_y = vertexes_[i].y;
    vertexes_[i].x = cos * temp_x + sin * temp_y;
    vertexes_[i].y = -sin * temp_x + cos * temp_y;
  }
}

/**
 * @brief Изменение мастштаба объекта
 * * @param a величина масштаба
 */
void Affine::Scaling(float a) {
  for (size_t i = 0; i < vertexes_.size(); ++i) {
    vertexes_[i].x *= a;
    vertexes_[i].y *= a;
    vertexes_[i].z *= a;
  }
}

/**
 * @brief Измение масштаба объекта к 1:1
 * * @param a старая величина масштаба
 */
void Affine::ScalingBack(float a) {
  for (size_t i = 0; i < vertexes_.size(); ++i) {
    vertexes_[i].x /= a;
    vertexes_[i].y /= a;
    vertexes_[i].z /= a;
  }
}

//  ============================== Getters:
//  ==========================================

/**
 * @brief Геттер вектора с координатами
 */
const std::vector<Vertex> &Affine::GetArrayVertexes() { return vertexes_; }

/**
 * @brief Геттер смещения Х
 */
float Affine::GetPositionX() { return posX_; }

/**
 * @brief Геттер смещения У
 */
float Affine::GetPositionY() { return posY_; }

/**
 * @brief Геттер смещения Z
 */
float Affine::GetPositionZ() { return posZ_; }

/**
 * @brief Геттер поворота по Х
 */
float Affine::GetRotateX() { return rotateX_; }

/**
 * @brief Геттер поворота по У
 */
float Affine::GetRotateY() { return rotateY_; }

/**
 * @brief Геттер поворота по Z
 */
float Affine::GetRotateZ() { return rotateZ_; }

/**
 * @brief Геттер масштаба
 */
float Affine::GetScaleRatio() { return scale_ratio_; }

//  ====================================== Setters:
//  ==================================

/**
 * @brief Сеттер смещения по Х
 * * @param px Величина смещения
 */
void Affine::SetPositionX(float px) { posX_ = px; }

/**
 * @brief Сеттер смещения по У
 * * @param py Величина смещения
 */
void Affine::SetPositionY(float py) { posY_ = py; }

/**
 * @brief Сеттер смещения по Z
 * * @param pz Величина смещения
 */
void Affine::SetPositionZ(float pz) { posZ_ = pz; }

/**
 * @brief Сеттер поворота по Х
 * * @param rx угол поворота
 */
void Affine::SetRotateX(float rx) { rotateX_ = rx; }

/**
 * @brief Сеттер поворота по У
 * * @param ry угол поворота
 */
void Affine::SetRotateY(float ry) { rotateY_ = ry; }

/**
 * @brief Сеттер поворота по Z
 * * @param rz угол поворота
 */
void Affine::SetRotateZ(float rz) { rotateZ_ = rz; }

/**
 * @brief Сеттер показателя масштаба
 * * @param scale новый показатель масштаба
 */
void Affine::SetScaleRatio(float scale) { scale_ratio_ = scale; }

/**
 * @brief Замена вектора координат на новый
 * * @param other новые координаты
 */
void Affine::SetArrayVertexes(std::vector<Vertex> other) { vertexes_ = other; }

/**
 * @brief Сброс показателей смещений, повротов и масштаба в изначальное
 * положение
 */
void Affine::ResetPosition() {
  posX_ = 0;
  posY_ = 0;
  posZ_ = 0;
  rotateX_ = 0;
  rotateY_ = 0;
  rotateZ_ = 0;
  scale_ratio_ = 1;
}

}  // namespace s21
