#include "subtitlewidget.h"

#include <string>
#include <QFont>
#include <QTime>
#include <QGridLayout>
#include <QPainter>
#include <QPainterPath>

SubtitleWidget::SubtitleWidget(QWidget *parent) :
    QWidget(parent),
    currentSubIndex(-1),
    currentTime(),
    paused(true),
    subTxt("Press Play")
{
    /* Always on top */
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint );

    /* Make the widgets */
    btnPlay = new QPushButton(">>", this);

    loadSubs("/home/chris/sub.srt");

    font.setBold(true);
    font.setPointSize(19);

    /* Make the connections */
    connect(btnPlay, SIGNAL(clicked()), this, SLOT(play()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateSub()));
}

QSize SubtitleWidget::minimumSizeHint() const
{
    return QSize(400, 50);
}

void SubtitleWidget::loadSubs(string filename)
{
    subVec.push_back(Subtitle(1, Time(0,0,2), Time(0,0,4), string("test sub 1 \n Line _ 2 !")));
    subVec.push_back(Subtitle(2, Time(0,0,2), Time(0,0,6), string("test sub 2")));
    subVec.push_back(Subtitle(3, Time(0,0,2), Time(0,0,4), string("test sub 3 \n Line _ 2 !")));

}

void SubtitleWidget::play()
{
    if (paused && !subVec.empty()) {
        paused = false;
        timer.start();
    }
}

void SubtitleWidget::pause()
{
    paused = true;
}

void SubtitleWidget::updateSub()
{
    if (++currentSubIndex >= subVec.size())
        currentSubIndex=0;

    Subtitle &curSub = subVec[currentSubIndex];
    subTxt = QString::fromStdString(curSub.getText());
    update();

    timer.start(curSub.duration());
}

void SubtitleWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(font);
    QFontMetrics fm(font);
    int x = width()/2 - fm.width(subTxt)/2;
    int y = height()/2;

    QPainterPath path;
    path.addText(x,y, font, subTxt);
    //painter.setPen(pen);
    //painter.setBrush(brush);
    painter.drawPath(path);

}

void SubtitleWidget::toggleWindow()
{
    hidden = !hidden;

    if (hidden)
        btnPlay->hide();
    else
        btnPlay->show();

    setWindowFlags(windowFlags() ^ Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground, hidden);
    show();
}

void SubtitleWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    toggleWindow();
}

void SubtitleWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void SubtitleWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

