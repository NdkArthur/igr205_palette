#ifndef TEXTURE2D_H
#define TEXTURE2D_H
#include <QPoint>
#include <QObject>
#include "blob.h"
#include "tessel.h"
#include <QHash>

typedef QHash<QPoint, Tessel> TesselMap;

class Texture2D : public QImage
{
public:
    Texture2D() : QImage(QSize(200, 200), QImage::Format_RGB16) {}
    Texture2D(int height, int width) : QImage(QSize(height, width), QImage::Format_RGB16) {
        mosaique = TesselMap();
    }
    void setTessel(QPoint p, Tessel t) {mosaique.insert(p,t);}
    Tessel getTessel(QPoint p) {return mosaique[p];}
    void paint();

private :
    TesselMap mosaique;
};

#endif // TEXTURE2D_H
