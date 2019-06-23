#include "dish.h"
#include <tuple>
#include <math.h>
#include <QVector3D>
#include <string>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions_4_5_Core>
#include <iostream>

const char *dish_verts_filename = PROJECT_DIR "/src/shaders/dish.vert";
const char *dish_frags_filename = PROJECT_DIR "/src/shaders/dish.frag";


Dish::Dish(QWidget * parent, int height, int width, std::vector<Blob*> b) : QOpenGLWidget (parent){

    blobs = b;
    setMinimumSize(QSize(height, width));
    setMaximumSize(QSize(height, width));
    std::vector<Blob*> blobs= std::vector<Blob*>();
    setMouseTracking(true);

}

void Dish::initializeGL() {
    makeCurrent();
    QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.3f, 0.f, 0.f, 1.0f);
    program_.removeAllShaders();
    program_.addShaderFromSourceFile(QOpenGLShader::Vertex, dish_verts_filename);
    program_.addShaderFromSourceFile(QOpenGLShader::Fragment, dish_frags_filename);
    program_.link();
    std::cout << program_.isLinked();
    vao_ptr = std::make_unique<QOpenGLVertexArrayObject>(new QOpenGLVertexArrayObject() );
    vao_ptr->create();
    doneCurrent();

}

void Dish::paintGL() {

    makeCurrent();

    QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT );

    program_.bind();

    program_.setUniformValue("treshold", treshold);
    program_.setUniformValue("nbOfBlobs", int(blobs.size()));

    unsigned int n = uint(std::min(int(blobs.size()), 20));
    for (unsigned int i =0; i < n; i++) {
        QColor c = blobs[i]->getColor();
        QPoint p = blobs[i]->getCenter();

        QString blob_color = QString("blobs[%1].color").arg(i);
        QString blob_center = QString("blobs[%1].center").arg(i);
        QString blob_radius = QString("blobs[%1].radius").arg(i);


        QByteArray ba = blob_color.toLocal8Bit();
        const char *c_co = ba.data();

        ba = blob_center.toLocal8Bit();
        const char *c_ce = ba.data();

        ba = blob_radius.toLocal8Bit();
        const char *c_r = ba.data();

        program_.setUniformValue(c_ce, p.x()/float(width()),(1.0-p.y()/float(height())));
        program_.setUniformValue(c_r, float(blobs[i]->getRadius()/10.0));
        program_.setUniformValue(c_co, c.redF(), c.greenF(), c.blueF());
    }

    vao_ptr->bind();
    f->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    vao_ptr->release();
    program_.release();
    doneCurrent();

}

QColor Dish::getPixel(QPoint p) {
    makeCurrent();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    float pix[4];
    f->glReadPixels(p.x(),int(height()) - p.y(), 1, 1, GL_RGBA, GL_FLOAT, pix);
    doneCurrent();
    return QColor(int(255*pix[0]), int(255*pix[1]), int(255*pix[2]));
}

void Dish::mousePressEvent(QMouseEvent * e){

    QRect clickRect = QRect((e->pos()), QSize(3,3));
    selectedBlobMove = nullptr;
    if (!pickedModeIsOn) {
        for(unsigned int i = 0; i < blobs.size(); i++){
            float rad = blobs[i]->getRadius();
            float l = 6*rad;
            QRect blobRect = QRect(blobs[i]->getCenter()-QPoint(0.7*l*2/3,0.7*l*2/3), QSize(l,l));
            if(blobRect.intersects(clickRect)){
                moveIsOn = true;
                selectedBlobMove = blobs[i];
                emit dragOn(selectedBlobMove);
                break;
            }
        }
    }

    update();
}

void Dish::mouseMoveEvent(QMouseEvent * e){

    if (pickedModeIsOn) {
        currentPos =  this->mapFromGlobal(QCursor::pos());
        emit colorPicked(getPixel(e->pos()));
    }

    else if (selectedBlobMove && moveIsOn && (e->buttons() & Qt::LeftButton) ) {
        selectedBlobMove->setCenter(e->pos());
        setCursor(QCursor(Qt::ClosedHandCursor));

    }

    update();
}

void Dish::mouseReleaseEvent(QMouseEvent * e){

    if(moveIsOn) {
        selectedBlobMove = nullptr;
        emit dragOff();
        moveIsOn = false;
        setCursor(QCursor(Qt::ArrowCursor));
    }
    update();

}

void Dish::mouseDoubleClickEvent(QMouseEvent * e){

    QRect clickRect = QRect((e->pos()), QSize(3,3));
    selectedBlobEdit = nullptr;
    //setPickedModeOff();
    if (!pickedModeIsOn) {
        for(unsigned int i = 0; i < blobs.size(); i++){
            float rad = blobs[i]->getRadius();
            float l = 5*rad;
            QRect blobRect = QRect(blobs[i]->getCenter()-QPoint(0.7*l*2/3,0.7*l*2/3), QSize(l,l));
            if(blobRect.intersects(clickRect)){
                selectedBlobEdit = blobs[i];

                emit doubleClickOn(selectedBlobEdit);
                break;
            }
        }

        if (!selectedBlobEdit) {
            emit doubleClickOff();
        }
    }
    else {
        setPickedModeOff();
    }

    update();
}

void Dish::resizeGL(int width, int height){
    makeCurrent();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glViewport(0, 0, width, height);
    doneCurrent();

}

void Dish::paintEvent(QPaintEvent*e) {
    paintGL();
    QPainter p;
    p.begin(this);

    if (selectedBlobEdit) {
        p.setBrush(Qt::black);
        p.drawEllipse(QRect((selectedBlobEdit->getCenter())-QPoint(15/4,15/4), QSize(5,5)));
    }
    if(pickedModeIsOn){
        p.setPen(Qt::black);
        p.setBrush(QBrush(getPixel(currentPos)));
        float l = 3*20/4;
        p.drawEllipse(QRect(currentPos-QPoint(0.7*l*2/3,0.7*l*2/3), QSize(20, 20)));
    }

    p.end();
}

