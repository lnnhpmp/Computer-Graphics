#ifndef CUBE_H
#define CUBE_H
#include <iostream>
#include <vector>
#include <qopenglfunctions_4_5_core.h>

class Cube
{
public:
    Cube(int tessellation);
    void draw();
protected:
    std::vector<std::vector<float>> vertices;
    std::vector<std::vector<float>> colors;
};

#endif // CUBE_H
