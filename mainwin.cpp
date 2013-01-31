#include "mainwin.h"

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowFlags(Qt::WindowStaysOnTopHint);
    //setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("background:transparent;");

}

MainWin::~MainWin()
{
    
}
