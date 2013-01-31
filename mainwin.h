#ifndef MAINWIN_H
#define MAINWIN_H

#include <QtGui/QMainWindow>
#include "subtitlewidget.h"

class MainWin : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWin(QWidget *parent = 0);
    ~MainWin();

private:
    SubtitleWidget subWidget;

};

#endif // MAINWIN_H
