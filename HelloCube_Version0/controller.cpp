#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{

}

void Controller::setModel(Model *model) {
    mymodel = model;
}

void Controller::setView(View *view) {
    myview = view;
}
