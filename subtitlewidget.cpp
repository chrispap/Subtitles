#include "subtitlewidget.h"

#include <QFont>
#include <QPainter>
#include <QPainterPath>

SubtitleWidget::SubtitleWidget(QWidget *parent) :
    QWidget(parent),
    currentSubIndex(-1),
    currentMsec(0),
    paused(true),
    currentTxt("Press Play")
{
    /* Set the default font */
    subtitleFont.setBold(true);
    subtitleFont.setPointSize(19);

    /* Timer responsible for update */
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateSubtitle()));

    /* Load subs */
    loadSrt("/home/chris/sub.srt");
}

QSize SubtitleWidget::minimumSizeHint() const
{
    return QSize(400, 50);
}

void SubtitleWidget::loadSrt(string filename)
{
    subVec.push_back(Subtitle(1, Time(0,0,2), Time(0,0,4), string("test sub 1 \n Line _ 2 !")));
    subVec.push_back(Subtitle(2, Time(0,0,2), Time(0,0,6), string("test sub 2")));
    subVec.push_back(Subtitle(3, Time(0,0,2), Time(0,0,4), string("test sub 3 \n Line _ 2 !")));

}

void SubtitleWidget::play()
{
    if (paused && !subVec.empty()) {
        paused = false;
        updateSubtitle();
    }
}

void SubtitleWidget::pause()
{
    paused = true;
    timer.stop();
}

void SubtitleWidget::updateSubtitle()
{
    // Just for tests loop...
    if (++currentSubIndex >= subVec.size()) currentSubIndex=0;

    /* Find the current subtitle */
    Subtitle &curSub = subVec[currentSubIndex];
    currentTxt = QString::fromStdString(curSub.getText());

    /* Request repaint */
    update();

    /* Setup timer for this subtitle's duration
       or for the next subtitle appearence*/
    timer.start(curSub.duration());
}

void SubtitleWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(subtitleFont);
    QFontMetrics fm(subtitleFont);
    int x = width()/2 - fm.width(currentTxt)/2;
    int y = height()/2;

    QPainterPath path;
    path.addText(x,y, subtitleFont, currentTxt);
    //painter.setPen(pen);
    //painter.setBrush(brush);
    painter.drawPath(path);

}
