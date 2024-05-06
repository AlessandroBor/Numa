#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QSequentialAnimationGroup>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Numa");
    QSequentialAnimationGroup group;
    w.show();
    return a.exec();
}



