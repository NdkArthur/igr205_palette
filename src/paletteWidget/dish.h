#ifndef DISH_H
#define DISH_H
#include "blob.h"
#include <QColor>
#include <QImage>
#include <iostream>

#include <QOpenGLWidget>
#include <QtOpenGL>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QDateTime>


class Dish : public QOpenGLWidget
{
    Q_OBJECT
private :

    std::vector<Blob*> blobs= std::vector<Blob*>();
    float treshold = 0.45;
    void pixelShader(QPoint p);
    bool loadProgram();
    QOpenGLShaderProgram program_;
    QDateTime last_link_;
    std::unique_ptr<QOpenGLVertexArrayObject>  vao_ptr;

    int canvasWidth = 300;
    int canvasHeight = 300;
    bool moveIsOn = false;
    Blob * selectedBlobMove = nullptr;
    Blob * selectedBlobEdit = nullptr;
    bool pickedModeIsOn = false;
    QState * passiveState = nullptr;
    QState * moveBlob = nullptr;
    QState * editBlob = nullptr;
    QStateMachine * mac = nullptr;
    QPoint currentPos = QPoint(0,0);

public :

    Dish(QWidget * parent) : QOpenGLWidget (parent) {
        setMinimumSize(QSize(200, 200));
        setMaximumSize(QSize(200, 200));
    }

    ~Dish() {
        makeCurrent();
        doneCurrent();
    }

    Dish(QWidget * parent, int height, int width, std::vector<Blob*> b);

    void addBlob(Blob * b) {
        blobs.push_back(b);
    }

    std::vector<Blob*> getBlobs(){
        return blobs;
    }

    Blob * getSelectedBlobMove(){
        return selectedBlobMove;
    }
    Blob * getSelectedBlobEdit(){
        return selectedBlobEdit;
    }

    void setSelectedBlobEdit(Blob * b) {selectedBlobEdit = b;}

    void paintGL();
    void initializeGL();
    void resizeGL(int width, int height);
    QColor getPixel(QPoint p);

public slots:
    void paintEvent(QPaintEvent*);
    void setPickedModeOn(){
        pickedModeIsOn = true;
        selectedBlobEdit = nullptr;
        setCursor(QCursor(Qt::CrossCursor));
        update();}

    void setPickedModeOff(){
        pickedModeIsOn = false;
        setCursor(QCursor(Qt::ArrowCursor));
        update();}

signals:
    void dragOn(Blob * b);
    void dragOff();
    void doubleClickOn(Blob * b);
    void doubleClickOff();
    void colorPicked(QColor c);

protected:
    void mousePressEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
    void mouseDoubleClickEvent(QMouseEvent * e);
};



#endif // DISH_H
