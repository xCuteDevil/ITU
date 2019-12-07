#include "mainwindow.h"

#include <QApplication>

/*
 *  Application starts here :-))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))42
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
