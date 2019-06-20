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
#include <QPoint>

#include "model.hh"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget(){
        makeCurrent();

    }

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void render();

signals:
    void drawn();

public slots:
    void updateTexture(Model*);
    void updateTextCoord(QVector2D tc);
    void setBrushColor(QColor c) {
        brushColor = c;
        update();
    }
    void setBrushWidth(int w) {
        brushWidth = float(w)/160.0;
        update();
    }
    void draw();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:

    QOpenGLTexture * color_map;
    bool loadProgram();
    QVector2D currentTextCoord = QVector2D(42,42);
    QColor brushColor = QColor(125, 125, 125);
    float brushWidth = 0.001;

    QOpenGLShaderProgram program_;
    QDateTime last_link_;

    float fov_ = 45.0;
    bool moveIsOn = false;

    std::unique_ptr<QOpenGLVertexArrayObject>  vao_ptr;
};

#endif // GLWIDGET_H
