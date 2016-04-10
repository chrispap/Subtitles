#ifndef SUBTITLEWINDOW_H
#define SUBTITLEWINDOW_H

#include "subtitlewidget.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>

class PlaybackControls;

class SubtitleWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SubtitleWindow(QWidget *parent = 0);

signals:
    void visibilityChanged(bool m_visible);

private slots:
    void toggleVisibility();
    void onTimeChanged();

protected:
    void mouseDoubleClickEvent (QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    bool m_visible;
    PlaybackControls *m_playback_controls;
    SubtitleWidget *m_subtitle_widget;
    QPushButton *m_btn_exit;
    QLabel *m_timelabel;
    QPoint m_drag_pos;
    QSize m_drag_size;
    QTimer m_timer;

    static const QString exit_str;
};

#endif // SUBTITLEWINDOW_H
