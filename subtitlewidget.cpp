#include "subtitlewidget.h"

#include <QFont>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOption>

SubtitleWidget::SubtitleWidget(QWidget *parent) :
    QWidget(parent),
    currentSubIndex(-1),
    currentMsec(0),
    paused(true),
    mWidth(600),
    mHeight(100),
    currentTxt("Press Play")
{
    /* Set the default font */
    subtitleFont.setBold(true);
    subtitleFont.setPointSize(25);

    /* Timer responsible for update */
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateSubtitle()));

    /* Load subs */
    loadSrt("/home/chris/sub.srt");
}

QSize SubtitleWidget::minimumSizeHint() const
{
    return QSize(mWidth, mHeight);
}

void SubtitleWidget::loadSrt(string filename)
{
    subVec.push_back(Subtitle(1, Time(0,0,2), Time(0,0,4), string("test sub 1")));
    subVec.push_back(Subtitle(2, Time(0,0,2), Time(0,0,6), string("test sub   2")));
    subVec.push_back(Subtitle(3, Time(0,0,2), Time(0,0,4), string("test sub     3")));

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

void SubtitleWidget::resizeEvent(QResizeEvent *evt)
{
    mWidth = width();
    mHeight = height();
}

void SubtitleWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setFont(subtitleFont);
    QFontMetrics fm(subtitleFont);
    int txtWidth = fm.width(currentTxt);
    int txtHeight = fm.height();
    float s = 0.8 * qMin(width()/txtWidth, height()/txtHeight);

    painter.fillRect(rect(), QColor(100,100,100,50));
    QPainterPath path;
    path.addText(width()/2-txtWidth/2, txtHeight, subtitleFont, currentTxt);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawPath(path);
}
