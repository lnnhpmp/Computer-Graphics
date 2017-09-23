#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "windows.h"
#include <QWidget>
#include <QOpenGLWidget>
#include <qopenglfunctions_4_5_core.h>
#include <glut/glut.h>
#include "cube.h"
#include <QOpenGLShader>
#include <QGLShader>
#include <QGLWidget>

class GLWidget : public QGLWidget//, protected QOpenGLFunctions_4_4_Core
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void initShaders();
    void setMaterial();

private:
    Cube *mycube;
    int tessellationN;
    QOpenGLShaderProgram *shaderProgram;

public slots:
    void setFlatMode();
    void setWireFrameMode();
    void setGouraudMode();
    void setPhongMode();
    void setTessellation(int t);
};

#endif // GLWIDGET_H
