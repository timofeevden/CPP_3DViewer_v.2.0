#ifndef CPP4_3DVIEWER_V2_VIEW_MAINWINDOW_H
#define CPP4_3DVIEWER_V2_VIEW_MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QMovie>
#include <QOpenGLWidget>
#include <QPainter>
#include <QProcess>
#include <QSettings>
#include <QTemporaryFile>
#include <QtGlobal>

#include "glwidget.h"
#include "recorder.h"

#define PI 3.14159265358979323846

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
/**
 * @brief Класс MainWindow основной класс в veiw в паттерне MVC
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(s21::ControllerObject* controller_ptr, QWidget* parent = nullptr);
  ~MainWindow();
  void update_timer();
  void clear_timer();

 private slots:
  //  Открытие файла:
  void on_pushButton_open_file_clicked();
  void on_pushButton_parcer_clicked();
  //  Преобразования:
  void on_pushButton_rotate_left_x_clicked();
  void on_pushButton_rotate_right_x_clicked();
  void on_pushButton_rotate_left_y_clicked();
  void on_pushButton_rotate_right_y_clicked();
  void on_pushButton_rotate_left_z_clicked();
  void on_pushButton_rotate_right_z_clicked();
  void on_SpinBox_zoom_valueChanged(double arg1);
  void on_pushButton_zoom_up_clicked();
  void on_pushButton_zoom_down_clicked();
  void on_pushButton_move_up_clicked();
  void on_pushButton_move_down_clicked();
  void on_pushButton_move_left_clicked();
  void on_pushButton_move_right_clicked();
  void on_pushButton_move_near_clicked();
  void on_pushButton_move_far_clicked();
  //  Настройки:
  void on_pushButton_reset_clicked();
  void update_window_settings();
  void on_radioButton_projection_mode_1_clicked();
  void on_radioButton_projection_mode_2_clicked();
  void on_radioButton_line_mode_0_clicked();
  void on_radioButton_line_mode_1_clicked();
  void on_radioButton_line_mode_2_clicked();
  void on_radioButton_color_background_clicked();
  void on_radioButton_color_vertex_clicked();
  void on_radioButton_color_line_clicked();
  void on_radioButton_vertex_mode_0_clicked();
  void on_radioButton_vertex_mode_1_clicked();
  void on_radioButton_vertex_mode_2_clicked();
  void on_checkBox_axis_clicked();
  //  Ползунки настроек:
  void on_slider_vertex_size_valueChanged(int value);
  void on_slider_line_width_valueChanged(int value);
  void on_slider_color_r_valueChanged(int value);
  void on_slider_color_g_valueChanged(int value);
  void on_slider_color_b_valueChanged(int value);
  //  Запись:
  void on_pushButton_screenshot_clicked();
  void on_pushButton_gif_clicked();
  void check_filename_format(QString& filename, QString format);

 private:
  ControllerObject* controller_;
  Ui::MainWindow* ui_;
  GLWidget* glwidget_;
  Settings* settings_;
  RecordManager* recording_;
  int cnt_seconds_;
};
}  // namespace s21

#endif  //  CPP4_3DVIEWER_V2_VIEW_MAINWINDOW_H
