#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "glwidget.h"
#include <iostream>
#include <string>
#include "view.h"
#include "model.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // == VIEWPORTS == //
    GLWidget *viewportPerspective;
    GLWidget *viewportFront;
    GLWidget *viewportLeft;
    GLWidget *viewportTop;

    void setModel(Model *model);

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

    void createInteractionMode();

    void set_ViewModeAction();
    void set_ViewModeMenu();

    void createViewports();

    void setCentralWidgets();


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

    QAction *CameraMode, *ObjectManiMode;
    QActionGroup *interactGroup;

    QToolButton *viewModeButton;
    QMenu *viewModeMenu;
    QActionGroup *viewModeGroup;
    QAction *setSingleViewModeAction, *setDualViewModeAction, *setQuadViewModeAction;

    QSplitter *splitterHorizontalTop;
    QSplitter *splitterHorizontalBottom;
    QSplitter *splitterVertical;

    Model *model_;
public slots :
    void showAboutBox();

signals:
    void setSingleViewMode();
    void setDualViewMode();
    void setQuadViewMode();
};

#endif // MAINWINDOW_H
