#pragma once

#include <QOpenGLWindow>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QDateTime>

class GLWindow : public QOpenGLWindow
{
  Q_OBJECT

public:
  GLWindow();
  ~GLWindow();

  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);

private slots:
  void checkShaders();

private:
  bool loadProgram();

  QOpenGLShaderProgram program_;
  QDateTime last_link_;
  QOpenGLVertexArrayObject vao_;
};