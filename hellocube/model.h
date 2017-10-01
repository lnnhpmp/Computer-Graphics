#ifndef MODEL_H
#define MODEL_H
#include <QObject>
#include "camera.h"

class Model : public QObject
{
public:
    Model();
    enum ViewportType {PERSPECTIVE, FRONT, LEFT, TOP};
    Camera* getCamera(ViewportType type);

private:
    Camera *cameras_[4];
};

#endif // MODEL_H
