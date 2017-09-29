#include "model.h"
#include "camera.h"

Model::Model()
{
    cameras_[PERSPECTIVE] = new Camera(0, Camera::PERSPECTIVE, false, QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 90.0f));
    cameras_[FRONT] = new Camera(0, Camera::ORTHOGRAPHIC, true, QQuaternion());
    cameras_[LEFT] = new Camera(0, Camera::ORTHOGRAPHIC, true, QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), 90.0f));
    cameras_[TOP] = new Camera(0, Camera::ORTHOGRAPHIC, true, QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 90.0f));


}

Camera* Model::getCamera(ViewportType type) {
    return cameras_[type];
}
