#ifndef CPP4_3DVIEWER_V2_SRC_VIEW_GLWIDGET_H
#define CPP4_3DVIEWER_V2_SRC_VIEW_GLWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QWidget>
#include <iostream>

#include "../controller/controller_object.h"
#include "./settings.h"

namespace s21 {
class GLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT

 public:
  GLWidget(s21::ControllerObject* controller_ptr, QWidget* parent = nullptr);
  ~GLWidget();
  QImage getScreenshot();

 private:
  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;
  void setProjectionMode(int mode);
  void drawPoints();
  void drawLines();
  void drawAxes();

 private:
  s21::ControllerObject* controller_;
  Settings* settings_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_SRC_VIEW_GLWIDGET_H
