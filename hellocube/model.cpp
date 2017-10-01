#include "model.h"
#include "camera.h"

Model::Model(QObject *parent):
    QObject(parent)
{
    cameras_[PERSPECTIVE] = new Camera(0, Camera::PERSPECTIVE, QQuaternion());
    cameras_[FRONT] = new Camera(0, Camera::ORTHOGRAPHIC, QQuaternion());
    cameras_[LEFT] = new Camera(0, Camera::ORTHOGRAPHIC, QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), 90.0f));
    cameras_[TOP] = new Camera(0, Camera::ORTHOGRAPHIC, QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 90.0f));

    interactionMode_ = Model::CAMERA;
}

Camera* Model::getCamera(ViewportType type) {
    return cameras_[type];
}

void Model::setObjectInteractionMode() {
    interactionMode_ = Model::OBJECT;
}

void Model::setCameraInteractionMode() {
    interactionMode_ = Model::CAMERA;
}

Model::InteractionType Model::getInteractionMode() {
    return interactionMode_;
}
