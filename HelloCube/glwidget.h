#ifndef GLWIDGET_H
#define GLWIDGET_H

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
#include "model.h"

#define _USE_MATH_DEFINES
#include <math.h>


class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();
    void setCamera(Camera *camera);
    //void glDraw();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    inline void glMultMatrix(const GLfloat  *m);
    inline void glMultMatrix(const GLdouble *m);

    void drawCube();


public slots:
    // shading mode
    void setWireframeShading();
    void setFlatShading();
    void setGouraudShading();
    void setPhongShading();

    void setTesselation(int t);
    void ResetCamera();

    void updateProjectionMatrix();

signals:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    int tesselationSteps;
    float current_z;
    QVector2D lastTranslationPoint;
    QVector3D lastRotationPoint;
    float trackballRadius;
    QQuaternion currentRotation;
    QVector2D currentTranslation;
    std::vector<std::vector<float>> initVertices;
    std::vector<std::vector<float> > vertices;
    std::vector<std::vector<float> > colors;
    std::vector<std::vector<float> > normals;
    QOpenGLShaderProgram  *shaderProgram;
    QGLShader *vertexShader;
    QGLShader *fragmentShader;

    // Camera
    Camera *camera_;
    Model *model_;
};

#endif // GLWIDGET_H
