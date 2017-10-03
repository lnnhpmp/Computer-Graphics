#-------------------------------------------------
#
# Project created by QtCreator 2017-09-20T19:17:58
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hellocube
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    camera.cpp \
    controller.cpp \
    model.cpp \
    mousecontroller.cpp \
    primitive.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    glut/glut.h \
    camera.h \
    controller.h \
    model.h \
    mousecontroller.h \
    primitive.h


LIBS   += -lopengl32 -lglu32
LIBS   += -L$$PWD/glut

DISTFILES +=

RESOURCES += \
    hellocube.qrc



