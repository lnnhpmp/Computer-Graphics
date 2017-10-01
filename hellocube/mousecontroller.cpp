#include "mousecontroller.h"

MouseController::MouseController(QObject *parent, GLWidget *view, Camera *camera, Model *model)
{
    ViewPort = view;
    camera_ = camera;
    model_ = model;
    trackballRadius = 1.0f;

    connect(ViewPort, SIGNAL(mousePressEvent(QMouseEvent*)), this, SLOT(mousePressEvent(QMouseEvent*)));
    connect(ViewPort, SIGNAL(mouseMoveEvent(QMouseEvent*)), this, SLOT(mouseMoveEvent(QMouseEvent*)));
    connect(ViewPort, SIGNAL(wheelEvent(QWheelEvent*)), this, SLOT(wheelEvent(QWheelEvent*)));
}

void MouseController::wheelEvent(QWheelEvent *event)
{
    camera_->zoom(event->delta() * 0.002f);
    emit updateViewport();
}

void MouseController::mousePressEvent(QMouseEvent *event)
{
    // set the current mouse point for further translation or rotation calculations (in mouseMoveEvent)
    if (event->button() == Qt::RightButton) {
        lastTranslationPoint = QVector2D(event->x(), event->y());
    } else if (event->button() == Qt::LeftButton) {
        lastRotationPoint = mapPointToTrackball(event->x(), event->y());
    }

    emit updateViewport();
}

void MouseController::mouseMoveEvent(QMouseEvent *event)
{
    // Postion of the mouse
    int x = event->x();
    int y = event->y();
    bool valid = true;

    // only translate or rotate when mouse pointer within the widget
    if (x > ViewPort->width() || y > ViewPort->height() || x < 0 || y < 0)
        valid = false;

    if ((event->buttons() & Qt::RightButton) == Qt::RightButton && valid) {
        QVector2D newPoint = QVector2D(x, y);
        float dX = newPoint.x() - lastTranslationPoint.x();
        float dY = lastTranslationPoint.y() - newPoint.y();

        float scaleFactor = 0.01;

        if (model_->getInteractionMode() == Model::CAMERA) {
            camera_->translate(QVector2D(dX * scaleFactor, dY * scaleFactor));
        }


        lastTranslationPoint = newPoint;

    } else if ((event->buttons() & Qt::LeftButton) == Qt::LeftButton && valid) {
        QVector3D newPoint = mapPointToTrackball(x, y);

        // calculate direction to last point and construct vector that is perpendicular to the plane spanned by the two vectors
        QVector3D normal;
        normal = QVector3D::crossProduct(lastRotationPoint, newPoint);

        // transform the normal with the current rotation
        normal = camera_->getRotation().conjugate().rotatedVector(normal);

        // convert the distance between the two points to a number of degrees for the rotation
        float degrees = acosf(QVector3D::dotProduct(newPoint, lastRotationPoint)) * 180 / M_PI;

        // create quaternion from the axis and the angle
        QQuaternion rotation = QQuaternion::fromAxisAndAngle(normal, degrees);
        rotation.normalize();

        // multiply with previous quaternion to add rotations
        camera_->rotate(rotation);

        lastRotationPoint = newPoint;
    }

    emit updateViewport();

}

QVector3D MouseController::mapPointToTrackball(float x, float y) {

    /* map mouse point (given in xy-plane) to the range of [-1, 1] in both dimensions
     * note: (0, 0) equals the upper left corner in the mouse coordinates retrieved,
     *       but OpenGL considers (0, 0) to be the lower left corner. Thus, the y-axis
     *       is inverted here.
     */
    QPointF newPoint ((2 * x - ViewPort->width()) / (float) ViewPort->width(), (-1) * (2 * y - ViewPort->height()) / (float) ViewPort->height());

    // treat this point as point on a unit hemisphere -> calculate corresponding z-value and normalize the vector
    float squaredDistanceFromOrigin2D = newPoint.x() * newPoint.x() + newPoint.y() * newPoint.y();

    // determine whether to map z to the sphere or the hyperbolic sheet
    float z = 0.0f;
    if (squaredDistanceFromOrigin2D < trackballRadius * trackballRadius / 2) {
        z = sqrt(trackballRadius * trackballRadius - squaredDistanceFromOrigin2D);
    }
    else {
        z = trackballRadius * trackballRadius / 2 / sqrt(squaredDistanceFromOrigin2D);
    }

    QVector3D newPoint3D (newPoint.x(), newPoint.y(), z);
    newPoint3D.normalize();

    return newPoint3D;
}
