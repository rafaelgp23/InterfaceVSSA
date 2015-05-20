#-------------------------------------------------
#
# Project created by QtCreator 2015-05-19T18:08:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = interface
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


INCLUDEPATH += /usr/local/include/
INCLUDEPATH += /usr/local/include/opencv2/
INCLUDEPATH += /usr/local/include/opencv/

LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_features2d -lopencv_calib3d


RESOURCES += \
    robok.qrc
