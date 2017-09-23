#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "glwidget.h"
#include <iostream>
#include <string>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void createMenuBar();
    void createFileMenu();
    void createExitAction();

    void createShadingAction();
    void createShadingMenu();

    void createAboutAction();

    void createToolBar();

    void createStatusBar();

    void createSlider();
    void createResetAction();
private:
    GLWidget *myWidget;

    QMenuBar *menuBar;
    QMenu *fileMenu, *shadingMenu;
    QAction *exitAction,
            *NoneMode, *FlatMode, *GouraudMode, *PhongMode,
            *aboutAction, *resetCamera;
    QToolBar *toolsBar;
    QActionGroup *shadingGroup;

    QSlider *TessellationSlider;
    QLabel *stat0;
public slots :
    void showAboutBox();
};

#endif // MAINWINDOW_H
