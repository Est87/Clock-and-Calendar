#include "newApp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    newApp w;
    w.show();
    return a.exec();
}
