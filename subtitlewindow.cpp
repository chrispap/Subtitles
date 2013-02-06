#include "subtitlewindow.h"

#include <QCoreApplication>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFont>

const QString SubtitleWindow::play_str(">");
const QString SubtitleWindow::pause_str("||");
const QString SubtitleWindow::exit_str("X");
const QString SubtitleWindow::rw_str("<<");

SubtitleWindow::SubtitleWindow(QWidget *parent) :
    QWidget(parent),
    visible(true)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    QFont btnFont;
    btnFont.setBold(true);

    playButton = new QPushButton(play_str);
    playButton->setMaximumWidth(50);
    playButton->setFont(btnFont);

    exitButton = new QPushButton(exit_str);
    exitButton->setMaximumWidth(50);
    exitButton->setFont(btnFont);

    rwButton = new QPushButton(rw_str);
    rwButton->setMaximumWidth(50);
    rwButton->setFont(btnFont);

    timeLabel = new QLabel("00:00");
    timeLabel->setMaximumWidth(50);
    timeLabel->setAlignment(Qt::AlignCenter);

    subWidget = new SubtitleWidget(true);

    connect(playButton, SIGNAL(clicked()), subWidget, SLOT(play_pause()));
    connect(rwButton, SIGNAL(clicked()), subWidget, SLOT(rewind()));
    connect(subWidget, SIGNAL(playStarted()), this, SLOT(playStarted()));
    connect(subWidget, SIGNAL(playPaused()), this, SLOT(playPaused()));
    connect(exitButton, SIGNAL(clicked()), QCoreApplication::instance(), SLOT(quit()));
    connect(this, SIGNAL(visibilityChanged(bool)), subWidget, SLOT(setVisibility(bool)));

    QGridLayout *lout = new QGridLayout;
    lout->addWidget(exitButton, 0, 0);
    lout->addWidget(playButton, 1, 0);
    lout->addWidget(rwButton,   2, 0);
    lout->addWidget(timeLabel,  3, 0);
    lout->addWidget(subWidget,  0, 1, 4, 1);

    setLayout(lout);
}

void SubtitleWindow::toggleVisibility()
{
    visible = !visible;

    if (!visible) {
        playButton->hide();
        exitButton->hide();
        rwButton->hide();
        timeLabel->hide();
    }
    else {
        playButton->show();
        exitButton->show();
        rwButton->show();
        timeLabel->show();
    }

    emit visibilityChanged(visible);

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

void SubtitleWindow::mouseDoubleClickEvent(QMouseEvent *)
{
    toggleVisibility();
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
