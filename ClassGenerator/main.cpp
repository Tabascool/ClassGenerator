#include "mainwindowv2.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowV2 w;
    w.show();

    return a.exec();
}
