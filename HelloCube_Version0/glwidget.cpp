#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{

}

GLWidget::~GLWidget()
{
    //cleanup();
}

void GLWidget::initializeGL()
{
    //glEnable(GL_LIGHTING);
    static GLfloat light_position[] = {0.5, 0.0, 2.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_position);
}

void GLWidget::paintGL()
{

}

void GLWidget::resizeGL(int width, int height)
{

}

void GLWidget::mousePressEvent(QMouseEvent *event)
{

}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void GLWidget::wheelEvent(QWheelEvent *event)
{

}
