#include "./settings.h"

namespace s21 {
Settings* Settings::p_instance = nullptr;

/**
 * @brief Констрктор класса Settings
 */

Settings::Settings()
    : QSettings(QDir::homePath() + "/3d_viewer_settings.ini",
                QSettings::IniFormat) {
  Load();
}

/**
 * @brief Геттер указателя на объект класса Settings, реализован паттерном
 * одиночка
 */
Settings* Settings::GetInstance() {
  if (!p_instance) {
    p_instance = new Settings();
  }
  return p_instance;
}

/**
 * @brief Уничтожение объекта класса Settings
 */
void Settings::FreeInstance() {
  delete p_instance;
  p_instance = nullptr;
}

/**
 * @brief Соханение настроек
 */
void Settings::Save() {
  QSettings::setValue("view/axis_mode", axis_mode_);
  QSettings::setValue("view/projection_mode", projection_mode_);
  QSettings::setValue("view/vertex_mode", vertex_mode_);
  QSettings::setValue("view/vertex_size", vertex_size_);
  QSettings::setValue("view/line_mode", line_mode_);
  QSettings::setValue("view/line_width", line_width_);

  QSettings::setValue("colors/color_background_r", color_background_.r);
  QSettings::setValue("colors/color_background_g", color_background_.g);
  QSettings::setValue("colors/color_background_b", color_background_.b);

  QSettings::setValue("colors/color_vertex_r", color_vertex_.r);
  QSettings::setValue("colors/color_vertex_g", color_vertex_.g);
  QSettings::setValue("colors/color_vertex_b", color_vertex_.b);

  QSettings::setValue("colors/color_line_r", color_line_.r);
  QSettings::setValue("colors/color_line_g", color_line_.g);
  QSettings::setValue("colors/color_line_b", color_line_.b);
  //      записываем настройки:
  QSettings::sync();
}

/**
 * @brief Загрузка настроек
 */
void Settings::Load() {
  axis_mode_ = QSettings::value("view/axis_mode", 0).toBool();
  projection_mode_ = QSettings::value("view/projection_mode", 1).toInt();
  vertex_mode_ = QSettings::value("view/vertex_mode", 1).toInt();
  vertex_size_ = QSettings::value("view/vertex_size", 1.0f).toFloat();
  line_mode_ = QSettings::value("view/line_mode", 1).toInt();
  line_width_ = QSettings::value("view/line_width", 1.0f).toFloat();

  color_background_.r =
      QSettings::value("colors/color_background_r", 0.5f).toFloat();
  color_background_.g =
      QSettings::value("colors/color_background_g", 0.5f).toFloat();
  color_background_.b =
      QSettings::value("colors/color_background_b", 0.5f).toFloat();

  color_vertex_.r = QSettings::value("colors/color_vertex_r", 0.0f).toFloat();
  color_vertex_.g = QSettings::value("colors/color_vertex_g", 0.0f).toFloat();
  color_vertex_.b = QSettings::value("colors/color_vertex_b", 0.0f).toFloat();

  color_line_.r = QSettings::value("colors/color_line_r", 0.0f).toFloat();
  color_line_.g = QSettings::value("colors/color_line_g", 0.0f).toFloat();
  color_line_.b = QSettings::value("colors/color_line_b", 0.0f).toFloat();
}

/**
 * @brief Сброс настроек
 */
void Settings::Reset() {
  color_vertex_ = {0.0f, 0.0f, 0.0f};
  color_line_ = {0.0f, 0.0f, 0.0f};
  color_background_ = {0.5f, 0.5f, 0.5f};
  projection_mode_ = 1;
  line_mode_ = 1;
  vertex_mode_ = 1;
  line_width_ = 1;
  vertex_size_ = 3;
  axis_mode_ = false;
}

//  ==========================  Getters ========================

bool Settings::GetAxisMode() { return axis_mode_; }

int Settings::GetProjectionMode() { return projection_mode_; }

int Settings::GetVertexMode() { return vertex_mode_; }

int Settings::GetLineMode() { return line_mode_; }

float Settings::GetLineWidth() { return line_width_; }

float Settings::GetVertexSize() { return vertex_size_; }

const color_t& Settings::GetColorBackground() { return color_background_; }

const color_t& Settings::GetColorVertex() { return color_vertex_; }

const color_t& Settings::GetColorLine() { return color_line_; }

//  ==========================  Setters ========================

void Settings::SetAxisMode(bool mode) { axis_mode_ = mode; }

void Settings::SetProjectionMode(int mode) { projection_mode_ = mode; }

void Settings::SetVertexMode(int mode) { vertex_mode_ = mode; }

void Settings::SetLineMode(int mode) { line_mode_ = mode; }

void Settings::SetLineWidth(float width) { line_width_ = width; }

void Settings::SetVertexSize(float size) { vertex_size_ = size; }

//  =========================   Colors =====================

void Settings::SetColorBackground(float r, float g, float b) {
  color_background_.r = r;
  color_background_.g = g;
  color_background_.b = b;
}

void Settings::SetColorVertex(float r, float g, float b) {
  color_vertex_.r = r;
  color_vertex_.g = g;
  color_vertex_.b = b;
}

void Settings::SetColorLine(float r, float g, float b) {
  color_line_.r = r;
  color_line_.g = g;
  color_line_.b = b;
}

void Settings::SetColorBackgroundR(float c) { color_background_.r = c; }

void Settings::SetColorBackgroundG(float c) { color_background_.g = c; }

void Settings::SetColorBackgroundB(float c) { color_background_.b = c; }

void Settings::SetColorVertexR(float c) { color_vertex_.r = c; }

void Settings::SetColorVertexG(float c) { color_vertex_.g = c; }

void Settings::SetColorVertexB(float c) { color_vertex_.b = c; }

void Settings::SetColorLineR(float c) { color_line_.r = c; }

void Settings::SetColorLineG(float c) { color_line_.g = c; }

void Settings::SetColorLineB(float c) { color_line_.b = c; }

}  // namespace s21
