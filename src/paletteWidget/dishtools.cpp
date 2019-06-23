#include "dishtools.h"
#include <QColorDialog>
#include <QLabel>

DishTools::DishTools(Dish * canv) : QGroupBox("Outils")
{
    canvas = canv;

    blobColorWidget = new QWidget();
    QPushButton * colorPicker = new QPushButton("Color Picker");
    QPushButton * newBlob = new QPushButton("Add Blob");
    QPushButton * blobColorPicker = new QPushButton("Blob Color");
    sizePicker = new QSlider(Qt::Horizontal);
    blobColorWidget->setMaximumHeight(50);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, blobColor);
    blobColorWidget->setAutoFillBackground(true);
    blobColorWidget->setPalette(pal);

    pickedColorWidget = new QWidget();
    pickedColorWidget->setMaximumHeight(50);
    pal = palette();
    pal.setColor(QPalette::Background, QColor(254, 253, 240));
    pickedColorWidget->setAutoFillBackground(true);
    pickedColorWidget->setPalette(pal);

    QVBoxLayout * sideButtons = new QVBoxLayout();
    sideButtons->addWidget(new QLabel("picked color : "));
    sideButtons->addWidget(pickedColorWidget);
    sideButtons->addWidget(colorPicker);
    sideButtons->addWidget(new QLabel("blob color : "));
    sideButtons->addWidget(blobColorWidget);
    sideButtons->addWidget(blobColorPicker);
    sideButtons->addWidget(sizePicker);
    sideButtons->addWidget(newBlob);


    sizePicker->setMinimum(5);
    sizePicker->setMaximum(20);
    sizePicker->setValue(8);

    connect(colorPicker, SIGNAL(clicked()), canvas, SLOT(setPickedModeOn()));
    connect(blobColorPicker, SIGNAL(clicked()), this, SLOT(setBlobColor()));
    connect(sizePicker, SIGNAL(sliderMoved(int)), this, SLOT(setBlobSize(int)));
    connect(canvas, SIGNAL(doubleClickOn(Blob*)), this, SLOT(setDefaultValues(Blob *)));
    connect(newBlob, SIGNAL(clicked()), this, SLOT(addBlob()));
    connect(canvas,SIGNAL(doubleClickOn(Blob*)),this, SLOT(blobColorChange(Blob*)));
    setLayout(sideButtons);
}

void DishTools::setBlobSize(int ray){
    Blob * b = canvas->getSelectedBlobEdit();
    if (b) {
        b->setRadius(ray);
        canvas->update();
    }
}

void DishTools::setDefaultValues(Blob * b ){
    if (b) {
        sizePicker->setValue(b->getRadius());
    }
}

void DishTools::setBlobColor(){
    Blob * b = canvas->getSelectedBlobEdit();
    if (b) {
        QPalette pal = palette();
        QColor color = QColorDialog::getColor(b->getColor(), nullptr);
        blobColor = color;

        b->setColor(blobColor);
        pal.setColor(QPalette::Background, blobColor);
        blobColorWidget->setAutoFillBackground(true);
        blobColorWidget->setPalette(pal);

    }
    else{
        QColor color = QColorDialog::getColor(blobColor, nullptr);
        blobColor = color;
        QPalette pal = palette();
        pal.setColor(QPalette::Background, blobColor);
        blobColorWidget->setAutoFillBackground(true);
        blobColorWidget->setPalette(pal);

    }
    update();
    canvas->setPickedModeOff();
    canvas->update();
}

void DishTools::addBlob() {
    Blob * b = new Blob(blobColor,
                   QPoint(50, 50),
                   50);

    b->setRadius(sizePicker->value());
    canvas->addBlob(b);
    canvas->setPickedModeOff();
    canvas->paintGL();
    canvas->update();
}

void DishTools::paintEvent(QPaintEvent* e) {
    QPalette pal = palette();
    pal.setColor(QPalette::Background, blobColor);
    blobColorWidget->setAutoFillBackground(true);
    blobColorWidget->setPalette(pal);

    QPalette pal2 = palette();

    QColor c = pickedColor;
    pal2.setColor(QPalette::Background, pickedColor);
    pickedColorWidget->setAutoFillBackground(true);
    pickedColorWidget->setPalette(pal2);
}

void DishTools::blobColorChange(Blob *b) {
    QColor c = b->getColor();
    blobColor = c;
    update();
}
