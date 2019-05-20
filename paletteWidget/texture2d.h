#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <QObject>
#include "blob.h"
typedef std::map<QPoint, Tessel> TesselMap;

class Texture2D : public QImage
{
public:
    Texture2D();
    Texture2D() : QImage(QSize(200, 200), QImage::Format_RGB16) {}
    Texture2D(int height, int width, std::vector<Blob*> b) : QImage(QSize(height, width), QImage::Format_RGB16) {
        mosaique = TesselMap();
    }
    void paint();
private :
    TesselMap mosaique;
};

#endif // TEXTURE2D_H
