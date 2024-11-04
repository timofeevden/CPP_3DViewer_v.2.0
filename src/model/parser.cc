#include "parser.h"

namespace s21 {
/**
 * @brief Конструктор по-умолчанию
 */
Parser::Parser() : cnt_vertexes_(0), cnt_polygons_(0) {}

/**
 * @brief Деструктор
 */
Parser::~Parser() {}

/**
 * @brief Считывание данных файла
 * * @param filename Файл, который будет считываться
 */
void Parser::OpenFile(const std::string& filename) {
  Clean();
  error_ = 0;
  file_.open(filename);
  if (file_.is_open()) {
    ReadFile();
    file_.close();
  } else {
    error_ = 1;
  }
}

void Parser::ReadFile() {
  std::string reading_str;
  while (!file_.eof() && !error_) {
    std::getline(file_, reading_str);
    std::string_view str = reading_str;
    if (str.find("v ") == 0) {
      ++cnt_vertexes_;
      TakeVertex(str);
      vertexes_.push_back(struct_vertex_);
    }
    if (str.find("f ") == 0) {
      ++cnt_polygons_;
      TakePolygon(str);
    }
  }

  if (error_) {
    Clean();
  }
}

void Parser::TakeVertex(std::string_view str) {
  int number_cols = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    if ((std::isdigit(str[i]) || str[i] == '-') && str[i - 1] == ' ' &&
        number_cols < 4) {
      ++number_cols;
      PushVertexPoint(str, &i, number_cols);
    }
  }
  if (number_cols < 3) {
    error_ = 2;  //  Не все 3 координаты
  }
}

void Parser::PushVertexPoint(std::string_view str, size_t* pos,
                             int number_cols) {
  std::string number;
  size_t iter = *pos;
  while (std::isdigit(str[iter]) || str[iter] == '.' || str[iter] == '-') {
    number += str[iter++];
  }
  *pos = iter;
  float result = std::stod(number);
  if (number_cols == 1) {
    struct_vertex_.x = result;
  } else if (number_cols == 2) {
    struct_vertex_.y = result;
  } else if (number_cols == 3) {
    struct_vertex_.z = result;
  }
  FindMinMaxVertex(number_cols, result);
}

void Parser::FindMinMaxVertex(int number_cols, float val) {
  if (number_cols == 1) {
    if (val > range_.x_max || cnt_vertexes_ == 1) range_.x_max = val;
    if (val < range_.x_min || cnt_vertexes_ == 1) range_.x_min = val;
  } else if (number_cols == 2) {
    if (val > range_.y_max || cnt_vertexes_ == 1) range_.y_max = val;
    if (val < range_.y_min || cnt_vertexes_ == 1) range_.y_min = val;
  } else if (number_cols == 3) {
    if (val > range_.z_max || cnt_vertexes_ == 1) range_.z_max = val;
    if (val < range_.z_min || cnt_vertexes_ == 1) range_.z_min = val;
  }
}

void Parser::TakePolygon(std::string_view str) {
  size_t cnt_lines = 0;
  for (size_t i = 0; i < str.size() && !error_; ++i) {
    if ((std::isdigit(str[i]) || str[i] == '-') && str[i - 1] == ' ') {
      ++cnt_lines;
      line_of_polygon_.pol[0] = PushPoligonPoint(str, &i);
      line_of_polygon_.pol[1] = line_of_polygon_.pol[0];
      polygons_.push_back(line_of_polygon_);
      if (cnt_lines > 1)
        polygons_[polygons_.size() - 2].pol[1] = line_of_polygon_.pol[0];
    }
  }
  polygons_[polygons_.size() - 1].pol[1] =
      polygons_[polygons_.size() - cnt_lines].pol[0];
}

int Parser::PushPoligonPoint(std::string_view str, size_t* pos) {
  std::string number;
  size_t iter = *pos;

  while (std::isdigit(str[iter]) || str[iter] == '-') {
    number += str[iter++];
  }
  *pos = iter;
  int result = std::stoi(number);

  if (result < 0) {
    if (result >= (-1) * cnt_vertexes_) {
      result = cnt_vertexes_ + result;
    } else {
      error_ =
          3;  //  отриц.индекс вершины меньше, чем всего вершин на данный момент
    }
  } else if (result > 0) {
    if (result > cnt_vertexes_) {
      error_ = 4;  //  индекс вершины больше, чем всего вершин
    } else {
      --result;  //  т.к отсчет в гл идет с 0
    }
  }
  return result;
}

void Parser::Clean() {
  vertexes_.clear();
  polygons_.clear();
  cnt_vertexes_ = 0;
  cnt_polygons_ = 0;
  range_.x_min = 0;
  range_.x_max = 0;
  range_.y_min = 0;
  range_.y_max = 0;
  range_.z_min = 0;
  range_.z_max = 0;
}

/**
 * @brief Центрирование координат
 */
void Parser::Centering() {
  if (!error_) {
    float dx = range_.x_max - range_.x_min;
    float dy = range_.y_max - range_.y_min;
    float dz = range_.z_max - range_.z_min;
    float center_x = range_.x_min + dx / 2.0f;
    float center_y = range_.y_min + dy / 2.0f;
    float center_z = range_.z_min + dz / 2.0f;
    float dmax = dx;

    if (dy >= dx && dy >= dz) {
      dmax = dy;
    } else if (dz >= dx && dz >= dy) {
      dmax = dz;
    }
    if (dmax == 0) {
      dmax = 1.0f;  //  при делении на 0
    }
    float scale_ratio = 0.7f / dmax;

    for (int i = 0; i < cnt_vertexes_; ++i) {
      vertexes_[i].x -= center_x;
      vertexes_[i].x *= scale_ratio;
      vertexes_[i].y -= center_y;
      vertexes_[i].y *= scale_ratio;
      vertexes_[i].z -= center_z;
      vertexes_[i].z *= scale_ratio;
    }
  }
}

//  =====================   Getters: ===============

/**
 * @brief Геттер количества вершин
 */
int Parser::GetVertexes() { return cnt_vertexes_; }

/**
 * @brief Геттер количества полигонов
 */
int Parser::GetPolygons() { return cnt_polygons_; }

/**
 * @brief Геттер ошибок, полученных при чтении файла
 */
int Parser::GetError() { return error_; }

/**
 * @brief Геттер вектора, в котором хранятся координаты объекта
 */
const std::vector<Vertex>& Parser::GetArrayVertexes() { return vertexes_; }

/**
 * @brief Геттер вектора, в котором хранятся линии полигонов
 */
const std::vector<Polygon>& Parser::GetArrayPolygons() { return polygons_; }

/**
 * @brief Геттер крайних координат файла
 */
Range Parser::GetRange() { return range_; }

}  // namespace s21
