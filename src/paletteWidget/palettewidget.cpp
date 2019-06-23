#include "palettewidget.h"
#include "blob.h"
#include "dish.h"
#include "dishtools.h"


PaletteWidget::PaletteWidget(QWidget *parent) :
    QWidget(parent)
{
    std::vector<Blob*> blobs = std::vector<Blob*>();
    Dish * canva = new Dish(this,300, 300, blobs);

    buttonZone = new DishTools(canva);
    //setCentralWidget(new Canvas(this));

    QHBoxLayout * mainLayout = new QHBoxLayout(this);

    mainLayout->addWidget(buttonZone);
    mainLayout->addWidget(canva);
    connect(canva, SIGNAL(colorPicked(QColor)), this, SLOT(sendColorPicked(QColor)));
    connect(canva, SIGNAL(colorPicked(QColor)), buttonZone, SLOT(setPickedColor(QColor)));


}

PaletteWidget::~PaletteWidget()
{

}
