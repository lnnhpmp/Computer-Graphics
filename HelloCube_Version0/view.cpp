#include "view.h"
#include <QMessageBox>

View::View(QWidget *parent) : QMainWindow(parent)
{
    FileMenu();
    ShadingMenu();
    ToolBar();
    MenuBar();
}

void View::FileMenu() {
    fileMenu = new QMenu("&File");

    exitAction = new QAction("E&xit", fileMenu);
    exitAction->setShortcut(Qt::CTRL + Qt::Key_Q);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    fileMenu->addAction(exitAction);
}

void View::ShadingMenu() {
    shadingMenu = new QMenu("&Shading");

    noneAction = new QAction("&None");
    noneAction->setShortcut(Qt::CTRL + Qt::Key_1);
    noneAction->setIcon(QIcon(":/icons/wireframe.png"));
    connect(noneAction, SIGNAL(triggered()), this, SLOT(close()));

    flatAction = new QAction("&Flat");
    flatAction->setShortcut(Qt::CTRL + Qt::Key_2);
    flatAction->setCheckable(true);
    flatAction->setChecked(true);
    flatAction->setIcon(QIcon(":/icons/flat.png"));
    connect(flatAction, SIGNAL(triggered()), this, SLOT(close()));

    gouraudAction = new QAction("&Gouraud");
    gouraudAction->setShortcut(Qt::CTRL + Qt::Key_3);
    gouraudAction->setIcon(QIcon(":/icons/gouraud.png"));
    connect(gouraudAction, SIGNAL(triggered()), this, SLOT(close()));

    phongAction = new QAction("&Phong");
    phongAction->setShortcut(Qt::CTRL + Qt::Key_4);
    phongAction->setIcon(QIcon(":/icons/phong.png"));
    connect(phongAction, SIGNAL(triggered()), this, SLOT(close()));

    shadingMenu->addAction(noneAction);
    shadingMenu->addAction(flatAction);
    shadingMenu->addAction(gouraudAction);
    shadingMenu->addAction(phongAction);
}

void View::showAboutBox() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("About Hello Cube!");
    msgBox.setText("Written by Fangyu Xu!");
    msgBox.exec();
}

void View::ToolBar() {
    tool = new QToolBar("&tool");
    addToolBar(tool);
    tool->addAction(noneAction);
    tool->addAction(flatAction);
    tool->addAction(gouraudAction);
    tool->addAction(phongAction);
}

void View::MenuBar() {
    menuBar = new QMenuBar();
    aboutAction = new QAction("&About");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutBox()));

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(shadingMenu);
    menuBar->addAction(aboutAction);

    setMenuBar(menuBar);
}

void View::setModel(Model *model) {
    mymodel = model;
}
