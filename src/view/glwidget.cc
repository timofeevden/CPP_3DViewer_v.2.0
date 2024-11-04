#include "glwidget.h"

namespace s21 {

/**
 * @brief Конструктор нашего GL-widget-а
 * * @param controller_ptr указатель на контроллер
 * * @param parent указатель на родительский виджет при необходимости
 */
GLWidget::GLWidget(s21::ControllerObject* controller_ptr, QWidget* parent)
    : QOpenGLWidget(parent), controller_(controller_ptr) {
  settings_ = Settings::GetInstance();
}

/**
 * @brief Деструктор
 */

GLWidget::~GLWidget() {}

/**
 * @brief Переопределенный метод инициализации OpenGL
 */
void GLWidget::initializeGL() {
  this->initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

/**
 * @brief Переопределенный метод отрисовки OpenGL
 */
void GLWidget::paintGL() {
  if (controller_ != nullptr) {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(settings_->GetColorBackground().r,
                 settings_->GetColorBackground().g,
                 settings_->GetColorBackground().b, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    drawAxes();                            //  оси
    glEnableClientState(GL_VERTEX_ARRAY);  //  включаем использование массива
    setProjectionMode(settings_->GetProjectionMode());
    drawPoints();
    drawLines();
    glDisableClientState(GL_VERTEX_ARRAY);  //  отключаем использование массива
    glFlush();                              //  очистка буферов
  }
  update();
}

/**
 * @brief Установка необходимой проекции
 * * @param mode режим проекции
 */
void GLWidget::setProjectionMode(int mode) {
  if (mode == 1) {  //  выбираем проекцию:
    glFrustum(-0.1, 0.1, -0.1, 0.1, 1.0, 100);
    glTranslatef(0, 0, -10);
  } else {
    glOrtho(-1, 1, -1, 1, -2, 100);
  }
}

/**
 * @brief Отрисовка точек
 */
void GLWidget::drawPoints() {
  float* ptr_vertex_arr = controller_->GetVertexCoords();

  if (ptr_vertex_arr != nullptr) {
    glVertexPointer(3, GL_FLOAT, 0, ptr_vertex_arr);

    if (settings_->GetVertexMode() && settings_->GetVertexSize()) {
      if (settings_->GetVertexMode() == 1) {
        glEnable(GL_POINT_SMOOTH);  //  точка-круг
      } else {
        glDisable(GL_POINT_SMOOTH);  //  точка-квадрат
      }
      glPointSize(settings_->GetVertexSize());  //  размер
      glColor3f(settings_->GetColorVertex().r, settings_->GetColorVertex().g,
                settings_->GetColorVertex().b);                   //  цвет
      glDrawArrays(GL_POINTS, 0, controller_->GetCntVertexes());  //  отрисовка
    }
  }
}

/**
 * @brief Отрисовка линий (полигонов)
 */
void GLWidget::drawLines() {
  if (settings_->GetLineMode() && settings_->GetLineWidth()) {
    if (settings_->GetLineMode() == 2) {
      glEnable(GL_LINE_STIPPLE);  //  задаем пунктир
      glLineStipple(1, 0xFF);
    } else {
      glDisable(GL_LINE_STIPPLE);  //  сплошная линия
    }
    glLineWidth(settings_->GetLineWidth());
    glColor3f(settings_->GetColorLine().r, settings_->GetColorLine().g,
              settings_->GetColorLine().b);
    glDrawElements(GL_LINES, 2 * controller_->GetArrayPolygons().size(),
                   GL_UNSIGNED_INT, controller_->GetArrayPolygons().data());
  }
}

/**
 * @brief Отрисовка координатных осей
 */
void GLWidget::drawAxes() {
  if (settings_->GetAxisMode()) {
    glLineWidth(1);
    glBegin(GL_LINES);
    {
      // x axes
      glColor3f(255, 0, 0);
      glVertex3f(-1, 0, 0);
      glVertex3f(1, 0, 0);

      // y axes
      glColor3f(255, 0, 0);
      glVertex3f(0, -1, 0);
      glVertex3f(0, 1, 0);

      // z axes
      glColor3f(255, 0, 0);
      glVertex3f(0, 0, -1);
      glVertex3f(0, 0, 1);
    }
    glEnd();
  }
}

/**
 * @brief Взятие изображения картинки на данный момент
 */
QImage GLWidget::getScreenshot() {
  glFlush();
  return grabFramebuffer();
}

/**
 * @brief Переопределенный метод отрисовки OpenGL
 * * @param width ширина
 * * @param height высота
 */
void GLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}
}  // namespace s21
