#ifndef DISHTOOLS_H
#define DISHTOOLS_H

#include <QSlider>
#include <QGroupBox>
#include <QBoxLayout>
#include <QPushButton>
#include <QSlider>
#include "dish.h"
#include "blob.h"
#include "tessel.h"

class DishTools : public QGroupBox
{
    Q_OBJECT

public:
    DishTools(Dish * canv);
    //QWidget * getColorSelected(){return colorSelected;};

private:
    Dish * canvas = nullptr;
    QSlider * sizePicker = nullptr;
    QColor blobColor = QColor(230, 230, 230);
    QColor pickedColor = QColor(230, 230, 230);
    QWidget * blobColorWidget = nullptr;
    QWidget * pickedColorWidget = nullptr;

public slots:
    void setBlobSize(int p);
    void setBlobColor();
    void setDefaultValues(Blob * b );
    void addBlob();
    void paintEvent(QPaintEvent*);
    void blobColorChange(Blob* b);
    void setPickedColor(QColor c) {
        pickedColor = c;
        update();}

};

#endif // DISHTOOLS_H
