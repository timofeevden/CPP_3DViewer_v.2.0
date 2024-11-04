#include "model.h"

namespace s21 {
/**
 * @brief Конструктор по-умолчанию
 */
Model::Model() : parser_(new Parser), affine_(new Affine) {}

/**
 * @brief Деструктор
 */
Model::~Model() {
  if (parser_) delete parser_;
  if (affine_) delete affine_;
}

/**
 * @brief Загрузка данных из файла в модель
 * * @param filename Файл, который будет считываться
 */
void Model::LoadingFile(const std::string& filename) {
  parser_->OpenFile(filename);
  parser_->Centering();
  affine_->ResetPosition();
  SetAffine();
}

/**
 * @brief Перемещение объекта по осям
 * * @param mx перемещение по оси Х
 * * @param my перемещение по оси У
 * * @param mz перемещение по оси z
 */
void Model::Moving(float mx, float my, float mz) {
  affine_->MovingX(mx);
  affine_->MovingY(my);
  affine_->MovingZ(mz);
}

/**
 * @brief Поворот объекта относительно своих осей
 * * @param mx Поворот относиельно своей оси Х
 * * @param my Поворот относиельно своей  оси У
 * * @param mz Поворот относиельно своей  оси z
 */
void Model::Rotation(float rx, float ry, float rz) {
  SetAffine();
  affine_->SetRotateX(affine_->GetRotateX() + rx);
  affine_->RotationX(affine_->GetRotateX());
  affine_->SetRotateY(affine_->GetRotateY() + ry);
  affine_->RotationY(affine_->GetRotateY());
  affine_->SetRotateZ(affine_->GetRotateZ() + rz);
  affine_->RotationZ(affine_->GetRotateZ());
  Moving(affine_->GetPositionX(), affine_->GetPositionY(),
         affine_->GetPositionZ());
  affine_->Scaling(affine_->GetScaleRatio());
}

/**
 * @brief Изменение масштаба объекта на заданную величину
 * * @param s новый показатель масштаба
 */
void Model::Scaling(float s) {
  affine_->ScalingBack(affine_->GetScaleRatio());
  affine_->SetScaleRatio(s);
  affine_->Scaling(s);
}

/**
 * @brief Передача классу affine координат, считанных в классе parser
 */
void Model::SetAffine() {
  affine_->SetArrayVertexes(parser_->GetArrayVertexes());
}

/**
 * @brief Сброс показателей смещения объекта
 */
void Model::ResetPosition() { affine_->ResetPosition(); }

/**
 * @brief Прибавить смещения объекта по 3 осям
 * * @param dx смещение по оси Х
 * * @param dy смещение по оси У
 * * @param dz смещение по оси z
 */
void Model::AddPosition(float dx, float dy, float dz) {
  affine_->SetPositionX(affine_->GetPositionX() + dx);
  affine_->SetPositionY(affine_->GetPositionY() + dy);
  affine_->SetPositionZ(affine_->GetPositionZ() + dz);
}

/**
 * @brief Геттер вектора, в котором хранятся координаты объекта
 */
const std::vector<Vertex>& Model::GetArrayVertexes() const {
  return affine_->GetArrayVertexes();
}

/**
 * @brief Геттер вектора, в котором хранятся линии полигонов
 */
const std::vector<Polygon>& Model::GetArrayPolygons() const {
  return parser_->GetArrayPolygons();
}

/**
 * @brief Геттер количества вершин
 */
int Model::GetCntVertexes() { return parser_->GetVertexes(); }

/**
 * @brief Геттер количества полигонов
 */
int Model::GetCntPolygons() { return parser_->GetPolygons(); }

/**
 * @brief Геттер крайних координат файла
 */
Range Model::GetRange() const { return parser_->GetRange(); }

}  // namespace s21
