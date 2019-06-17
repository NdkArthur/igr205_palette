#include "glwidget.h"
#include "model.hh"


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


GLWidget::GLWidget(QWidget *parent, Model* m) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent){
    xRot = 0;
    yRot = 0;
    zRot = 0;
    model = m;
}

QSize GLWidget::minimumSizeHint() const{
    return QSize(500, 150);
}

QSize GLWidget::sizeHint() const{
    return QSize(400, 400);
}


void GLWidget::initializeGL(){
    QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    f->glClearColor(0.3f, 0.f, 0.f, 1.0f);

    std::cout<<"###\nintialized GL widget : start" <<std::endl;

    f->glEnable(GL_DEPTH_TEST);
    std::cout<<"load model : start" <<std::endl;
//    glview.model;
//    model = Model::load(PROJECT_DIR "/assets/WaterBottle/WaterBottle.gltf");
    std::cout<<"load model : end" <<std::endl;
    std::cout<<"load shaders : start" <<std::endl;
    program_.removeAllShaders();
    program_.addShaderFromSourceFile(QOpenGLShader::Vertex, verts_filename);
    program_.addShaderFromSourceFile(QOpenGLShader::Fragment, frags_filename);
    program_.link();
    std::cout<<"load shaders : end" <<std::endl;

    //color_map = model->getColormap();
    QOpenGLTexture * test = new QOpenGLTexture(QImage(PROJECT_DIR "/assets/WaterBottle/WaterBottle_baseColor.png"));
    std::cout<<"send attributes to GPU : start" <<std::endl;
    int tex_unit_count = 0;

    test->bind(tex_unit_count);
    program_.setUniformValue("color_map", tex_unit_count);

    std::cout<<"send attributes to GPU : end" <<std::endl;
    m_posAttrib = program_.attributeLocation("vtx_positions");

    std::cout<<"intialized GL widget : end" <<std::endl;
}

void GLWidget::render(){
    QOpenGLFunctions * f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    f->glClearColor(0.3f, 0.f, 0.f, 1.0f);

    program_.bind();
    GLfloat vertices[12] = {
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f,-1.0f, 0.0f,
        -1.0f,-1.0f, 0.0f
    };

    f->glVertexAttribPointer(m_posAttrib, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    f->glEnableVertexAttribArray(0);
    f->glDrawArrays(GL_TRIANGLES, 0, 4);
    f->glDisableVertexAttribArray(0);

    program_.release();
}

void GLWidget::resizeGL(int width, int height){


}

void GLWidget::paintGL(){
    render();
}

void GLWidget::mousePressEvent(QMouseEvent *event){

}

void GLWidget::mouseMoveEvent(QMouseEvent *event){

}

//bool GLWidget::loadProgram()
//{
//    program_.removeAllShaders();
//    program_.addShaderFromSourceFile(QOpenGLShader::Vertex, verts_filename);
//    program_.addShaderFromSourceFile(QOpenGLShader::Fragment, frags_filename);
//    bool link_res = program_.link();
//    if (link_res)
//        last_link_ = QDateTime::currentDateTime();

//    return link_res;
//}

void GLWidget::loadTexture(QString textureName)
{
    QImage Texture;
    QImage TempTexture;
    TempTexture.load(textureName);
    Texture = QGLWidget::convertToGLFormat(TempTexture);
//    glGenTextures( 1, &m_texture[0] );
//    glBindTexture( GL_TEXTURE_2D, m_texture[0] );
//    glTexImage2D( GL_TEXTURE_2D, 0, 3, Texture.width(), Texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, Texture.bits() );
//    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
//    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}
