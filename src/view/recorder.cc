#include "recorder.h"

#include "mainwindow.h"

namespace s21 {

/**
 * @brief Констрктор класса ScreenShot
 * * @param gl указатель на виджет, с которого будет браться скриншот
 * * @param filename полное название файла для сохранения
 */
ScreenShot::ScreenShot(GLWidget* gl, QString filename)
    : gl_(gl), filename_(filename) {}

/**
 * @brief Переопреденный метод записи
 */
void ScreenShot::Record() {
  QImage img = gl_->getScreenshot();
  img.save(filename_);
}

/**
 * @brief Констрктор класса GifRecorder
 * * @param ui указатель на главное окно
 * * @param gl указатель на виджет, с которого будет браться гиф
 * * @param filename полное название файла для сохранения
 */
GifRecorder::GifRecorder(MainWindow* ui, GLWidget* gl, QString filename)
    : gl_(gl),
      ui_(ui),
      filename_(filename),
      timer_(new QTimer(this)),
      timer_seconds_(new QTimer(this)),
      cnt_(0),
      cnt_seconds_(0) {
  connect(timer_, &QTimer::timeout, this, &GifRecorder::DoSnapshot);
  connect(timer_seconds_, &QTimer::timeout, ui_, &MainWindow::update_timer);
  connect(timer_seconds_, &QTimer::destroyed, ui_, &MainWindow::clear_timer);
}

/**
 * @brief Переопреденный метод записи
 */
void GifRecorder::Record() {
  timer_->start(1000 / GIF_FPS);
  timer_seconds_->start(1000);
}

/**
 * @brief Взятие скриншота для гиф
 */
void GifRecorder::DoSnapshot() {
  if (cnt_ < GIF_TIME * GIF_FPS) {
    gif_vector_.push_back(gl_->getScreenshot());  //  сохраняем снимок в вектор:
    ++cnt_;
  } else {
    timer_->stop();
    timer_seconds_->stop();
    SaveGif();
    cnt_ = 0;
    delete timer_;
    delete timer_seconds_;
  }
}

/**
 * @brief Сохранеие гиф
 */
void GifRecorder::SaveGif() {
  QGifImage gifka(QSize(GIF_SIZE));
  gifka.setDefaultDelay(1000 / GIF_FPS);  // выставляем задержку
  QVector<QImage>::Iterator snapshots = gif_vector_.begin();
  QVector<QImage>::Iterator end = gif_vector_.end();
  while (snapshots != end) {
    *snapshots = snapshots->scaled(GIF_SIZE, Qt::IgnoreAspectRatio);
    gifka.addFrame(*snapshots);  //  добавляем кадр
    ++snapshots;
  }
  gifka.save(filename_);
  gif_vector_.clear();  //  очищает вектор
}
}  // namespace s21
