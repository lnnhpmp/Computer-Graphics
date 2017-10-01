#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "mainwindow.h"
#include "model.h"
#include "mousecontroller.h"
#include <iostream>

class Controller : public QObject
{
    Q_OBJECT
signals:
    void updateViewports();

public:
    Controller();
    void ConnectView(MainWindow *view);
    void createMouseControllers();
    void setModel(Model *model);

private:
    MainWindow *view_;
    Model *model_;

    MouseController *mousePerspective;
    MouseController *mouseFront;
    MouseController *mouseLeft;
    MouseController *mouseTop;

public slots:
    void setSingleViewMode();
    void setDualViewMode();
    void setQuadViewMode();
};

#endif // CONTROLLER_H
