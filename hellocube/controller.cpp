#include "controller.h"

Controller::Controller()
{

}

void Controller::ConnectView(MainWindow *view)
{
    view_ = view;

    connect(view_, SIGNAL(setSingleViewMode()), this, SLOT(setSingleViewMode()));
    connect(view_, SIGNAL(setDualViewMode()), this, SLOT(setDualViewMode()));
    connect(view_, SIGNAL(setQuadViewMode()), this, SLOT(setQuadViewMode()));
}

void Controller::setSingleViewMode()
{
    view_->viewportPerspective->show();
    view_->viewportFront->hide();
    view_->viewportLeft->hide();
    view_->viewportTop->hide();
}

void Controller::setDualViewMode()
{
    view_->viewportPerspective->show();
    view_->viewportFront->show();
    view_->viewportLeft->hide();
    view_->viewportTop->hide();
}

void Controller::setQuadViewMode()
{
    view_->viewportPerspective->show();
    view_->viewportFront->show();
    view_->viewportLeft->show();
    view_->viewportTop->show();
}
