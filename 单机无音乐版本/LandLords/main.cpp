#include "interface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
    Interface w;
    w.setWindowTitle("首页");
    w.show();

    return a.exec();
}
