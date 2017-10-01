#include "view.h"

View::View()
{

}

void View::initializeGL()
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    // enable depth testing
    glEnable(GL_DEPTH_TEST);

    //glEnable(GL_CULL_FACE);
    // enable color
    glEnable(GL_COLOR_MATERIAL);

    // init shading model
    glShadeModel(GL_FLAT);

    // enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // lightsource
    float positionLight0[4] = {0.5f, 0.0f, 2.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, positionLight0);

    // set material parameters
    float specularReflection[4] = {0.7, 1.0, 1.0, 1.0};
    int shininess = 120.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularReflection);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    int width = this->width();
    int height = this->height();
    if (width == 0) width = 1;
    if (height == 0) height = 1;

    glViewport(0, 0, width, height);

    // create and compile shader program
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
}
