#ifndef MODEL_H
#define MODEL_H
#include <QObject>
#include "camera.h"

class Model : public QObject
{
    Q_OBJECT
public:
    Model(QObject *parent = 0);
    enum ViewportType {PERSPECTIVE, FRONT, LEFT, TOP};
    Camera* getCamera(ViewportType type);

    enum InteractionType {OBJECT, CAMERA};
    InteractionType getInteractionMode();

private:
    Camera *cameras_[4];
    InteractionType interactionMode_;

public slots:
    void setObjectInteractionMode();
    void setCameraInteractionMode();

};

#endif // MODEL_H
