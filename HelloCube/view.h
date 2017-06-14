#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "model.h"

class View : public QMainWindow
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = 0);
    void setModel(Model *model);

private:
    /**********file menu**********/
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QAction *exitAction;
    /**********file menu**********/

    /**********shading menu**********/
    QMenu *shadingMenu;
    QAction *noneAction;
    QAction *flatAction;
    QAction *gouraudAction;
    QAction *phongAction;
    /**********shading menu**********/

    /**********about**********/
    QAction *aboutAction;
    /**********about**********/

    QToolBar *tool;

    Model *mymodel;
protected:
    void FileMenu();
    void ShadingMenu();
    void ToolBar();
    void MenuBar();
signals:

public slots:
    void showAboutBox();
};

#endif // VIEW_H
