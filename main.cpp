#include "subtitlewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SubtitleWindow w;
    w.show();
    return a.exec();
}
