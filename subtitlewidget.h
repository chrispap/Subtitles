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
    vector<QString> subLines;
    QFont subFont;
    QTimer timer;

    static const QString ready_str, promt_str;

protected:
    void paintEvent(QPaintEvent *);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

};

#endif // SUBTITLEWIDGET_H
