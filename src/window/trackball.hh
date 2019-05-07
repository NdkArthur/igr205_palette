#pragma once

#include <QVector>
#include <QQuaternion>
#include <QMatrix4x4>

class TrackBall
{
public:
    void lookAt(const QVector3D &eye, const QVector3D &target, const QVector3D &up);
    void setTarget(const QVector3D &target);
    bool track(const QPointF &newPoint2D);
    bool zoom(float val, float scale = 0.9);
    void start();
    void stop();
    QMatrix4x4 viewMatrix() { return view_; }
    QVector3D position();

private:
    bool mapToSphere(const QPointF &p2, QVector3D &v3);
    void rotateAroundTarget(float angle, const QVector3D &axis);

    QMatrix4x4 view_;
    QVector3D target_;
    QVector3D last_point_;
    bool last_point_valid_ = false;
    bool is_active_ = false;
};