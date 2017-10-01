#include "controller.h"
#include "mainwindow.h"

Controller::Controller()
{

}

void Controller::setModel(Model *model)
{
    model_ = model;

    connect(view_, SIGNAL(setCameraMode()), model_, SLOT(setCameraInteractionMode()));
    connect(view_, SIGNAL(setObjectMode()), model_, SLOT(setObjectInteractionMode()));
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

void Controller::createMouseControllers() {
    if (model_ != NULL && view_ != NULL) {
        mousePerspective = new MouseController(0, view_->getViewport(Model::PERSPECTIVE), model_->getCamera(Model::PERSPECTIVE), model_);
        mouseFront = new MouseController(0, view_->getViewport(Model::FRONT), model_->getCamera(Model::FRONT), model_);
        mouseLeft = new MouseController(0, view_->getViewport(Model::LEFT), model_->getCamera(Model::LEFT), model_);
        mouseTop = new MouseController(0, view_->getViewport(Model::TOP), model_->getCamera(Model::TOP), model_);
    }
    else
        std::cout << "Model or View has not been set in the Controller previously to calling createMouseController()!" << std::endl;

    connect(mousePerspective, SIGNAL(updateViewport()), view_, SIGNAL(updateViewports()));
    connect(mouseFront, SIGNAL(updateViewport()), view_, SIGNAL(updateViewports()));
    connect(mouseLeft, SIGNAL(updateViewport()), view_, SIGNAL(updateViewports()));
    connect(mouseTop, SIGNAL(updateViewport()), view_, SIGNAL(updateViewports()));

    connect(this, SIGNAL(updateViewports()), view_, SIGNAL(updateViewports()));
}
