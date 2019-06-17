#include "mainwindow.hh"
#include <QCheckBox>
#include <QToolBar>
#include <QWidget>
#include <QBoxLayout>
#include "../paletteWidget/palettewidget.h"
#include <QPixmap>

MainWindow::MainWindow()
{
    QWidget * cw = new QWidget(this);

    QVBoxLayout * mainLayout = new QVBoxLayout(cw);
    QHBoxLayout * visuLayout = new QHBoxLayout();
    QHBoxLayout * toolLayout = new QHBoxLayout();
    palette = new PaletteWidget(this);
    toolLayout->addWidget(palette);
    toolLayout->addStretch(5);



//    connect(xSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setXRotation(int)));
//    connect(glWidget, SIGNAL(xRotationChanged(int)), xSlider, SLOT(setValue(int)));
//    connect(ySlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setYRotation(int)));
//    connect(glWidget, SIGNAL(yRotationChanged(int)), ySlider, SLOT(setValue(int)));
//    connect(zSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setZRotation(int)));
//    connect(glWidget, SIGNAL(zRotationChanged(int)), zSlider, SLOT(setValue(int)));

    gl_view_ = new GLView(this);
    visuLayout->addWidget(gl_view_);
    mainLayout->addLayout(visuLayout);
    mainLayout->addLayout(toolLayout);


//    glWidget = new GLWidget(this, gl_view_->getModel());

//    visuLayout->addWidget(glWidget);
    visuLayout->addStretch(5);

    setCentralWidget(cw);

    QToolBar *tool_bar = new QToolBar("Tools", this);
    addToolBar(Qt::LeftToolBarArea, tool_bar);

    // Setup CheckBox for toggle pbr/color map rendering
    QCheckBox *checkbox = new QCheckBox("Only Color Map", tool_bar);
    tool_bar->addWidget(checkbox);
    connect(checkbox, SIGNAL(toggled(bool)), gl_view_, SLOT(toggleColorMap(bool)));
}
