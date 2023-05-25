#include "yrmainwindow.hxx"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    YRMainWindow w;
    w.show();
    return a.exec();
}
