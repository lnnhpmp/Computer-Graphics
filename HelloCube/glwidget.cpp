#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    //setAutoFillBackground(false);
    //setAutoBufferSwap(false);
    //this->setStyleSheet("QGLWidget::handle { background-color: black }");


    camera_ = new Camera();
    tesselationSteps = 1;
    current_z = -5.0;

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

    // front initVertices[0:3]
    initVertices.push_back(position0);
    initVertices.push_back(position1);
    initVertices.push_back(position5);
    initVertices.push_back(position4);

    // right initVertices[4:7]
    initVertices.push_back(position2);
    initVertices.push_back(position6);
    initVertices.push_back(position5);
    initVertices.push_back(position1);

    // back initVertices[8:11]
    initVertices.push_back(position3);
    initVertices.push_back(position2);
    initVertices.push_back(position6);
    initVertices.push_back(position7);

    // left initVertices[12:15]
    initVertices.push_back(position3);
    initVertices.push_back(position0);
    initVertices.push_back(position4);
    initVertices.push_back(position7);

    // bottom initVertices[16:19]
    initVertices.push_back(position3);
    initVertices.push_back(position0);
    initVertices.push_back(position1);
    initVertices.push_back(position2);

    // top initVertices[20:23]
    initVertices.push_back(position7);
    initVertices.push_back(position4);
    initVertices.push_back(position5);
    initVertices.push_back(position6);

    vertices = initVertices;

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

    // set cube normals
    float normal0[3] = {0, 0, 1};
    float normal1[3] = {1, 0, 0};
    float normal2[3] = {0, 0, -1};
    float normal3[3] = {-1, 0, 0};
    float normal4[3] = {0, -1, 0};
    float normal5[3] = {0, 1, 0};

    normals.push_back(std::vector<float> (normal0, normal0 + 3));
    normals.push_back(std::vector<float> (normal1, normal1 + 3));
    normals.push_back(std::vector<float> (normal2, normal2 + 3));
    normals.push_back(std::vector<float> (normal3, normal3 + 3));
    normals.push_back(std::vector<float> (normal4, normal4 + 3));
    normals.push_back(std::vector<float> (normal5, normal5 + 3));

    // set rotation, zoom and translation to default
    currentRotation = QQuaternion();
    current_z = -5.0;
    currentTranslation = QVector2D();

    // set radius of the trackball
    trackballRadius = 1.0f;
}

GLWidget::~GLWidget()
{

}
/*
void GLWidget::glDraw()
{

    QGLWidget::glDraw();

    if(hasFocus())
    {
        QPainter painter(this);

        QPen pen(Qt::yellow, 4);
        painter.setPen(pen);

        painter.drawRect(0, 0, width(), height());
        std::cout<<width()<<" "<<height()<<std::endl;
    }

    swapBuffers();
}*/

void GLWidget::initializeGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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
    int shininess = 60.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularReflection);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

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

void GLWidget::drawCube()
{
    // apply rotation
    QMatrix4x4 rotation;
    rotation.rotate(currentRotation);
    glMultMatrix(rotation.constData());
    int nrVerticesSameColor = 4 * tesselationSteps * tesselationSteps;

    glBegin(GL_QUADS);
    // draw all faces of the cube and set color and normal accordingly
        for (uint i = 0; i < vertices.size(); i++) {
            if (i % nrVerticesSameColor == 0) {
                glColor3f(colors[i / nrVerticesSameColor][0], colors[i / nrVerticesSameColor][1], colors[i / nrVerticesSameColor][2]);
                glNormal3f(normals[i / nrVerticesSameColor][0], normals[i / nrVerticesSameColor][1], normals[i / nrVerticesSameColor][2]);
            }
            glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
        }
    glEnd();
}

void GLWidget::paintGL() {
    // Clear framebuffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrix(camera_->getCameraMatrix().constData());  
    drawCube();
}

inline void GLWidget::glMultMatrix(const GLfloat  *m) { glMultMatrixf(m); }
inline void GLWidget::glMultMatrix(const GLdouble *m) { glMultMatrixd(m); }


void GLWidget::resizeGL(int width, int height) {
    // set the viewport to be the entire window
    glViewport(0, 0, width, height);

    // reset projection matrix
    glMatrixMode(GL_PROJECTION);
    // reset coordinate system
    glLoadIdentity();

    /*
    gluPerspective(45.0f, (double) width / (double) height, 0.01, 100.0);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    */
    if (camera_->getProjectionMode() == Camera::PERSPECTIVE) {
        if (height != 0)
            gluPerspective(45.0, ((double) width) / ((double) height), 0.01, 100.0);
    } else if (camera_->getProjectionMode() == Camera::ORTHOGRAPHIC) {
        updateProjectionMatrix();
    }

}

void GLWidget::setWireframeShading()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    shaderProgram->release();
    updateGL();
}

void GLWidget::setFlatShading()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glShadeModel(GL_FLAT);
    shaderProgram->release();
    updateGL();
}

void GLWidget::setGouraudShading()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glShadeModel(GL_SMOOTH);
    shaderProgram->release();
    updateGL();
}

void GLWidget::setPhongShading()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glShadeModel(GL_SMOOTH);
    shaderProgram->bind();
    updateGL();
}

void GLWidget::setTesselation(int t)
{
    tesselationSteps = t;
    std::cout<<"current tessellation:"<<tesselationSteps<<std::endl;
    std::vector<std::vector<float> > newVertices;

    // for each quad
    for (uint quad = 0; quad < initVertices.size() / 4; quad++) {
        // the vertices of a quad are listed counterclockwise, starting at the lower left corner
        int lowerLeftCorner = quad * 4;
        float stepSize[3] = {0, 0, 0};

        // determine stepSize by calculating the difference in x- and y- coordinate between two opposite vertices of the quad
        for (int d = 0; d < 3; d++) {
            if (initVertices[lowerLeftCorner][d] != initVertices[lowerLeftCorner + 2][d]) {
                stepSize[d] = (fabs(initVertices[lowerLeftCorner][d]) + fabs(initVertices[lowerLeftCorner + 2][d])) / t;
            }
        }

        std::vector<float> lowerLeftVertex = initVertices[lowerLeftCorner];

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

void GLWidget::ResetCamera()
{
    // set rotation, zoom and translation to default
    currentRotation = QQuaternion();
    current_z = -5;
    currentTranslation = QVector2D();

    //updateGL();
}


void GLWidget::setCamera(Camera *camera) {
    camera_ = camera;
    connect(camera_, SIGNAL(zoomChanged()), this, SLOT(updateProjectionMatrix()));
}

void GLWidget::updateProjectionMatrix() {
    if (camera_->getProjectionMode() == Camera::ORTHOGRAPHIC) {
        // Makes this widget the current widget for OpenGL operations
        makeCurrent();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        float zoom = camera_->getZoom();
        float aspectRatio = 1;
        if (height() != 0)
            aspectRatio = (float) width() / height();
        float goodZoomFactor = zoom / 10;
        // multiply the current matrix with an orthographic matrix
        glOrtho(- aspectRatio * (1 - goodZoomFactor), aspectRatio * (1 - goodZoomFactor), -1 + goodZoomFactor, 1 - goodZoomFactor, 0.01, 100.0);
    }
}
