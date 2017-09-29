#ifndef VIEW_H
#define VIEW_H

#include "windows.h"
#include <QGLWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QWidget>
#include <glut/glut.h>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QVector3D>
#include <QMatrix4x4>
#include <QGLShaderProgram>
#include <QGLShader>
#include <QGraphicsView>
#include <iostream>
#include <QOpenGLShaderProgram>
#include "camera.h"

class View : public QGLWidget
{
    Q_OBJECT
public:
    View();
protected:
    void initializeGL();

private:
    QOpenGLShaderProgram  *shaderProgram;
    QGLShader *vertexShader;
    QGLShader *fragmentShader;
};

#endif // VIEW_H
