#include "subtitlewidget.h"
#include <QDebug>

#include "time.h"

#include <QFont>
#include <QUrl>
#include <Qfile.h>
#include <Qtextstream.h>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOption>

const QString SubtitleWidget::ready_str("Press Play");
const QString SubtitleWidget::promt_str("Drag & Drop .srt file here.");

SubtitleWidget::SubtitleWidget(QWidget *parent) :
    QWidget(parent),
    paused(true),
    subOn(false),
    subIndex(0),
    timeOffset(0)
{
    /* Set the default font */
    subFont.setBold(true);
    subFont.setPointSize(23);

    subLines.push_back(promt_str);

    /* Timer responsible for update */
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateSubtitle()));
    timer.setSingleShot(true);

    setAcceptDrops(true);
}

QSize SubtitleWidget::minimumSizeHint() const
{
    return QSize(600, 120);
}

void SubtitleWidget::loadSrt(QString filename)
{
    vector<QString> lines;
    int id, h[2], m[2], s[2], ms[2];
    char c;
    QString str;

    QFile file(filename);
    if (!file.open(QFile::ReadOnly))
        return ;

    QTextStream stream(&file);
    while (!stream.atEnd()) {
        id = stream.readLine().toInt();

        stream >>
            id >> h[0] >> c >> m[0] >> c >> s[0] >> c >> ms[0] >> str >>
            id >> h[1] >> c >> m[1] >> c >> s[1] >> c >> ms[1];

        stream.skipWhiteSpace();

        while ((str=stream.readLine()).size()>0)
            lines.push_back(str);

        subVec.push_back(Subtitle(id, Time(h[0],m[0],s[0],ms[0]), Time(h[1],m[1],s[1],ms[1]), lines));
        lines.clear();
        stream.skipWhiteSpace();
    }

    file.close(); // when your done.

    subLines.clear();
    subLines.push_back(ready_str);
    update();
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
    subLines.clear();
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
        subLines.clear();
        ++subIndex;
        updateSubtitle();
    }
    else {
        /* We are inside the time span of a subtitle */
        Subtitle &nSub = subVec[subIndex];
        subLines = nSub.getLines();

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

    for (int i=0; i< subLines.size(); ++i)
        path.addText(width()/2-fm.width(subLines[i])/2, fm.height()*(i+1.1), subFont, subLines[i]);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawPath(path);
}

void SubtitleWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}


void SubtitleWidget::dropEvent(QDropEvent *event)
{
    const QMimeData* mimeData = event->mimeData();

    if (mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();

        for (int i = 0; i < urlList.size() && i < 1; ++i)
            loadSrt(urlList.at(i).toLocalFile());

    }
}
