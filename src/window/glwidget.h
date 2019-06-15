#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QtOpenGL>
#include <QGLWidget>

#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QDateTime>
#include "model.hh"
#include "trackball.hh"
#include "glview.hh"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QGLWidget{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0, Model * m = nullptr);
    ~GLWidget(){}

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void render();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    int xRot;
    int yRot;
    int zRot;
    QOpenGLTexture * color_map;
    bool loadProgram();

    QOpenGLShaderProgram program_;
    QDateTime last_link_;

    TrackBall trackball_;
    QMatrix4x4 proj_mat_;
    bool only_color_map;

    float width_, height_;
    float fov_ = 45.0;

    void loadTexture(QString textureName);

    Model * model;
//    GLView * glview = new GLView();

    GLuint m_posAttrib;
};

#endif // GLWIDGET_H
