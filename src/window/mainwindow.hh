#pragma once

#include <QMainWindow>
#include "glview.hh"

class MainWindow : public QMainWindow
{
public:
    MainWindow();

private:
    GLView *gl_view_;
};