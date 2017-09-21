#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "glwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    createMenuBar();
    createFileMenu();
    createExitAction();

    createShadingAction();
    createShadingMenu();

    createAboutAction();

    createToolBar();
    createStatusBar();
private:
    GLWidget *myWidget;

    QMenuBar *menuBar;
    QMenu *fileMenu, *shadingMenu;
    QAction *exitAction,
            *NoneMode, *FlatMode, *GouraudMode, *PhongMode,
            *aboutAction;
    QToolBar *toolsBar;

    QLabel *statusLabel;
    QStatusBar *statusBar;

public slots :
    showAboutBox();
};

#endif // MAINWINDOW_H
