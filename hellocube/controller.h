#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "mainwindow.h"


class Controller : public QObject
{
    Q_OBJECT
public:
    Controller();
    void ConnectView(MainWindow *view);

private:
    MainWindow *view_;

public slots:
    void setSingleViewMode();
    void setDualViewMode();
    void setQuadViewMode();
};

#endif // CONTROLLER_H
