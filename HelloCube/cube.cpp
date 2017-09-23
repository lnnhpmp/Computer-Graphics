#include "cube.h"

Cube::Cube()
{
    //tessellN = 0;

    // set cube vertices
    float x = 0.5f;

    std::vector<GLfloat> position0 = {-x, -x, +x};
    std::vector<GLfloat> position1 = {+x, -x, +x};
    std::vector<GLfloat> position2 = {+x, -x, -x};
    std::vector<GLfloat> position3 = {-x, -x, -x};
    std::vector<GLfloat> position4 = {-x, +x, +x};
    std::vector<GLfloat> position5 = {+x, +x, +x};
    std::vector<GLfloat> position6 = {+x, +x, -x};
    std::vector<GLfloat> position7 = {-x, +x, -x};

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
    std::vector<GLfloat> color0 = {0, 0, 1};
    std::vector<GLfloat> color1 = {1, 0, 0};
    std::vector<GLfloat> color2 = {1, 1, 0};
    std::vector<GLfloat> color3 = {0, 1, 1};
    std::vector<GLfloat> color4 = {1, 0, 1};
    std::vector<GLfloat> color5 = {0, 1, 0};

    colors.push_back(color0);
    colors.push_back(color1);
    colors.push_back(color2);
    colors.push_back(color3);
    colors.push_back(color4);
    colors.push_back(color5);
}

void Cube::draw(int tessellation)
{
    int nrVerticesSameColor = 4 * tesselationSteps * tesselationSteps;
    glBegin(GL_QUADS);
    // draw all faces of the cube and set color and normal accordingly
    for (uint i = 0; i < vertices.size(); i++) {
        if (i % nrVerticesSameColor == 0) {
            glColor3f(colors[i / nrVerticesSameColor][0], colors[i / nrVerticesSameColor][1], colors[i / nrVerticesSameColor][2]);
            //glNormal3f(normals[i / nrVerticesSameColor][0], normals[i / nrVerticesSameColor][1], normals[i / nrVerticesSameColor][2]);
        }
        glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
    }
    glEnd();
}

void Cube::settessel(int t)
{
    tesselationSteps = t;

    std::vector<std::vector<float> > newVertices;

    // for each quad
    for (uint quad = 0; quad < vertices.size() / 4; quad++) {
        // the vertices of a quad are listed counterclockwise, starting at the lower left corner
        int lowerLeftCorner = quad * 4;
        float stepSize[3] = {0, 0, 0};

        // determine stepSize by calculating the difference in x- and y- coordinate between two opposite vertices of the quad
        for (int d = 0; d < 3; d++) {
            if (vertices[lowerLeftCorner][d] != vertices[lowerLeftCorner + 2][d]) {
                stepSize[d] = (fabs(vertices[lowerLeftCorner][d]) + fabs(vertices[lowerLeftCorner + 2][d])) / t;
            }
        }

        std::vector<float> lowerLeftVertex = vertices[lowerLeftCorner];

        // divide each quad into t*2 quads
        for (int i = 0; i < t; i++) {
            for (int j = 0; j < t; j++) {
                if (stepSize[0] == 0) {  // in case the quad is in the zy plane
                    float position0[3] = {lowerLeftVertex[0], lowerLeftVertex[1], lowerLeftVertex[2]};
                    float position1[3] = {lowerLeftVertex[0], lowerLeftVertex[1], lowerLeftVertex[2] + stepSize[2]};
                    float position2[3] = {lowerLeftVertex[0], lowerLeftVertex[1] + stepSize[1], lowerLeftVertex[2] + stepSize[2]};
                    float position3[3] = {lowerLeftVertex[0], lowerLeftVertex[1] + stepSize[1], lowerLeftVertex[2]};

                    // insert new quad into vertices list
                    newVertices.push_back(std::vector<float> (position0, position0 + 3));
                    newVertices.push_back(std::vector<float> (position1, position1 + 3));
                    newVertices.push_back(std::vector<float> (position2, position2 + 3));
                    newVertices.push_back(std::vector<float> (position3, position3 + 3));
                } else if (stepSize[1] == 0) {  // in case the quad is in the xz plane
                    float position0[3] = {lowerLeftVertex[0], lowerLeftVertex[1], lowerLeftVertex[2]};
                    float position1[3] = {lowerLeftVertex[0] + stepSize[0], lowerLeftVertex[1], lowerLeftVertex[2]};
                    float position2[3] = {lowerLeftVertex[0] + stepSize[0], lowerLeftVertex[1], lowerLeftVertex[2] + stepSize[2]};
                    float position3[3] = {lowerLeftVertex[0], lowerLeftVertex[1], lowerLeftVertex[2] + stepSize[2]};

                    // insert new quad into vertices list
                    newVertices.push_back(std::vector<float> (position0, position0 + 3));
                    newVertices.push_back(std::vector<float> (position1, position1 + 3));
                    newVertices.push_back(std::vector<float> (position2, position2 + 3));
                    newVertices.push_back(std::vector<float> (position3, position3 + 3));
                } else if (stepSize[2] == 0) {  // in case the quad is in the xy plane
                    float position0[3] = {lowerLeftVertex[0], lowerLeftVertex[1], lowerLeftVertex[2]};
                    float position1[3] = {lowerLeftVertex[0] + stepSize[0], lowerLeftVertex[1], lowerLeftVertex[2]};
                    float position2[3] = {lowerLeftVertex[0] + stepSize[0], lowerLeftVertex[1] + stepSize[1], lowerLeftVertex[2]};
                    float position3[3] = {lowerLeftVertex[0], lowerLeftVertex[1] + stepSize[1], lowerLeftVertex[2]};

                    // insert new quad into vertices list
                    newVertices.push_back(std::vector<float> (position0, position0 + 3));
                    newVertices.push_back(std::vector<float> (position1, position1 + 3));
                    newVertices.push_back(std::vector<float> (position2, position2 + 3));
                    newVertices.push_back(std::vector<float> (position3, position3 + 3));
                }
                // proceed to the next column
                lowerLeftVertex = newVertices[quad * (t * t * 4) + i * (t * 4) + j * 4 + 1];
            }
            // proceed to the next row
            lowerLeftVertex = newVertices[quad * (t * t * 4) + i * (t * 4) + 3];
        }
    }

    vertices = newVertices;

    updateGL();
}
