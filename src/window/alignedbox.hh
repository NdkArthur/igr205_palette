#pragma once

#include <QMatrix4x4>
#include <QVector3D>

class AlignedBox
{
public:
    AlignedBox();

    QVector3D minPos() { return min_pos_; }
    QVector3D maxPos() { return max_pos_; }
    float scale() { return (max_pos_ - min_pos_).length(); }
    QVector3D center() { return (max_pos_ + min_pos_) / 2.; }

    void extend(const QVector3D &v);
    void extend(const AlignedBox &b);
    AlignedBox transform(const QMatrix4x4 &m) const;

private:
    QVector3D min_pos_;
    QVector3D max_pos_;
};