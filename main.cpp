#include <QApplication>
#include "mainwindow.h"
#include<QtGui>
#include<QtCore>
#include<qwidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.setWindowTitle("kostka 3d");
    window.show();

    return a.exec();
}
