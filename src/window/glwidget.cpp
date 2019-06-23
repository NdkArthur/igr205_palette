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
const char *draw_frags_filename = PROJECT_DIR "/src/shaders/draw.frag";

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

    draw_program_.removeAllShaders();
    draw_program_.addShaderFromSourceFile(QOpenGLShader::Vertex, verts_filename);
    draw_program_.addShaderFromSourceFile(QOpenGLShader::Fragment, draw_frags_filename);
    draw_program_.link();
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
    
    vao_ptr->bind();
    f->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    vao_ptr->release();
    program_.release();

}



void GLWidget::draw() {


    QOpenGLFramebufferObjectFormat format ;
    format.setInternalTextureFormat(QOpenGLTexture::SRGB8_Alpha8);
    QOpenGLFramebufferObject * fbo = new QOpenGLFramebufferObject( color_map->width(),color_map->height(), format);

    if (fbo->bind()) {
        QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();
        f->glViewport(0,0,color_map->width(),color_map->height());
        f->glEnable(GL_FRAMEBUFFER_SRGB);

        f->glClear(GL_COLOR_BUFFER_BIT );


        draw_program_.bind();
        int tex_unit_count = 0;
        color_map->bind(tex_unit_count);
        draw_program_.setUniformValue("color_map", tex_unit_count);
        GLfloat position[2];
        position[0] = currentTextCoord.x();
        position[1] = currentTextCoord.y();
        draw_program_.setUniformValue("click_coord", QPointF(currentTextCoord.x(), currentTextCoord.y()));
        draw_program_.setUniformValue("brush_color", float(brushColor.redF()) , float(brushColor.greenF()), float(brushColor.blueF()));
        draw_program_.setUniformValue("brush_width",brushWidth);

        vao_ptr->bind();
        f->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        vao_ptr->release();
        draw_program_.release();

        static int lala = 0 ;
        if (lala<2) {
            QImage textCoord = fbo->toImage();
            textCoord.save("frameBuffetTest.png");
            lala += 1;
        }


        f->glCopyImageSubData(fbo->texture(),GL_TEXTURE_2D,0,0,0,0,
                              color_map->textureId(),GL_TEXTURE_2D,0,0,0,0,color_map->width(),color_map->height(),1);
        fbo->release();
        f->glViewport(0,0,width(),height());


    }
    delete fbo;



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



void GLWidget::mouseMoveEvent(QMouseEvent *event){

    if (event->buttons() & Qt::LeftButton) {
        updateTextCoord(QVector2D(float(event->pos().x())/width(), 1-float(event->pos().y())/height()));
        emit drawn();
    }
}

void GLWidget::save() {
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save texture"), "",
            tr("Image (*.png *.jpg);;All Files (*)"));
    QOpenGLFramebufferObject * fbo = new QOpenGLFramebufferObject(width(), height());
    makeCurrent();
    if (fbo->bind()) {
        QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();
        render();
        QImage im = fbo->toImage();
        im.save(fileName);
        fbo->release();
        f->glViewport(0,0,width(),height());
    }

    doneCurrent();



}

