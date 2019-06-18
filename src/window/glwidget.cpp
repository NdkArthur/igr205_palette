#include "glwidget.h"



#include <tiny_gltf.h>
#include <QDir>
#include <QDebug>
#include <string>
#include <QOpenGLShaderProgram>
#include <QOpenGLContext>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QVector2D>
#include <vector>
#include <memory>
#include <map>
#include <iostream>
#include <QUuid>
#include <QPixmap>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>

#include <algorithm>
#include <float.h>

const char *verts_filename = PROJECT_DIR "/src/shaders/textureWidget.vert";
const char *frags_filename = PROJECT_DIR "/src/shaders/textureWidget.frag";


GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent){


}

QSize GLWidget::minimumSizeHint() const{
    return QSize(500, 300);
}

QSize GLWidget::sizeHint() const{
    return QSize(500, 500);
}


void GLWidget::initializeGL(){
    makeCurrent();
    QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.3f, 0.f, 0.f, 1.0f);
    program_.removeAllShaders();
    program_.addShaderFromSourceFile(QOpenGLShader::Vertex, verts_filename);
    program_.addShaderFromSourceFile(QOpenGLShader::Fragment, frags_filename);
    program_.link();
    vao_ptr = std::make_unique<QOpenGLVertexArrayObject>(new QOpenGLVertexArrayObject() );
    vao_ptr->create();
    doneCurrent();

}

void GLWidget::updateTexture(Model* model) {
    color_map = model->getColormap();
}

void GLWidget::render(){

    QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT );


    program_.bind();

    int tex_unit_count = 0;

    color_map->bind(tex_unit_count);
    program_.setUniformValue("color_map", tex_unit_count);
    GLfloat position[2];
    position[0] = currentTextCoord.x();
    position[1] = currentTextCoord.y();
    program_.setUniformValue("click_coord", QPointF(currentTextCoord.x(), currentTextCoord.y()));
    float r = brushColor.redF();
    float g = brushColor.greenF();
    float b = brushColor.blueF();
    program_.setUniformValue("brush_color",r , g, b);
    vao_ptr->bind();
    f->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    vao_ptr->release();
    program_.release();

}

void GLWidget::resizeGL(int width, int height){
    makeCurrent();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glViewport(0, 0, width, height);
    doneCurrent();

}

void GLWidget::paintGL(){
    makeCurrent();
    render();
    doneCurrent();
}

void GLWidget::updateTextCoord(QVector2D tc){
    currentTextCoord = tc;
    makeCurrent();
    draw();
    doneCurrent();
    update();
}

void GLWidget::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::RightButton)
    {   makeCurrent();
        draw();
        doneCurrent();

    }

}

void GLWidget::draw() {


//    std::cout << "# Event detected" <<std::endl;
    QOpenGLFramebufferObject * fbo = new QOpenGLFramebufferObject(size(),QOpenGLFramebufferObject::Depth, GL_TEXTURE_2D);
//    std::cout << "###" <<std::endl;
    if (fbo->bind()) {
        render();
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        QImage textureIm = fbo->toImage(false);
        color_map = new QOpenGLTexture(textureIm, QOpenGLTexture::DontGenerateMipMaps);
        fbo->release();
//        std::cout << "###" <<std::endl;

    }
    delete fbo;



}

void GLWidget::mouseMoveEvent(QMouseEvent *event){

    updateTextCoord(QVector2D(float(event->pos().x())/width(), 1-float(event->pos().y())/height()));

}

