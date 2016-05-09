#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("C&L Company");
    a.setApplicationName("Stock Analysis Application");
    MainWindow w;
    w.show();

    return a.exec();
}
