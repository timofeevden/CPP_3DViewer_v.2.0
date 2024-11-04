
#include "controller_object.h"

namespace s21 {
/**
 * @brief Конструктор по-умолчанию
 */
ControllerObject::ControllerObject(Model* model_ptr) { model_ = model_ptr; }

/**
 * @brief Геттер массива, в котором хранятся координаты объекта
 */
float* ControllerObject::GetVertexCoords() {
  return (float*)model_->GetArrayVertexes().data();
}

/**
 * @brief Геттер вектора, в котором хранятся линии полигонов
 */
const std::vector<Polygon>& ControllerObject::GetArrayPolygons() const {
  return model_->GetArrayPolygons();
}

/**
 * @brief Считывание данных файла
 * * @param path_file Файл, который будет считываться
 */
void ControllerObject::OpenFile(std::string path_file) {
  model_->LoadingFile(path_file);
}

/**
 * @brief Сброс показателей смещения объекта
 */
void ControllerObject::ResetPosition() {
  model_->SetAffine();
  model_->ResetPosition();
}

/**
 * @brief Геттер количества вершин
 */
int ControllerObject::GetCntVertexes() { return model_->GetCntVertexes(); }

/**
 * @brief Геттер количества полигонов
 */
int ControllerObject::GetCntPolygons() { return model_->GetCntPolygons(); }

/**
 * @brief Перемещение объекта по осям
 * * @param mx перемещение по оси Х
 * * @param my перемещение по оси У
 * * @param mz перемещение по оси z
 */
void ControllerObject::Moving(float mx, float my, float mz) {
  model_->Moving(mx, my, mz);
  model_->AddPosition(mx, my, mz);
}

/**
 * @brief Поворот объекта относительно своих осей
 * * @param rx Поворот относиельно своей оси Х
 * * @param ry Поворот относиельно своей  оси У
 * * @param rz Поворот относиельно своей  оси z
 */
void ControllerObject::Rotate(float rx, float ry, float rz) {
  model_->Rotation(rx, ry, rz);
}

/**
 * @brief Изменение масштаба объекта на заданную величину
 * * @param zoom новый показатель масштаба
 */
void ControllerObject::Zoom(float zoom) { model_->Scaling(zoom); }

}  // namespace s21
