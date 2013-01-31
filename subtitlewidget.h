#ifndef SUBTITLEWIDGET_H
#define SUBTITLEWIDGET_H

#include "subtitle.h"
#include "time.h"

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QMouseEvent>
#include <QList>
#include <QPoint>
#include <QPushButton>
#include <vector>
#include <string>

using namespace std;

class SubtitleWidget : public QWidget
{
    Q_OBJECT

public:
    SubtitleWidget(QWidget *parent = 0);
    void loadSubs(string filename);
    QSize minimumSizeHint() const;

public slots:
    void play();
    void pause();

private slots:
    void updateSub();
    void toggleWindow();

private:
    QPoint dragPosition;
    bool hidden;
    QList<QString> subList;
    QPushButton *btnPlay;
    void setSub();
    QString subTxt;
    QFont font;
    vector<Subtitle> subVec;
    QTimer timer;
    bool paused;
    Time currentTime;
    int currentSubIndex;

protected:
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent (QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // SUBTITLEWIDGET_H
