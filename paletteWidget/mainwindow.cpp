#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "blob.h"
#include "dish.h"
#include "canvas.h"
#include "dishtools.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Canvas * canva = new Canvas(this);

    buttonZone = new DishTools(canva);
    //setCentralWidget(new Canvas(this));

    QHBoxLayout * mainLayout = new QHBoxLayout();
    QWidget * mainWidget = new QWidget();

    mainLayout->addWidget(buttonZone);
    mainLayout->addWidget(canva);
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
