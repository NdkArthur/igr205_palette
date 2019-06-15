#pragma once

#include <QMainWindow>
#include <QSlider>
#include "glwidget.h"
#include "glview.hh"
#include "../paletteWidget/palettewidget.h"

class MainWindow : public QMainWindow
{
public:
    MainWindow();

private:
    GLView *gl_view_;
    PaletteWidget *palette;
    GLWidget *glWidget;

    QSlider *createSlider();
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
};
