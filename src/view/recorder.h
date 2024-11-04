#ifndef CPP4_3DVIEWER_V2_VIEW_RECORDER_H
#define CPP4_3DVIEWER_V2_VIEW_RECORDER_H

#define GIF_FPS 10
#define GIF_TIME 5
#define GIF_SIZE 640, 480

// #include <gifimage/qgifimage.h>
#include <QMainWindow>
#include <QTimer>

#include "../libs/QtGifImage/src/gifimage/qgifimage.h"
#include "glwidget.h"

namespace s21 {

class MainWindow;

// интерфейс записи
/**
 * @brief Класс для записи
 */
class IRecording {
 public:
  virtual ~IRecording(){};
  virtual void Record() = 0;
};

// Screenshot
/**
 * @brief Класс для записи скриншота
 */
class ScreenShot : public IRecording {
 public:
  ScreenShot(GLWidget* gl, QString filename);
  ~ScreenShot() = default;
  void Record() override;

 private:
  GLWidget* gl_;
  QString filename_;
};

// Gif
/**
 * @brief Класс для записи гиф
 */
class GifRecorder : public QWidget, public IRecording {
  Q_OBJECT
 public:
  GifRecorder(MainWindow* ui, GLWidget* gl, QString filename);
  ~GifRecorder() = default;
  void Record() override;

 private:
  GLWidget* gl_;
  MainWindow* ui_;
  QString filename_;
  QVector<QImage> gif_vector_;
  QTimer* timer_;
  QTimer* timer_seconds_;
  int cnt_;
  int cnt_seconds_;

 private:
  void DoSnapshot();
  void SaveGif();
};

/**
 * @brief Общий класс для записи, реализован паттерном стратегия
 */
class RecordManager {
 public:
  RecordManager(IRecording* rec) : rec_(rec){};
  ~RecordManager() { delete rec_; };
  void SetRecording() { rec_->Record(); }

 private:
  IRecording* rec_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_VIEW_RECORDER_H
