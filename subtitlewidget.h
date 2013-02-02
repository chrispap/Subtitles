#ifndef SUBTITLEWIDGET_H
#define SUBTITLEWIDGET_H

#include "subtitle.h"
#include "time.h"

#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QTimer>
#include <QTime>
#include <vector>
#include <string>

using namespace std;

class SubtitleWidget : public QWidget
{
    Q_OBJECT

public:
    SubtitleWidget(QWidget *parent = 0);
    QSize minimumSizeHint() const;
    void loadSrt(QString filename);
    Time timePlaying();

signals:
    void playStarted();
    void playPaused();

public slots:
    void play_pause();
    void rewind();

private slots:
    void updateSubtitle();

private:
    bool paused;
    bool subOn;
    int subIndex;
    QTime timeLive;
    Time timeOffset;

    vector<Subtitle> subVec;
    QString subLine1, subLine2;
    QFont subFont;
    QTimer timer;

    static const QString line1_def, line2_def;

protected:
    void paintEvent(QPaintEvent *);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

};

#endif // SUBTITLEWIDGET_H
