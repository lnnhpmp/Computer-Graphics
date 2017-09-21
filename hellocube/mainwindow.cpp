#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set Widget
    myWidget = new GLWidget(this);
    setCentralWidget(myWidget);

    createExitAction();

    createFileMenu();

    // Shading Menu
    createShadingAction();
    createShadingMenu();

    createAboutAction();

    createMenuBar();
    setMenuBar(menuBar);

    createToolBar();
}

MainWindow::~MainWindow()
{

}

MainWindow::createMenuBar()
{
    menuBar = new QMenuBar ();
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(shadingMenu);
    menuBar->addAction(aboutAction);
}

MainWindow::createFileMenu()
{
    fileMenu = new QMenu("&File");
    fileMenu->addAction(exitAction);
}

MainWindow::createExitAction()
{
    exitAction = new QAction("E&xit", this);
    exitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    connect (exitAction, SIGNAL (triggered()), this, SLOT (close()));
}

MainWindow::createShadingAction()
{
    NoneMode = new QAction("None", this);
    NoneMode->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_1));
    NoneMode->setCheckable(true);
    NoneMode->setIcon(QIcon(":/img/Resources/wireframe.png"));

    FlatMode = new QAction("Flat", this);
    FlatMode->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_2));
    FlatMode->setIcon(QIcon(":/img/Resources/flat.png"));

    GouraudMode = new QAction("Gouraud", this);
    GouraudMode->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_3));
    GouraudMode->setIcon(QIcon(":/img/Resources/gouraud.png"));

    PhongMode = new QAction("Phong", this);
    PhongMode->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_4));
    PhongMode->setIcon(QIcon(":/img/Resources/phong.png"));
}

MainWindow::createShadingMenu()
{
    shadingMenu = new QMenu("&Shading");
    shadingMenu->addAction(NoneMode);
    shadingMenu->addAction(FlatMode);
    shadingMenu->addAction(GouraudMode);
    shadingMenu->addAction(PhongMode);
}

MainWindow::createAboutAction()
{
     aboutAction = new QAction("About", this);
     connect (aboutAction, SIGNAL (triggered()), this, SLOT (showAboutBox()));
}

MainWindow::showAboutBox()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle ("About Hello Cube!");
    msgBox.setText ("Written by 徐方雨!");
    msgBox.exec();
}

MainWindow::createToolBar()
{
    toolsBar = addToolBar(tr("tools"));;
    toolsBar->addAction(NoneMode);
    toolsBar->addAction(FlatMode);
    toolsBar->addAction(GouraudMode);
    toolsBar->addAction(PhongMode);
}

MainWindow::createStatusBar()
{
    statusLabel = new QLabel(this);
    statusLabel->setText("Status Label");
    statusBar->addWidget(statusLabel);
    setStatusBar(statusBar);
}
