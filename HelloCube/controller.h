#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "model.h"
#include "view.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    void setModel(Model *model);
    void setView(View *view);

private:
    View *myview;
    Model *mymodel;

signals:

public slots:
};

#endif // CONTROLLER_H
