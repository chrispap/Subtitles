#include "subtitlewidget.h"
#include <QDebug>

#include "time.h"

#include <QFont>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOption>

const QString SubtitleWidget::line1_def("Press Play");
const QString SubtitleWidget::line2_def(":D");

SubtitleWidget::SubtitleWidget(QWidget *parent) :
    QWidget(parent),
    paused(true),
    subOn(false),
    subIndex(0),
    timeOffset(0),
    subLine1(line1_def),
    subLine2(line2_def)
{
    /* Set the default font */
    subFont.setBold(true);
    subFont.setPointSize(25);

    /* Timer responsible for update */
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateSubtitle()));
    timer.setSingleShot(true);

    /* Load subs */
    loadSrt("/home/chris/sub.srt");
}

QSize SubtitleWidget::minimumSizeHint() const
{
    return QSize(400, 100);
}

void SubtitleWidget::loadSrt(string filename)
{
    subVec.push_back(Subtitle(1, Time(0,0,0), Time(0,0,1), string("test sub 1")));
    subVec.push_back(Subtitle(2, Time(0,0,2), Time(0,0,3), string("test sub 2")));
    subVec.push_back(Subtitle(3, Time(0,0,4), Time(0,0,8), string("test sub 3")));
}

Time SubtitleWidget::timePlaying()
{
    if (paused)
        return timeOffset;
    else
        return Time(timeOffset.msecTotal() + timeLive.elapsed());

}

void SubtitleWidget::play_pause()
{
    if (paused && !subVec.empty()) { // play
        paused = false;
        timeLive.start();
        updateSubtitle();
        emit playStarted();
    }
    else if (!paused){ // pause
        timer.stop();
        timeOffset = Time(timeOffset.msecTotal() + timeLive.elapsed());
        paused = true;
        emit playPaused();
    }
}

void SubtitleWidget::rewind()
{
    timer.stop();
    timeOffset = Time(0);
    subIndex = 0;
    paused = true;
    subLine1 = line1_def;
    subLine2 = line2_def;
    update();
    emit playPaused();
}

void SubtitleWidget::updateSubtitle()
{
    if (subIndex >= subVec.size()) {
        rewind();
        return;
    }

    Subtitle &cSub = subVec[subIndex];
    Time time = timePlaying();
    qDebug() << subIndex;
    if (time <= cSub.startTime()) { // Schedule cSub's appearence
        timer.start(cSub.startTime().msecTotal() - time.msecTotal() + 10);
        return;
    }
    else if (time >= cSub.endTime()) {
        subLine1.clear();
        subLine2.clear();
        ++subIndex;
        updateSubtitle();
    }
    else {
        /* We are inside the time span of a subtitle */
        Subtitle &nSub = subVec[subIndex];
        subLine1 = QString::fromStdString(nSub.getText());

        /* Schedule subtitle's disappearence */
        timer.start(nSub.endTime().msecTotal() - time.msecTotal() + 10);
    }

    /* Request repaint */
    update();


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
