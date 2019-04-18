#include "glwindow.hh"

#include <QOpenGLExtraFunctions>
#include <QTimer>
#include <QFileInfo>
#include <iostream>

const char *vert_filename = PROJECT_DIR "/src/shaders/simple.vert";
const char *frag_filename = PROJECT_DIR "/src/shaders/simple.frag";

GLWindow::GLWindow()
{
    // Setup a timer to check periodically if the shader files have been modified
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(checkShaders()));
    timer->start();
}

GLWindow::~GLWindow()
{
}

void GLWindow::initializeGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.2, 0.2, 0.2, 1);
    loadProgram();
    vao_.create();
}

void GLWindow::paintGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (program_.isLinked())
    {
        program_.bind();
        vao_.bind();
        f->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
}

void GLWindow::resizeGL(int w, int h)
{
}

// Reload shaders if they have been modified since the last link
void GLWindow::checkShaders()
{
    QDateTime vdata = QFileInfo(vert_filename).lastModified();
    QDateTime fdata = QFileInfo(frag_filename).lastModified();
    if (vdata > last_link_ || fdata > last_link_)
    {
        loadProgram();
        update();
    }
}

bool GLWindow::loadProgram()
{
    program_.removeAllShaders();
    program_.addShaderFromSourceFile(QOpenGLShader::Vertex, vert_filename);
    program_.addShaderFromSourceFile(QOpenGLShader::Fragment, frag_filename);
    bool link_res = program_.link();
    if (link_res)
        last_link_ = QDateTime::currentDateTime();

    return link_res;
}