#include "cube.h"

Cube::Cube()
{
    // set cube vertices
    float x = 0.5f;

    std::vector<float> position0 = {-x, -x, +x};
    std::vector<float> position1 = {+x, -x, +x};
    std::vector<float> position2 = {+x, -x, -x};
    std::vector<float> position3 = {-x, -x, -x};
    std::vector<float> position4 = {-x, +x, +x};
    std::vector<float> position5 = {+x, +x, +x};
    std::vector<float> position6 = {+x, +x, -x};
    std::vector<float> position7 = {-x, +x, -x};

    // front
    vertices.push_back(position0);
    vertices.push_back(position1);
    vertices.push_back(position5);
    vertices.push_back(position4);

    // right
    vertices.push_back(position1);
    vertices.push_back(position2);
    vertices.push_back(position6);
    vertices.push_back(position5);

    // back
    vertices.push_back(position2);
    vertices.push_back(position3);
    vertices.push_back(position7);
    vertices.push_back(position6);

    // left
    vertices.push_back(position3);
    vertices.push_back(position0);
    vertices.push_back(position4);
    vertices.push_back(position7);

    // bottom
    vertices.push_back(position3);
    vertices.push_back(position2);
    vertices.push_back(position1);
    vertices.push_back(position0);

    // top
    vertices.push_back(position4);
    vertices.push_back(position5);
    vertices.push_back(position6);
    vertices.push_back(position7);

    // set cube colors
    std::vector<float> color0 = {0, 0, 1};
    std::vector<float> color1 = {1, 0, 0};
    std::vector<float> color2 = {1, 1, 0};
    std::vector<float> color3 = {0, 1, 1};
    std::vector<float> color4 = {1, 0, 1};
    std::vector<float> color5 = {0, 1, 0};

    colors.push_back(color0);
    colors.push_back(color1);
    colors.push_back(color2);
    colors.push_back(color3);
    colors.push_back(color4);
    colors.push_back(color5);
}

void Cube::draw()
{
    glBegin(GL_QUADS);
    // draw all faces of the cube and set color and normal accordingly
    for (int i = 0; i < vertices.size(); i++) {
        glColor3f(colors[i/4][0], colors[i/4][1], colors[i/4][2]);
        //glNormal3f(normals[i / nrVerticesSameColor][0], normals[i / nrVerticesSameColor][1], normals[i / nrVerticesSameColor][2]);
        glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
    }
    glEnd();
}
