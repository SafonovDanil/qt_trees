#include "mainwindow.h"
#include "basic_tree.h"
#include "search_tree.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
