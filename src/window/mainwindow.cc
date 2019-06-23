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
    toolLayout->addStretch(5);
    toolLayout->addWidget(palette);
    toolLayout->addStretch(5);

    gl_view_ = new GLView(this);
    visuLayout->addWidget(gl_view_);
    mainLayout->addLayout(visuLayout);
    mainLayout->addLayout(toolLayout);


    glWidget = new GLWidget(this);

    visuLayout->addWidget(glWidget);
    visuLayout->addStretch(5);

    setCentralWidget(cw);

    QToolBar *tool_bar = new QToolBar("Tools", this);
    addToolBar(Qt::LeftToolBarArea, tool_bar);

    // Setup CheckBox for toggle pbr/color map rendering
    QCheckBox *checkbox = new QCheckBox("Only Color Map", tool_bar);
    tool_bar->addWidget(checkbox);
    tool_bar->addSeparator();

    QSlider *penWidth = new QSlider(Qt::Orientation::Horizontal,this);
    penWidth->setRange(1,10);
    tool_bar->addWidget(new QLabel("Pen width"));
    tool_bar->addWidget(penWidth);

    QPushButton * saveButton = new QPushButton("Save");
    tool_bar->addWidget(saveButton);


    connect(checkbox, SIGNAL(toggled(bool)), gl_view_, SLOT(toggleColorMap(bool)));
    connect(gl_view_, SIGNAL(loadedModel(Model*)), glWidget, SLOT(updateTexture(Model*)));
    connect(gl_view_, SIGNAL(clicked(QVector2D)), glWidget, SLOT(updateTextCoord(QVector2D)));
    connect(palette, SIGNAL(colorPicked(QColor)), glWidget, SLOT(setBrushColor(QColor)));
    connect(penWidth, SIGNAL(valueChanged(int)), glWidget, SLOT(setBrushWidth(int)));
    connect(saveButton, SIGNAL(clicked()), glWidget, SLOT(save()));
    connect(glWidget, SIGNAL(drawn()), gl_view_, SLOT(update()));

}

