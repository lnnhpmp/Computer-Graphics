#ifndef MOUSECONTROLLER_H
#define MOUSECONTROLLER_H

#include <QObject>
#include <QMouseEvent>
#include <QVector2D>
#include <QVector3D>
#include "glwidget.h"
#include "camera.h"
#include "model.h"
#include <iostream>

class MouseController : public QObject
{
    Q_OBJECT

signals:
    void updateViewport();

public:
    MouseController(QObject *parent = 0, GLWidget *viewport = 0, Camera *camera = 0, Model *model = 0);
    QVector3D mapPointToTrackball(float x, float y);

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
private:
    GLWidget *ViewPort;
    QVector2D lastTranslationPoint;
    QVector3D lastRotationPoint;

    float trackballRadius;

    Camera *camera_;
    Model *model_;
};

#endif // MOUSECONTROLLER_H
