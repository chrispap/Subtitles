#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::goTransparrent()
{
    setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);

}

void MainWindow::on_btn_goTransp_clicked()
{
    goTransparrent();
}

void MainWindow::enterEvent ( QMouseEvent * event )
{
    Qt::WindowFlags flags = this->windowFlags();
    setWindowFlags(flags ^ Qt::FramelessWindowHint);
    show();
    qDebug() << "enter";
}
