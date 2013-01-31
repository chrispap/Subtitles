#ifndef SUBTITLEWIDGET_H
#define SUBTITLEWIDGET_H

#include "subtitle.h"
#include "time.h"

#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QTimer>
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

public slots:
    void play();
    void pause();

private slots:
    void updateSubtitle();

private:
    vector<Subtitle> subVec;
    QString currentTxt;
    QFont subtitleFont;
    QTimer timer;
    Time currentMsec;
    int currentSubIndex;
    bool paused;
    int mWidth, mHeight;

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
};

#endif // SUBTITLEWIDGET_H
