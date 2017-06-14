#include "view.h"
#include <QApplication>
#include "model.h"
#include "view.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model model;
    View w;
    Controller controller;

    w.setModel(&model);
    w.setWindowTitle("Hello Cube");
    w.resize(400, 300);

    controller.setModel(&model);
    controller.setView(&w);

    w.show();

    return a.exec();
}
