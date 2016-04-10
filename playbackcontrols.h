#ifndef ANIMATION_CONTROL_H
#define ANIMATION_CONTROL_H

#include "ui_playbackcontrols.h"
#include <QWidget>
#include <QGroupBox>

class PlaybackControls : public QWidget, public Ui::PlaybackControls
{
    Q_OBJECT

public:
    PlaybackControls(QWidget *parent = 0);
    bool isPlaying() const { return m_is_playing; }
    float speed() const;
    void setSpeed(float speed);

public slots:
    void play();
    void pause();
    void setTimebar(float a);

signals:
    void playPressed();
    void pausePressed();
    void rewindPressed();
    void timebarMoved(float a);
    void speedChanged(float v);

private:
    bool m_is_playing;
};

#endif
