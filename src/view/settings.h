#ifndef CPP4_3DVIEWER_V2_VIEW_SETTINGS_H
#define CPP4_3DVIEWER_V2_VIEW_SETTINGS_H

#include <QFileDialog>
#include <QSettings>

namespace s21 {
/**
 * @brief структура для хранения цвета
 */
typedef struct {
  float r;
  float g;
  float b;
} color_t;

/**
 * @brief Класс Settings реализован паттерном "Одиночка"
 */
class Settings : public QSettings {
 public:
  Settings(const Settings&) = delete;
  Settings(Settings&&) = delete;
  Settings& operator=(const Settings&) = delete;
  Settings& operator=(Settings&&) = delete;
  static Settings* GetInstance();

 public:
  void FreeInstance();
  void Save();
  void Load();
  void Reset();
  //  getters:
  bool GetAxisMode();
  int GetProjectionMode();
  int GetVertexMode();
  int GetLineMode();
  float GetLineWidth();
  float GetVertexSize();
  const color_t& GetColorBackground();
  const color_t& GetColorVertex();
  const color_t& GetColorLine();
  //  setters:
  void SetAxisMode(bool mode);
  void SetProjectionMode(int mode);
  void SetVertexMode(int mode);
  void SetLineMode(int mode);
  void SetLineWidth(float width);
  void SetVertexSize(float size);
  void SetColorBackground(float r, float g, float b);
  void SetColorVertex(float r, float g, float b);
  void SetColorLine(float r, float g, float b);
  void SetColorBackgroundR(float c);
  void SetColorBackgroundG(float c);
  void SetColorBackgroundB(float c);
  void SetColorVertexR(float c);
  void SetColorVertexG(float c);
  void SetColorVertexB(float c);
  void SetColorLineR(float c);
  void SetColorLineG(float c);
  void SetColorLineB(float c);

 private:
  Settings();
  ~Settings() = default;

  // private:
 private:
  static Settings* p_instance;
  bool axis_mode_;
  int projection_mode_;
  int vertex_mode_;
  int line_mode_;
  float line_width_;
  float vertex_size_;
  color_t color_background_;
  color_t color_vertex_;
  color_t color_line_;
};
}  // namespace s21
#endif  //  CPP4_3DVIEWER_V2_VIEW_SETTINGS_H
