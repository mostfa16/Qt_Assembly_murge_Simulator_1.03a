#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    w.setWindowTitle("Assembly Murge Smulator 1.03");
    return a.exec();
}
