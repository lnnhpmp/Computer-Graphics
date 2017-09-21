#include "glwidget.h"
//#include<GL/glu.h>
GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{

}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
    //glEnable(GL_LIGHTING);
    static GLfloat light_position[] = {0.5, 0.0, 2.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_position);

}

void GLWidget::paintGL()
{
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares

}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0.0f, 0.0f, width/2.0f, height/2.0f);
    gluPerspective(45.0f, GLfloat(width) / height, 0.01f, 100.0f);
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

