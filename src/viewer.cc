#include <iostream>
#include <QGuiApplication>
#include <QSurfaceFormat>
#include <QOpenGLContext>

#include "window/glwindow.hh"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);

    // Request OpenGL 4.5 compatibility
    qDebug("Requesting 4.5 Core context");
    fmt.setVersion(4, 5);
    fmt.setProfile(QSurfaceFormat::CoreProfile);

    QSurfaceFormat::setDefaultFormat(fmt);

    GLWindow glWindow;
    glWindow.showNormal();

    return app.exec();
}