#ifndef CPP4_3DVIEWER_V2_0_1_SRC_MODEL_PARSER_H_
#define CPP4_3DVIEWER_V2_0_1_SRC_MODEL_PARSER_H_

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#define START_SCALE_RATIO 0.7

namespace s21 {

/**
 * @brief Структура хранения координат вершины
 */
struct Vertex {
  float x, y, z;
};

/**
 * @brief Структура минимальных и максимальных координат объекта
 */
struct Range {
  float x_min, x_max;
  float y_min, y_max;
  float z_min, z_max;
};

/**
 * @brief Структура для использования описания полигонов как линий
 */
struct Polygon {
  int pol[2];
};

/**
 * @brief Класс для азагрузки объекта из файла
 */
class Parser {
 public:
  Parser();
  ~Parser();
  void OpenFile(const std::string& filename);
  void Centering();

  int GetVertexes();
  int GetPolygons();
  int GetError();
  const std::vector<Vertex>& GetArrayVertexes();
  const std::vector<Polygon>& GetArrayPolygons();
  Range GetRange();

 private:
  int error_;
  int cnt_vertexes_;              // счетчик вершин
  int cnt_polygons_;              // счетчик полигонов
  std::vector<Vertex> vertexes_;  // вектор с координатами вершин
  std::vector<Polygon> polygons_;  // вектор с координатами полигонов (линий)
  Range range_;  // структура с максимумами и минимуми координат
  std::ifstream file_;
  Vertex struct_vertex_;     //  вершины
  Polygon line_of_polygon_;  //  полигоны

 private:
  void ReadFile();
  void TakePolygon(std::string_view str);
  int PushPoligonPoint(std::string_view str, size_t* pos);
  void TakeVertex(std::string_view str);
  void PushVertexPoint(std::string_view str, size_t* pos, int number_cols);
  void FindMinMaxVertex(int number_cols, float val);
  void Clean();
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODEL_PARSER_H_
