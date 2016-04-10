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

class SubtitleWidget : public QWidget
{
    Q_OBJECT

public:
    SubtitleWidget(bool _visible, QWidget *parent = 0);
    QSize minimumSizeHint() const;
    void loadSrt(QString filename);
    Time timePlaying();
    Time totalTime();

public slots:
    void play_pause();
    void rewind();
    void setTime(float a);
    void setVisibility(bool visible);

signals:
    void playStarted();
    void playPaused();

protected:
    void paintEvent(QPaintEvent *);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private slots:
    void updateSubtitle();

private:
    std::vector<Subtitle> m_subs;
    std::vector<QString> m_sub_lines;
    unsigned m_sub_index;
    bool m_visible;
    bool m_paused;
    bool m_sub_on;
    QFont m_sub_font;
    QTime m_time_live;
    Time m_time_offset;
    QTimer m_timer;

private:
    static const QString ready_str1, ready_str2, promt_str1, promt_str2;
};

#endif // SUBTITLEWIDGET_H
