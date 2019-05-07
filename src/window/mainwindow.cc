#include "mainwindow.hh"
#include <QCheckBox>
#include <QToolBar>

MainWindow::MainWindow()
{
    gl_view_ = new GLView(this);
    setCentralWidget(gl_view_);

    QToolBar *tool_bar = new QToolBar("Tools", this);
    addToolBar(Qt::LeftToolBarArea, tool_bar);

    // Setup CheckBox for toggle pbr/color map rendering
    QCheckBox *checkbox = new QCheckBox("Only Color Map", tool_bar);
    tool_bar->addWidget(checkbox);
    connect(checkbox, SIGNAL(toggled(bool)), gl_view_, SLOT(toggleColorMap(bool)));
}