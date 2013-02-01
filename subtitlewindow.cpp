#include "subtitlewindow.h"

#include <QHBoxLayout>
#include <QGridLayout>
#include <QPalette>

SubtitleWindow::SubtitleWindow(QWidget *parent) :
    QWidget(parent),
    hidden(false)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    QGridLayout *lout = new QGridLayout;
    playButton = new QPushButton("Play");
    playButton->setMaximumWidth(50);
    subtitleWidget = new SubtitleWidget;
    QObject::connect(playButton, SIGNAL(clicked()), subtitleWidget, SLOT(play()));
    lout->addWidget(playButton, 0,0,1,1, Qt::AlignTop);
    lout->addWidget(subtitleWidget, 0,1);

    setLayout(lout);
}

void SubtitleWindow::toggleWindowFrame()
{
    hidden = !hidden;

    if (hidden) {
        playButton->hide();
    }
    else {
        playButton->show();
    }

    show();
}

void SubtitleWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    toggleWindowFrame();
}

void SubtitleWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    else if (event->buttons() & Qt::RightButton) {
        dragPosition = event->globalPos();
        dragSize = size();
        event->accept();
    }
}

void SubtitleWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
    else if (event->buttons() & Qt::RightButton) {
        int x = dragSize.width() - dragPosition.x() + event->globalPos().x();
        int y = dragSize.height() - dragPosition.y() + event->globalPos().y();
        resize(x, y);
        event->accept();
    }
}
