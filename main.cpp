#include <QtGui/QApplication>
#include "subtitlewidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SubtitleWidget w;
    w.show();
    
    return a.exec();
}
