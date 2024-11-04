#include "./mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {

/**
 * @brief Конструктор MainWindow по-умолчанию
 */
MainWindow::MainWindow(s21::ControllerObject* controller_ptr, QWidget* parent)
    : QMainWindow(parent),
      controller_(controller_ptr),
      ui_(new Ui::MainWindow),
      glwidget_(new GLWidget(controller_)),
      settings_(Settings::GetInstance()),
      recording_(nullptr),
      cnt_seconds_(0) {
  ui_->setupUi(this);
  this->setFixedSize(this->size());
  ui_->openglLayout->layout()->addWidget(glwidget_);
  this->setWindowTitle("3DViewer v.2.0");
  update_window_settings();
}

/**
 * @brief Деструктор MainWindow
 */
MainWindow::~MainWindow() {
  if (ui_->checkBox_save_settings->isChecked()) {
    settings_->Save();
  }
  if (recording_) {
    delete recording_;
  }
  delete glwidget_;
  delete ui_;
  settings_->FreeInstance();
}

//  ============================== Открытие файла ==============================

/**
 * @brief Открытие файла с возможностью выбора из каталога
 */
void MainWindow::on_pushButton_open_file_clicked() {
  QString fileFilter = "OBJ Files (*.obj);;All Files (*)";
  QString fileName =
      QFileDialog::getOpenFileName(this, tr("Load Model File"), "", fileFilter);
  ui_->label_loading_file->setText("Загрузка файла...");

  if (!fileName.isEmpty()) {
    QFileInfo fileInfo(fileName);
    QString absoluteFilePath = fileInfo.absoluteFilePath();
    controller_->OpenFile(absoluteFilePath.toStdString());
    ui_->filename_input->setText(absoluteFilePath);
    QStringList w = absoluteFilePath.split("/");
    ui_->label_filename->setText(w.last());
    ui_->label_cnt_vertex->setText(
        "Кол-во вершин: " + QString::number(controller_->GetCntVertexes()));
    ui_->label_cnt_facets->setText(
        "Поверхностей: " + QString::number(controller_->GetCntPolygons()));
  }
  ui_->label_loading_file->setText("");
}

/**
 * @brief Открытие файла
 */
void MainWindow::on_pushButton_parcer_clicked() {
  ui_->label_loading_file->setText("Загрузка файла...");
  QString filename = ui_->filename_input->text();
  controller_->OpenFile(filename.toStdString());
  ui_->label_loading_file->setText("");
}

//  ================================= Повороты =================================

/**
 * @brief Повороты модели налево по оси х
 */
void MainWindow::on_pushButton_rotate_left_x_clicked() {
  controller_->Rotate((float)ui_->SpinBox_rotate->value() * PI / 180.0, 0, 0);
}

/**
 * @brief Повороты модели направо по оси х
 */
void MainWindow::on_pushButton_rotate_right_x_clicked() {
  controller_->Rotate(
      (-1.0f) * (float)ui_->SpinBox_rotate->value() * PI / 180.0, 0, 0);
}

/**
 * @brief Повороты модели налево по оси y
 */
void MainWindow::on_pushButton_rotate_left_y_clicked() {
  controller_->Rotate(0.0f, (float)ui_->SpinBox_rotate->value() * PI / 180.0,
                      0);
}

/**
 * @brief Повороты модели направо по оси y
 */
void MainWindow::on_pushButton_rotate_right_y_clicked() {
  controller_->Rotate(
      0.0f, (-1.0f) * (float)ui_->SpinBox_rotate->value() * PI / 180.0, 0);
}

/**
 * @brief Повороты модели налево по оси z
 */
void MainWindow::on_pushButton_rotate_left_z_clicked() {
  controller_->Rotate(0.0f, 0.0f,
                      (float)ui_->SpinBox_rotate->value() * PI / 180.0);
}

/**
 * @brief Повороты модели направо по оси z
 */
void MainWindow::on_pushButton_rotate_right_z_clicked() {
  controller_->Rotate(
      0.0f, 0.0f, (-1.0f) * (float)ui_->SpinBox_rotate->value() * PI / 180.0);
}

//  ============================= Масштабирование =============================

/**
 * @brief Изменение масштаба модели на определенную велечину
 * * @param arg1 Величина, на которую изменяется масштаб модели
 */
void MainWindow::on_SpinBox_zoom_valueChanged(double arg1) {
  controller_->Zoom((float)arg1);
}

/**
 * @brief Увеличение масштаба модели
 */
void MainWindow::on_pushButton_zoom_up_clicked() {
  ui_->SpinBox_zoom->setValue(ui_->SpinBox_zoom->value() + 0.1);
}

/**
 * @brief Уменьшение масштаба модели
 */
void MainWindow::on_pushButton_zoom_down_clicked() {
  ui_->SpinBox_zoom->setValue(ui_->SpinBox_zoom->value() - 0.1);
}

//  ===============================  Перемещения ===============================

/**
 * @brief Перемещение модели вверх по оси y
 */
void MainWindow::on_pushButton_move_up_clicked() {
  float dy = (float)ui_->SpinBox_move->value();
  controller_->Moving(0.0f, dy, 0.0f);
}

/**
 * @brief Перемещение модели вниз по оси y
 */
void MainWindow::on_pushButton_move_down_clicked() {
  float dy = -(float)ui_->SpinBox_move->value();
  controller_->Moving(0.0f, dy, 0.0f);
}

/**
 * @brief Перемещение модели налево по оси х
 */
void MainWindow::on_pushButton_move_left_clicked() {
  float dx = -(float)ui_->SpinBox_move->value();
  controller_->Moving(dx, 0.0f, 0.0f);
}

/**
 * @brief Перемещение модели направо по оси х
 */
void MainWindow::on_pushButton_move_right_clicked() {
  float dx = (float)ui_->SpinBox_move->value();
  controller_->Moving(dx, 0.0f, 0.0f);
}

/**
 * @brief Перемещение модели ближе по оси z
 */
void MainWindow::on_pushButton_move_near_clicked() {
  float dz = (float)ui_->SpinBox_move->value();
  controller_->Moving(0.0f, 0.0f, dz);
}

/**
 * @brief Перемещение модели дальше по оси z
 */
void MainWindow::on_pushButton_move_far_clicked() {
  float dz = -(float)ui_->SpinBox_move->value();
  controller_->Moving(0.0f, 0.0f, dz);
}

//  ==================== Настройки отображения элементов: ====================

/**
 * @brief Настройка тип проекции (параллельная)
 */
void MainWindow::on_radioButton_projection_mode_1_clicked() {
  settings_->SetProjectionMode(1);
}

/**
 * @brief Настройка тип проекции (центральная)
 */
void MainWindow::on_radioButton_projection_mode_2_clicked() {
  settings_->SetProjectionMode(2);
}

/**
 * @brief Настройка отображения вершин (без вершин)
 */
void MainWindow::on_radioButton_vertex_mode_0_clicked() {
  settings_->SetVertexMode(0);
}

/**
 * @brief Настройка отображения вершин (круг)
 */
void MainWindow::on_radioButton_vertex_mode_1_clicked() {
  settings_->SetVertexMode(1);
}

/**
 * @brief Настройка отображения вершин (квадрат)
 */
void MainWindow::on_radioButton_vertex_mode_2_clicked() {
  settings_->SetVertexMode(2);
}

/**
 * @brief Настройка отображения линий (без линий)
 */
void MainWindow::on_radioButton_line_mode_0_clicked() {
  settings_->SetLineMode(0);
}

/**
 * @brief Настройка отображения линий (сплошная линия)
 */
void MainWindow::on_radioButton_line_mode_1_clicked() {
  settings_->SetLineMode(1);
}

/**
 * @brief Настройка отображения линий (пунктиром)
 */
void MainWindow::on_radioButton_line_mode_2_clicked() {
  settings_->SetLineMode(2);
}

/**
 * @brief Настройка отображения осей x, y, z
 */
void MainWindow::on_checkBox_axis_clicked() {
  if (ui_->checkBox_axis->isChecked()) {
    settings_->SetAxisMode(true);
  } else {
    settings_->SetAxisMode(false);
  }
}

//  ============================== Ползунки: ==============================

/**
 * @brief Изменение размера вершин на параметр value
 * * @param value Параметр, на котрый будет изменяться размер вершин
 */
void MainWindow::on_slider_vertex_size_valueChanged(int value) {
  settings_->SetVertexSize((float)value);
}

/**
 * @brief Изменение ширины линий на параметр value
 * * @param value Параметр, на котрый будет изменяться ширина линий
 */
void MainWindow::on_slider_line_width_valueChanged(int value) {
  settings_->SetLineWidth((float)value);
}

/**
 * @brief Изменение цвета фона, вершин и линий по оси "Red"
 * * @param value Параметр, на котрый будет изменяться цвет
 */
void MainWindow::on_slider_color_r_valueChanged(int value) {
  if (ui_->radioButton_color_background->isChecked()) {
    settings_->SetColorBackgroundR(value / 100.0f);
  } else if (ui_->radioButton_color_vertex->isChecked()) {
    settings_->SetColorVertexR(value / 100.0f);
  } else if (ui_->radioButton_color_line->isChecked()) {
    settings_->SetColorLineR(value / 100.0f);
  }
}

/**
 * @brief Изменение цвета фона, вершин и линий по оси "Green"
 * * @param value Параметр, на котрый будет изменяться цвет
 */
void MainWindow::on_slider_color_g_valueChanged(int value) {
  if (ui_->radioButton_color_background->isChecked()) {
    settings_->SetColorBackgroundG(value / 100.0f);
  } else if (ui_->radioButton_color_vertex->isChecked()) {
    settings_->SetColorVertexG(value / 100.0f);
  } else if (ui_->radioButton_color_line->isChecked()) {
    settings_->SetColorLineG(value / 100.0f);
  }
}

/**
 * @brief Изменение цвета фона, вершин и линий по оси "Blue"
 * * @param value Параметр, на котрый будет изменяться цвет
 */
void MainWindow::on_slider_color_b_valueChanged(int value) {
  if (ui_->radioButton_color_background->isChecked()) {
    settings_->SetColorBackgroundB(value / 100.0f);
  } else if (ui_->radioButton_color_vertex->isChecked()) {
    settings_->SetColorVertexB(value / 100.0f);
  } else if (ui_->radioButton_color_line->isChecked()) {
    settings_->SetColorLineB(value / 100.0f);
  }
}

//  =====================  Переключатели настройка цветов =====================

/**
 * @brief Изменение цвета фона
 */
void MainWindow::on_radioButton_color_background_clicked() {
  ui_->slider_color_r->setValue(settings_->GetColorBackground().r * 100);
  ui_->slider_color_g->setValue(settings_->GetColorBackground().g * 100);
  ui_->slider_color_b->setValue(settings_->GetColorBackground().b * 100);
}

/**
 * @brief Изменение цвета вершин
 */
void MainWindow::on_radioButton_color_vertex_clicked() {
  ui_->slider_color_r->setValue(settings_->GetColorVertex().r * 100);
  ui_->slider_color_g->setValue(settings_->GetColorVertex().g * 100);
  ui_->slider_color_b->setValue(settings_->GetColorVertex().b * 100);
}

/**
 * @brief Изменение цвета линий
 */
void MainWindow::on_radioButton_color_line_clicked() {
  ui_->slider_color_r->setValue(settings_->GetColorLine().r * 100);
  ui_->slider_color_g->setValue(settings_->GetColorLine().g * 100);
  ui_->slider_color_b->setValue(settings_->GetColorLine().b * 100);
}

//  ===========================  Настройки ===========================

/**
 * @brief Сброс настроек и позиции моднли до перевоночальных
 */
void MainWindow::on_pushButton_reset_clicked() {
  settings_->Reset();
  controller_->ResetPosition();
  update_window_settings();
}

//  обновление переключателей на ui

/**
 * @brief Обновление переключателей
 */
void MainWindow::update_window_settings() {
  if (settings_->GetAxisMode()) {
    ui_->checkBox_axis->setChecked(true);
  } else {
    ui_->checkBox_axis->setChecked(false);
  }
  if (settings_->GetProjectionMode() == 1) {
    ui_->radioButton_projection_mode_1->setChecked(true);
  } else if (settings_->GetProjectionMode() == 2) {
    ui_->radioButton_projection_mode_2->setChecked(true);
  }

  if (settings_->GetVertexMode() == 0) {
    ui_->radioButton_vertex_mode_0->setChecked(true);
  } else if (settings_->GetVertexMode() == 1) {
    ui_->radioButton_vertex_mode_1->setChecked(true);
  } else if (settings_->GetVertexMode() == 2) {
    ui_->radioButton_vertex_mode_2->setChecked(true);
  }
  ui_->slider_vertex_size->setValue(settings_->GetVertexSize());

  if (settings_->GetLineMode() == 0) {
    ui_->radioButton_line_mode_0->setChecked(true);
  } else if (settings_->GetLineMode() == 1) {
    ui_->radioButton_line_mode_1->setChecked(true);
  } else if (settings_->GetLineMode() == 2) {
    ui_->radioButton_line_mode_2->setChecked(true);
  }
  ui_->slider_line_width->setValue(settings_->GetLineWidth());
  //  Ползунки цвета:
  if (ui_->radioButton_color_background->isChecked()) {
    ui_->slider_color_r->setValue(
        (int)(settings_->GetColorBackground().r * 100.0f));
    ui_->slider_color_g->setValue(
        (int)(settings_->GetColorBackground().g * 100.0f));
    ui_->slider_color_b->setValue(
        (int)(settings_->GetColorBackground().b * 100.0f));
  } else if (ui_->radioButton_color_vertex->isChecked()) {
    ui_->slider_color_r->setValue(
        (int)(settings_->GetColorVertex().r * 100.0f));
    ui_->slider_color_g->setValue(
        (int)(settings_->GetColorVertex().g * 100.0f));
    ui_->slider_color_b->setValue(
        (int)(settings_->GetColorVertex().b * 100.0f));
  } else if (ui_->radioButton_color_line->isChecked()) {
    ui_->slider_color_r->setValue((int)(settings_->GetColorLine().r * 100.0f));
    ui_->slider_color_g->setValue((int)(settings_->GetColorLine().g * 100.0f));
    ui_->slider_color_b->setValue((int)(settings_->GetColorLine().b * 100.0f));
  }
}

//  ===========================  Запись ===========================

/**
 * @brief Создание скриншота
 */
void MainWindow::on_pushButton_screenshot_clicked() {
  QString screenshot_path = NULL;
  if (ui_->radioButton_jpeg->isChecked()) {  //  выбираем формат
    screenshot_path = QFileDialog::getSaveFileName(this, "Save screenshot jpeg",
                                                   "../", "JPEG (*.jpeg)");
    check_filename_format(screenshot_path, ".jpeg");
  } else {
    screenshot_path = QFileDialog::getSaveFileName(this, "Save screenshot bmp",
                                                   "../", "BMP (*.bmp)");
    check_filename_format(screenshot_path, ".bmp");
  }

  if (recording_) {
    delete recording_;
  }
  recording_ = new RecordManager(new ScreenShot(glwidget_, screenshot_path));
  recording_->SetRecording();
  delete recording_;
  recording_ = nullptr;
}

/**
 * @brief Создание gif-анимации
 */
void MainWindow::on_pushButton_gif_clicked() {
  QString gif_path = QFileDialog::getSaveFileName(this, tr("Save GIF"), NULL,
                                                  tr("GIF files (*.gif)"));
  check_filename_format(gif_path, ".gif");
  ui_->pushButton_gif->setDisabled(true);
  ui_->pushButton_screenshot->setDisabled(true);
  if (recording_) {
    delete recording_;
  }
  recording_ = new RecordManager(new GifRecorder(this, glwidget_, gif_path));
  recording_->SetRecording();
}

/**
 * @brief Проверка на наличие формата в названии файла
 */
void MainWindow::check_filename_format(QString& filename, QString format) {
  if (filename.contains(format) == false) {
    filename.append(format);
  }
}

/**
 * @brief Обновление таймера
 */
void MainWindow::update_timer() {
  int seconds = GIF_TIME - cnt_seconds_;
  if (seconds != 0) {
    ui_->label_gif_progress->setText("Идет запись: " +
                                     QString::number(seconds));
    ++cnt_seconds_;
  }
}

/**
 * @brief Завершение таймера
 */
void MainWindow::clear_timer() {
  ui_->label_gif_progress->clear();
  cnt_seconds_ = 0;
  ui_->pushButton_gif->setEnabled(true);
  ui_->pushButton_screenshot->setEnabled(true);
}

}  // namespace s21
