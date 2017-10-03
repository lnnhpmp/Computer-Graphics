#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set central widget

    myWidget = new GLWidget(this);
    setCentralWidget(myWidget);


    createViewports();
    setCentralWidgets();
/**/
    createExitAction();

    createFileMenu();

    // Shading Menu
    createShadingAction();
    createShadingMenu();

    createAboutAction();

    // Object Menu
    createObjectMenu();

    createMenuBar();
    setMenuBar(menuBar);

    // tessellation bar
    createSlider();

    createResetAction();

    // camera mode and object manipulation mode
    createInteractionMode();

    // single, dual, quad view
    set_ViewModeAction();
    set_ViewModeMenu();

    createToolBar();
    //createStatusBar();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createMenuBar()
{
    menuBar = new QMenuBar ();
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(shadingMenu);
    menuBar->addAction(aboutAction);
    menuBar->addMenu(objectMenu);
}

void MainWindow::createFileMenu()
{
    fileMenu = new QMenu("&File");
    fileMenu->addAction(exitAction);
}

void MainWindow::createExitAction()
{
    exitAction = new QAction("E&xit", this);
    exitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    connect (exitAction, SIGNAL (triggered()), this, SLOT (close()));
}

void MainWindow::createShadingAction()
{
    NoneMode = new QAction("&None", this);
    NoneMode->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_1));
    NoneMode->setIcon(QIcon(":/Resources/wireframe.png"));
    NoneMode->setCheckable(true);
    connect (NoneMode, SIGNAL (triggered()), myWidget, SLOT (setWireframeShading()));

    FlatMode = new QAction("&Flat", this);
    FlatMode->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_2));
    FlatMode->setIcon(QIcon(":/Resources/flat.png"));
    FlatMode->setChecked(true);
    connect (FlatMode, SIGNAL (triggered()), myWidget, SLOT (setFlatShading()));

    GouraudMode = new QAction("&Gouraud", this);
    GouraudMode->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_3));
    GouraudMode->setIcon(QIcon(":/Resources/gouraud.png"));
    GouraudMode->setCheckable(true);
    connect (GouraudMode, SIGNAL (triggered()), myWidget, SLOT (setGouraudShading()));

    PhongMode = new QAction("&Phong", this);
    PhongMode->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_4));
    PhongMode->setIcon(QIcon(":/Resources/phong.png"));
    PhongMode->setCheckable(true);
    connect (PhongMode, SIGNAL (triggered()), myWidget, SLOT (setPhongShading()));

    shadingGroup = new QActionGroup(this);
    shadingGroup->addAction(NoneMode);
    shadingGroup->addAction(FlatMode);
    shadingGroup->addAction(GouraudMode);
    shadingGroup->addAction(PhongMode);
    FlatMode->setChecked(true);
}

void MainWindow::createShadingMenu()
{
    shadingMenu = new QMenu("&Shading");
    shadingMenu->addAction(NoneMode);
    shadingMenu->addAction(FlatMode);
    shadingMenu->addAction(GouraudMode);
    shadingMenu->addAction(PhongMode);
}

void MainWindow::createAboutAction()
{
     aboutAction = new QAction("About", this);
     connect (aboutAction, SIGNAL (triggered()), this, SLOT (showAboutBox()));
}

void MainWindow::createResetAction()
{
     resetCamera = new QAction("Reset", this);
     resetCamera->setIcon(QIcon(":/Resources/cam_home.png"));
     connect (resetCamera, SIGNAL (triggered()), myWidget, SLOT (ResetCamera()));
}

void MainWindow::showAboutBox()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle ("About Hello Cube!");
    msgBox.setText ("Written by 徐方雨!");
    msgBox.exec();
}

void MainWindow::createToolBar()
{
    toolsBar = addToolBar(tr("tools"));
    toolsBar->addAction(NoneMode);
    toolsBar->addAction(FlatMode);
    toolsBar->addAction(GouraudMode);
    toolsBar->addAction(PhongMode);
    toolsBar->addWidget(TessellationSlider);
    toolsBar->addAction(resetCamera);
    toolsBar->addAction(CameraMode);
    toolsBar->addAction(ObjectManiMode);
    toolsBar->addWidget(viewModeButton);
}

void MainWindow::createStatusBar()
{
    stat0 = new QLabel("abb");
    statusBar()->addWidget(stat0);
}

void MainWindow::createSlider()
{
    // Create Tessellation Slider
    TessellationSlider = new QSlider(Qt::Horizontal);
    TessellationSlider->setFixedWidth(100);
    TessellationSlider->setRange(1, 50);
    TessellationSlider->setValue(4);
    connect(TessellationSlider, SIGNAL(valueChanged(int)), myWidget, SLOT(setTesselation(int)));
}

void MainWindow::createInteractionMode()
{
    CameraMode = new QAction(this);
    CameraMode->setIcon(QIcon(":/icon/camera.png"));
    CameraMode->setCheckable(true);
    CameraMode->setChecked(true);
    connect(CameraMode, SIGNAL(triggered()), this, SIGNAL(setCameraMode()));

    ObjectManiMode = new QAction(this);
    ObjectManiMode->setIcon(QIcon(":/icon/select.png"));
    ObjectManiMode->setCheckable(true);
    connect(ObjectManiMode, SIGNAL(triggered()), this, SIGNAL(setObjectMode()));

    interactGroup = new QActionGroup(this);
    interactGroup->addAction(CameraMode);
    interactGroup->addAction(ObjectManiMode);
}

void MainWindow::set_ViewModeMenu()
{
    viewModeMenu = new QMenu("&View Mode");
    viewModeGroup = new QActionGroup(viewModeMenu);

    viewModeButton = new QToolButton(viewModeMenu);
    viewModeButton->setMenu(viewModeMenu);
    viewModeButton->setPopupMode(QToolButton::InstantPopup);
    viewModeButton->setIcon(QIcon(":/icon/viewports.png"));


    viewModeGroup->addAction(setSingleViewModeAction);
    viewModeGroup->addAction(setDualViewModeAction);
    viewModeGroup->addAction(setQuadViewModeAction);

    viewModeMenu->addAction(setSingleViewModeAction);
    viewModeMenu->addAction(setDualViewModeAction);
    viewModeMenu->addAction(setQuadViewModeAction);
}

void MainWindow::set_ViewModeAction()
{
    setSingleViewModeAction = new QAction("&Single View");
    setSingleViewModeAction->setIcon(QIcon(":/icon/view-single.png"));
    setSingleViewModeAction->setShortcut(tr("1"));
    setSingleViewModeAction->setCheckable(true);
    setSingleViewModeAction->setChecked(true);
    connect(setSingleViewModeAction, SIGNAL(triggered()), this, SIGNAL(setSingleViewMode()));

    setDualViewModeAction = new QAction("&Dual View");
    setDualViewModeAction->setShortcut(tr("2"));
    setDualViewModeAction->setIcon(QIcon(":/icon/view-dual.png"));
    setDualViewModeAction->setCheckable(true);
    connect(setDualViewModeAction, SIGNAL(triggered()), this, SIGNAL(setDualViewMode()));

    setQuadViewModeAction = new QAction("&Quad View");
    setQuadViewModeAction->setShortcut(tr("4"));
    setQuadViewModeAction->setIcon(QIcon(":/icon/viewports.png"));
    setQuadViewModeAction->setCheckable(true);
    connect(setQuadViewModeAction, SIGNAL(triggered()), this, SIGNAL(setQuadViewMode()));
}

void MainWindow::createViewports()
{
    viewportPerspective = new GLWidget(this);
    viewportFront = new GLWidget(this);
    viewportLeft = new GLWidget(this);
    viewportTop = new GLWidget(this);
}

void MainWindow::setCentralWidgets()
{
    // assign four viewports
    splitterHorizontalTop = new QSplitter(this);

    //viewportPerspective->glDraw();

    splitterHorizontalTop->addWidget(viewportPerspective);
    splitterHorizontalTop->addWidget(viewportFront);
    splitterHorizontalTop->setStyleSheet("QSplitter::handle { background-color: black }");

    splitterHorizontalBottom = new QSplitter(this);
    splitterHorizontalBottom->addWidget(viewportLeft);
    splitterHorizontalBottom->addWidget(viewportTop);
    splitterHorizontalBottom->setStyleSheet("QSplitter::handle { background-color: black }");

    splitterVertical = new QSplitter(this);
    splitterVertical->setOrientation(Qt::Vertical);
    splitterVertical->setStyleSheet("QSplitter::handle { background-color: black }");
    splitterVertical->addWidget(splitterHorizontalTop);
    splitterVertical->addWidget(splitterHorizontalBottom);

    // initialize with single view
    /*viewportFront->hide();*/
    viewportLeft->hide();
    viewportTop->hide();

    setCentralWidget(splitterVertical);
}

void MainWindow::setModel(Model *model)
{
    model_ = model;
    viewportPerspective->setCamera(model_->getCamera(Model::PERSPECTIVE));
    viewportFront->setCamera(model_->getCamera(Model::FRONT));
    viewportLeft->setCamera(model_->getCamera(Model::LEFT));
    viewportTop->setCamera(model_->getCamera(Model::TOP));

    connect(this, SIGNAL(updateViewports()), viewportPerspective, SLOT(updateGL()));
    connect(this, SIGNAL(updateViewports()), viewportFront, SLOT(updateGL()));
    connect(this, SIGNAL(updateViewports()), viewportLeft, SLOT(updateGL()));
    connect(this, SIGNAL(updateViewports()), viewportTop, SLOT(updateGL()));

}

GLWidget* MainWindow::getViewport(Model::ViewportType type)
{
    switch (type) {
    case Model::PERSPECTIVE : return viewportPerspective;
    case Model::FRONT: return viewportFront;
    case Model::LEFT: return viewportLeft;
    case Model::TOP: return viewportTop;
    default: return viewportPerspective;
    }
}

void MainWindow::createObjectMenu()
{
    objectMenu = new QMenu("&Object");

    createCubeAction = new QAction("Create Box", objectMenu);
    createCubeAction->setIcon(QIcon(":/icon/box.png"));
    //connect(createCubeAction, SIGNAL(triggered()), this, SIGNAL(createCube()));


    createSphereAction = new QAction("Create Sphere", objectMenu);
    createSphereAction->setIcon(QIcon(":/icon/sphere.png"));
    //connect(createSphereAction, SIGNAL(triggered()), this, SIGNAL(createSphere()));

    createCylinderAction = new QAction("Create Cylinder", objectMenu);
    createCylinderAction->setIcon(QIcon(":/icon/cylinder.png"));
    //connect(createCylinderAction, SIGNAL(triggered()), this, SIGNAL(createCylinder()));

    createConeAction = new QAction("Create Cone", objectMenu);
    createConeAction->setIcon(QIcon(":/icon/cone.png"));
    //connect(createConeAction, SIGNAL(triggered()), this, SIGNAL(createCone()));

    createTorusAction = new QAction("Create Torus", objectMenu);
    createTorusAction->setIcon(QIcon(":/icon/torus.png"));
    //connect(createTorusAction, SIGNAL(triggered()), this, SIGNAL(createTorus()));

    objectMenu->addAction(createCubeAction);
    objectMenu->addAction(createSphereAction);
    objectMenu->addAction(createCylinderAction);
    objectMenu->addAction(createConeAction);
    objectMenu->addAction(createTorusAction);

}
