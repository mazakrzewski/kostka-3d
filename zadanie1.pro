QT += core gui widgets

CONFIG += c++11

TARGET = zadanie1

TEMPLATE = app

SOURCES += main.cpp \
    mowidget.cpp \
    mainwindow.cpp \
    draw.cpp \
    types.cpp \
    files.cpp \
    miksuj.cpp \
    rotate_class.cpp \
    figury.cpp \
    trojkoty.cpp \
    krawedz.cpp \
    rotate_3d_class.cpp

HEADERS += \
    mowidget.h \
    mainwindow.h \
    types.h \
    rotate_class.h \
    miksuj.h \
    figury.h \
    trojkoty.h \
    krawedz.h \
    punkt_struct.h \
    rotate_3d_class.h

FORMS += \
    mainwindow.ui



LIBS += -llapack -lblas -larmadillo
