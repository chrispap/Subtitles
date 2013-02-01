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
    void loadSrt(string filename);

signals:
    void playStarted();
    void playPaused();

public slots:
    void play_pause();

private slots:
    void updateSubtitle();

private:
    int subIndex;
    bool paused;
    vector<Subtitle> subVec;
    QString subLine1, subLine2;
    QFont subFont;
    QTimer timer;
    QTime timeElapsed;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // SUBTITLEWIDGET_H
