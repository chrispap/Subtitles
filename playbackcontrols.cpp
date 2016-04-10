#include "playbackcontrols.h"
#include <QTimer>

#define SPEED_DECI_DIGITS 3

PlaybackControls::PlaybackControls(QWidget *parent)
    : QWidget(parent)
    , m_is_playing(false)
{
    setupUi(this);

    value_speed->setText(QString::number(wheel_speed->value(), 'f', SPEED_DECI_DIGITS));

    connect(btn_play_pause, &QPushButton::clicked, [=](){
        if (m_is_playing) emit pausePressed();
        else emit playPressed();
    });

    connect(btn_rewind, &QPushButton::clicked, [=](){
        emit rewindPressed();
    });

    connect(slider_timebar, &QSlider::sliderMoved, [=](){
        emit timebarMoved((float)slider_timebar->value() / slider_timebar->maximum());
    });

    connect(wheel_speed, &QwtWheel::valueChanged, [=](double v){
        value_speed->setText(QString::number(v, 'f', SPEED_DECI_DIGITS));
        emit speedChanged((float)v);
    });

    QTimer::singleShot(100, [&]() {
        setFixedHeight(height()); 
    });
}

void PlaybackControls::play()
{
    btn_play_pause->setText("Pause");
    btn_play_pause->setIcon(QIcon(":/Icons/pause.png"));
    m_is_playing = true;
}

void PlaybackControls::pause()
{
    btn_play_pause->setText("Play");
    btn_play_pause->setIcon(QIcon(":/Icons/play.png"));
    m_is_playing = false;
}

void PlaybackControls::setTimebar(float a)
{
    slider_timebar->setValue(a*slider_timebar->maximum());
}

float PlaybackControls::speed() const 
{ 
    return value_speed->text().toFloat(); 
}

void PlaybackControls::setSpeed(float speed) 
{
    value_speed->setText(QString::number(speed, 'f', SPEED_DECI_DIGITS));
    wheel_speed->setValue(speed);
}
