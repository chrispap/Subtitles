#ifndef SUBTITLEWINDOW_H
#define SUBTITLEWINDOW_H

#include "subtitlewidget.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class SubtitleWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SubtitleWindow(QWidget *parent = 0);

signals:
    void visibilityChanged(bool visible);

private slots:
    void toggleVisibility();
    void playStarted();
    void playPaused();

protected:
    void mouseDoubleClickEvent (QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    bool visible;
    SubtitleWidget *subWidget;
    QPushButton *playButton, *exitButton, *rwButton;
    QLabel *timeLabel;
    QPoint dragPosition;
    QSize dragSize;

    static const QString play_str, pause_str, exit_str, rw_str;
    
};

#endif // SUBTITLEWINDOW_H
