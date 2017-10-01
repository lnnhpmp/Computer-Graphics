#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include "controller.h"
#include "model.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mywindow;
    QDesktopWidget dw;
    int x = dw.width()*0.5;
    int y = dw.height()*0.5;
    mywindow.setFixedSize(x, y);
    mywindow.setWindowTitle("Modelling Tool");

    Model model;
    mywindow.setModel(&model);

    Controller controller;
    controller.ConnectView(&mywindow);
    controller.setModel(&model);
    controller.createMouseControllers();

    mywindow.show();

    return a.exec();
}
