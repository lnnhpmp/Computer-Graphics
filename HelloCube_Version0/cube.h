#ifndef CUBE_H
#define CUBE_H

#include <QObject>

class Cube : public QObject
{
    Q_OBJECT
public:
    explicit Cube(QObject *parent = 0);

signals:

public slots:
};

#endif // CUBE_H