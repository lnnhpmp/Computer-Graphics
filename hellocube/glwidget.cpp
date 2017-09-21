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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // enable depth testing
    glEnable(GL_DEPTH_TEST);

    // enable color
    glEnable(GL_COLOR_MATERIAL);

    // init shading model
    glShadeModel(GL_FLAT);

    // enable lighting
    glEnable(GL_LIGHTING);

    // light source
    static GLfloat light_position[] = {0.5, 0.0, 2.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_position);

    mycube = new Cube();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-5.0);
    mycube->draw();
}

void GLWidget::resizeGL(int width, int height)
{
    // set the viewport to be the entire window
    glViewport(0.0f, 0.0f, width, height);
    // reset projection matrix
    glMatrixMode(GL_PROJECTION);
    // reset coordinate system
    glLoadIdentity();
    gluPerspective(45.0f, (double) width / (double) height, 0.01f, 100.0f);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
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

