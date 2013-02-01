#include "subtitlewindow.h"

#include <QHBoxLayout>
#include <QGridLayout>
#include <QCoreApplication>

const QString SubtitleWindow::play_str(">>");
const QString SubtitleWindow::pause_str("||");
const QString SubtitleWindow::exit_str("Close");

SubtitleWindow::SubtitleWindow(QWidget *parent) :
    QWidget(parent),
    hidden(false)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    playButton = new QPushButton(play_str);
    playButton->setMaximumWidth(50);

    closeButton = new QPushButton(exit_str);
    closeButton->setMaximumWidth(50);

    timeLabel = new QLabel("00:00");
    timeLabel->setMaximumWidth(50);
    timeLabel->setAlignment(Qt::AlignCenter);

    subtitleWidget = new SubtitleWidget;

    connect(playButton, SIGNAL(clicked()), subtitleWidget, SLOT(play_pause()));
    connect(subtitleWidget, SIGNAL(playStarted()), this, SLOT(playStarted()));
    connect(subtitleWidget, SIGNAL(playPaused()), this, SLOT(playPaused()));
    connect(closeButton, SIGNAL(clicked()), QCoreApplication::instance(), SLOT(quit()));

    QGridLayout *lout = new QGridLayout;
    lout->addWidget(playButton, 0, 0);
    lout->addWidget(closeButton, 1, 0);
    lout->addWidget(timeLabel, 2, 0);
    lout->addWidget(subtitleWidget, 0, 1, 4, 1);

    setLayout(lout);
}

void SubtitleWindow::toggleWindowFrame()
{
    hidden = !hidden;

    if (hidden) {
        playButton->hide();
        closeButton->hide();
    }
    else {
        playButton->show();
        closeButton->show();
    }

    show();
}

void SubtitleWindow::playStarted()
{
    playButton->setText(pause_str);
}

void SubtitleWindow::playPaused()
{
    playButton->setText(play_str);
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
