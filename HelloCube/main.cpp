#include "view.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View w;
    w.setWindowTitle("Hello Cube");
    w.resize(500, 400);
    w.show();

    return a.exec();
}
