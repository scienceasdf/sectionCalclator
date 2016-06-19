#include "widget.h"
#include <QApplication>
#include<QFile>
#include<QString>
#include<QDebug>

int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
