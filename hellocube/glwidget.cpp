#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
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

    // enable backface culling
    glEnable(GL_CULL_FACE);

    // enable color
    glEnable(GL_COLOR_MATERIAL);

    // init shading model
    glShadeModel(GL_FLAT);

    // enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // light source
    static GLfloat light_position[] = {0.5f, 0.0f, 2.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // set material parameters
    setMaterial();

    // compile and link shaders
    initShaders();

    tessellationN = 1;
    mycube = new Cube(tessellationN);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // set camera position
    glTranslatef(0.0f, 0.0f, -4.0f);

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
    gluPerspective(45.0f, (double) width / (double) height, 0.01f, 10.0f);
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

void GLWidget::initShaders()
{
    shaderProgram = new QOpenGLShaderProgram(this);

    // Compile vertex shader
    if (!shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/cube.vertexShader"))
        close();

    // Compile fragment shader
    if (!shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/cube.fragmentShader"))
        close();

    // Link shader pipeline
    if (!shaderProgram->link())
        close();

    // Bind shader pipeline for use
    //if (!shaderProgram->bind())
        //close();
}

void GLWidget::setMaterial()
{
    //GLfloat mat_diffuse[4] = {0.7, 1.0, 1.0, 1.0};
    GLfloat mat_specular[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat shininess = 120.0f;
    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
}

void GLWidget::setFlatMode()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glShadeModel(GL_FLAT);
    shaderProgram->release();
    updateGL();
}

void GLWidget::setWireFrameMode()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    shaderProgram->release();
    updateGL();
}

void GLWidget::setGouraudMode()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glShadeModel(GL_SMOOTH);
    shaderProgram->release();
    updateGL();
}

void GLWidget::setPhongMode()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glShadeModel(GL_SMOOTH);
    shaderProgram->release();
    updateGL();
}

void GLWidget::setTessellation(int t)
{
    tessellationN = t;
    updateGL();
}
