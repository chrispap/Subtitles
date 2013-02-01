#include "subtitlewidget.h"
#include <QDebug>

#include <QFont>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOption>

SubtitleWidget::SubtitleWidget(QWidget *parent) :
    QWidget(parent),
    subIndex(0),
    paused(true),
    subLine1("Press Play"),
    subLine2(":D")
{
    /* Set the default font */
    subFont.setBold(true);
    subFont.setPointSize(25);

    /* Timer responsible for update */
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateSubtitle()));

    /* Load subs */
    loadSrt("/home/chris/sub.srt");
}

QSize SubtitleWidget::minimumSizeHint() const
{
    return QSize(400, 100);
}

void SubtitleWidget::loadSrt(string filename)
{
    subVec.push_back(Subtitle(1, Time(0,0,2), Time(0,0,3), string("test sub 1")));
    subVec.push_back(Subtitle(2, Time(0,0,4), Time(0,0,5), string("test sub   2")));
    subVec.push_back(Subtitle(3, Time(0,0,6), Time(0,0,6,500), string("test sub     3")));
}

void SubtitleWidget::play_pause()
{
    if (paused && !subVec.empty()) {
        paused = false;
        updateSubtitle();
        emit playStarted();
    }
    else if (!paused){
        paused = true;
        timer.stop();
        emit playPaused();
    }
}

void SubtitleWidget::updateSubtitle()
{
    // Just for tests loop...
    if (++subIndex >= subVec.size()) subIndex=0;

    /* Find the current subtitle */
    Subtitle &curSub = subVec[subIndex];
    subLine1 = QString::fromStdString(curSub.getText());

    /* Request repaint */
    update();

    /* Setup timer for this subtitle's duration
       or for the next subtitle appearence*/
    qDebug() << curSub.duration();
    timer.start(curSub.duration());
}

void SubtitleWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setFont(subFont);
    QFontMetrics fm(subFont);

    painter.fillRect(rect(), QColor(100,100,100,50));
    QPainterPath path;
    path.addText(width()/2-fm.width(subLine1)/2, fm.height(), subFont, subLine1);
    path.addText(width()/2-fm.width(subLine2)/2, fm.height()*2.1, subFont, subLine2);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawPath(path);
}
