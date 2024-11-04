#ifndef CPP4_3DVIEWER_V2_0_1_SRC_MODEL_MODEL_H_
#define CPP4_3DVIEWER_V2_0_1_SRC_MODEL_MODEL_H_

#include "affine.h"
#include "parser.h"

/**
 * @brief namespace s21
 */
namespace s21 {
//  Класс Model реализован паттерном "Фасад"
/**
 * @brief Класс Model реализован паттерном "Фасад", состоит из классов Parser и
 * Affine
 */
class Model {
 public:
  Model();
  ~Model();
  void LoadingFile(const std::string& filename);
  void Moving(float mx, float my, float mz);
  void Rotation(float rx, float ry, float rz);
  void Scaling(float s);
  void SetAffine();
  void ResetPosition();
  void AddPosition(float dx, float dy, float dz);
  //  Getters:
  const std::vector<Vertex>& GetArrayVertexes() const;
  const std::vector<Polygon>& GetArrayPolygons() const;
  int GetCntVertexes();
  int GetCntPolygons();
  Range GetRange() const;

 private:
  Parser* parser_;
  Affine* affine_;
};
}  // namespace s21

#endif  //  CPP4_3DVIEWER_V2_0_1_SRC_MODEL_MODEL_H_
