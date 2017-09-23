#ifndef CUBE_H
#define CUBE_H
#include <iostream>
#include <vector>
#include <qopenglfunctions_4_5_core.h>
#include <math.h>
#include <QGLWidget>

class Cube : public QGLWidget
{
public:
    Cube();
    void draw(int tessellation);
    void settessel(int t);
protected:
    std::vector<std::vector<GLfloat>> vertices;
    std::vector<std::vector<GLfloat>> colors;
private:
    //int tessellN = 0;
    int tesselationSteps = 1;
};

#endif // CUBE_H
