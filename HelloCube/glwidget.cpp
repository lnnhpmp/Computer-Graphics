#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
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


    static const char *fragmentShaderSource =
        "#version 120\n"
        "\n"
        "varying vec3 normal;\n"
        "varying vec3 lightRay;\n"
        "varying vec3 viewRay;\n"
        "void main() {\n"
        "   vec3 N = normalize(normal);\n"
        "   vec3 L = normalize(lightRay);\n"
        "   vec3 V = normalize(viewRay);\n"
        "   float LdotN = dot(L, N);\n"
        "   if (LdotN > 0) {\n"
        "       vec3 R = 2 * LdotN * N - L;\n"
        "       float RdotV = max(0, dot(R,V));\n"
        "       vec4 diffuseColor = gl_Color * LdotN * gl_LightSource[0].diffuse;\n"
        "       vec4 specularColor = gl_FrontMaterial.specular * pow(RdotV, gl_FrontMaterial.shininess) * gl_LightSource[0].specular;\n"
        "       gl_FragColor = diffuseColor + specularColor;\n"
        "   } else {\n"
        "       gl_FragColor = vec4(0,0,0,1);\n"
        "       ;\n"
        "   }\n"
        "}\n";
    static const char *vertexShaderSource =
        "#version 120\n"
        "\n"
        "varying vec3 normal;\n"
        "varying vec3 lightRay;\n"
        "varying vec3 viewRay;\n"
        "void main() {\n"
        "   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
        "   normal = normalize(gl_NormalMatrix * gl_Normal);\n"
        "   lightRay = gl_LightSource[0].position.xyz - vec3(gl_ModelViewMatrix * gl_Vertex);\n"
        "   viewRay = (- gl_ModelViewMatrix * gl_Vertex).xyz;\n"
        "   gl_FrontColor = gl_Color;\n"
        "   gl_BackColor = gl_Color;\n"
        "}\n";
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

void GLWidget::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // set camera position
    glTranslatef(currentTranslation.x(), currentTranslation.y(), current_z);

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

inline void GLWidget::glMultMatrix(const GLfloat  *m) { glMultMatrixf(m); }
inline void GLWidget::glMultMatrix(const GLdouble *m) { glMultMatrixd(m); }


void GLWidget::resizeGL(int width, int height) {
    if (height == 0)
        height = 1;
    // set the viewport to be the entire window
    glViewport(0, 0, width, height);

    // reset projection matrix
    glMatrixMode(GL_PROJECTION);
    // reset coordinate system
    glLoadIdentity();
    gluPerspective(45.0f, (double) width / (double) height, 0.01, 100.0);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
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

void GLWidget::wheelEvent(QWheelEvent *event)
{
    current_z += event->delta() * 0.002f;
    updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    // set the current mouse point for further translation or rotation calculations (in mouseMoveEvent)
    if (event->button() == Qt::RightButton) {
        lastTranslationPoint = QVector2D(event->x(), event->y());
    } else if (event->button() == Qt::LeftButton) {
        lastRotationPoint = mapPointToTrackball(event->x(), event->y());
    }
    updateGL();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    bool valid = true;

    // only translate or rotate when mouse pointer within the widget
    if (x > width() || y > height() || x < 0 || y < 0) valid = false;

    if ((event->buttons() & Qt::RightButton) == Qt::RightButton && valid) {

        QVector2D newPoint = QVector2D(x, y);
        float dX = newPoint.x() - lastTranslationPoint.x();
        // Qt has an inverted y-axis compared to OpenGL
        float dY = lastTranslationPoint.y() - newPoint.y();

        float scaleFactor = -current_z * 0.001166;    // this factor was chosen through testing
        currentTranslation += QVector2D(dX * scaleFactor, dY * scaleFactor);
        lastTranslationPoint = newPoint;

    } else if ((event->buttons() & Qt::LeftButton) == Qt::LeftButton && valid) {

        QVector3D newPoint = mapPointToTrackball(x, y);

        // calculate direction to last point and construct vector that is perpendicular to the plane spanned by the two vectors
        QVector3D normal;
        normal = QVector3D::crossProduct(lastRotationPoint, newPoint);

        /* transform the normal with the current rotation */
        //float currentModelView[16];
        //glGetFloatv(GL_MODELVIEW_MATRIX, currentModelView);
        double currentModelView[16];
        glGetDoublev(GL_MODELVIEW_MATRIX, currentModelView);
        QMatrix4x4 mv (currentModelView[0], currentModelView[1], currentModelView[2], currentModelView[3],
                       currentModelView[4], currentModelView[5], currentModelView[6], currentModelView[7],
                       currentModelView[8], currentModelView[9], currentModelView[10], currentModelView[11],
                       currentModelView[12], currentModelView[13], currentModelView[14], currentModelView[15]);
        normal = mv * normal;

        /* convert the distance between the two points to a number of degrees for the rotation */
        float degrees = acosf(QVector3D::dotProduct(newPoint, lastRotationPoint)) * 180 / M_PI;

        // create quaternion from the axis and the angle
        QQuaternion rotation (degrees, normal);
        rotation.normalize();

        // multiply with previous quaternion to add rotations
        rotation = currentRotation * rotation;
        currentRotation = rotation;

        lastRotationPoint = newPoint;
    }

    updateGL();
}

void GLWidget::resetCamera()
{
    // set rotation, zoom and translation to default
    currentRotation = QQuaternion();
    current_z = -5;
    currentTranslation = QVector2D();

    updateGL();
}

QVector3D GLWidget::mapPointToTrackball(float x, float y) {

    /* map mouse point (given in xy-plane) to the range of [-1, 1] in both dimensions
     * note: (0, 0) equals the upper left corner in the mouse coordinates retrieved,
     *       but OpenGL considers (0, 0) to be the lower left corner. Thus, the y-axis
     *       is inverted here.
     */
    QPointF newPoint ((2 * x - width()) / (float) width(), (-1) * (2 * y - height()) / (float) height());

    // treat this point as point on a unit hemisphere -> calculate corresponding z-value and normalize the vector
    float squaredDistanceFromOrigin2D = newPoint.x() * newPoint.x() + newPoint.y() * newPoint.y();

    // determine whether to map z to the sphere or the hyperbolic sheet
    float z = 0.0f;
    if (squaredDistanceFromOrigin2D < trackballRadius * trackballRadius / 2) {
        z = sqrt(trackballRadius * trackballRadius - squaredDistanceFromOrigin2D);
    } else {
        z = trackballRadius * trackballRadius / 2 / sqrt(squaredDistanceFromOrigin2D);
    }

    QVector3D newPoint3D (newPoint.x(), newPoint.y(), z);
    newPoint3D.normalize();

    return newPoint3D;
}


