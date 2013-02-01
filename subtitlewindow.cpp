#include "subtitlewindow.h"

#include <QHBoxLayout>
#include <QPalette>

SubtitleWindow::SubtitleWindow(QWidget *parent) :
    QWidget(parent),
    hidden(false)
{
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);

    QHBoxLayout *lout = new QHBoxLayout;
    playButton = new QPushButton("Play");
    playButton->setMaximumWidth(50);
    subtitleWidget = new SubtitleWidget;
    QObject::connect(playButton, SIGNAL(clicked()), subtitleWidget, SLOT(play()));
    lout->addWidget(playButton);
    lout->addWidget(subtitleWidget);

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

