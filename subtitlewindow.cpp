#include "subtitlewindow.h"

#include <QHBoxLayout>

SubtitleWindow::SubtitleWindow(QWidget *parent) :
    QWidget(parent),
    hidden(false)
{
    setWindowFlags(Qt::WindowStaysOnTopHint);
    QHBoxLayout *lout = new QHBoxLayout;
    playButton = new QPushButton("Play");
    subtitleWidget = new SubtitleWidget;
    QObject::connect(playButton, SIGNAL(clicked()), subtitleWidget, SLOT(play()));
    lout->addWidget(playButton);
    lout->addWidget(subtitleWidget);
    setLayout(lout);
}

void SubtitleWindow::toggleWindowFrame()
{
    hidden = !hidden;

    setWindowFlags(windowFlags() ^ Qt::FramelessWindowHint);

    if (hidden)
        playButton->hide();
    else
        playButton->show();

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
}

void SubtitleWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

