#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mywindow;
    mywindow.setWindowTitle("Hello Cube");
    mywindow.show();

    return a.exec();
}
