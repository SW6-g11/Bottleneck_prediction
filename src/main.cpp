#include "mainwindow.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow& w = MainWindow::getInstance(); // Retrieve the singleton instance
    w.show();
    return a.exec();
}