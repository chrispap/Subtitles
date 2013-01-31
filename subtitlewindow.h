#ifndef SUBTITLEWINDOW_H
#define SUBTITLEWINDOW_H

#include "subtitlewidget.h"

#include <QWidget>
#include <QPushButton>

class SubtitleWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SubtitleWindow(QWidget *parent = 0);

private slots:
    void toggleWindowFrame();

protected:
    void mouseDoubleClickEvent (QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    bool hidden;
    SubtitleWidget *subtitleWidget;
    QPushButton *playButton;
    QPoint dragPosition;
    
};

#endif // SUBTITLEWINDOW_H
