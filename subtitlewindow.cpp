#include "subtitlewindow.h"
#include "playbackcontrols.h"
#include <QCoreApplication>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFont>

const QString SubtitleWindow::exit_str("Close");

SubtitleWindow::SubtitleWindow(QWidget *parent)
    : QWidget(parent)
    , m_visible(true)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    QFont btnFont;
    btnFont.setBold(true);

    m_btn_exit = new QPushButton(exit_str);
    m_btn_exit->setFont(btnFont);
    m_timelabel = new QLabel("00:00");
    m_timelabel->setAlignment(Qt::AlignCenter);
    m_timelabel->setFont(btnFont);
    m_timelabel->setMaximumWidth(m_timelabel->width());
    m_playback_controls = new PlaybackControls();
    m_playback_controls->wheel_speed->hide();
    m_playback_controls->label_speed->hide();
    m_playback_controls->value_speed->hide();
    m_subtitle_widget = new SubtitleWidget(true);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(m_btn_exit,           0, 0, 1, 2);
    layout->addWidget(m_subtitle_widget,    1, 0, 1, 2);
    layout->addWidget(m_timelabel,          2, 1, 1, 1);
    layout->addWidget(m_playback_controls,  2, 0, 1, 1);
    setLayout(layout);

    connect(m_playback_controls, SIGNAL(playPressed()), m_subtitle_widget, SLOT(play_pause()));
    connect(m_playback_controls, SIGNAL(pausePressed()), m_subtitle_widget, SLOT(play_pause()));
    connect(m_playback_controls, SIGNAL(rewindPressed()), m_subtitle_widget, SLOT(rewind()));
    connect(m_playback_controls, SIGNAL(timebarMoved(float)), m_subtitle_widget, SLOT(setTime(float)));
    connect(m_subtitle_widget, SIGNAL(playStarted()), m_playback_controls, SLOT(play()));
    connect(m_subtitle_widget, SIGNAL(playPaused()), m_playback_controls, SLOT(pause()));
    connect(m_btn_exit, SIGNAL(clicked()), QCoreApplication::instance(), SLOT(quit()));
    connect(this, SIGNAL(visibilityChanged(bool)), m_subtitle_widget, SLOT(setVisibility(bool)));
    connect(&m_timer, &QTimer::timeout, this, &SubtitleWindow::onTimeChanged);
    m_timer.start(70);
}

void SubtitleWindow::onTimeChanged()
{
    const Time &t = m_subtitle_widget->timePlaying();
    const Time &tt = m_subtitle_widget->totalTime();

    if (tt.msecTotal()>0)
    {
        m_playback_controls->setTimebar((float)t.msecTotal()/tt.msecTotal());
    }

    m_timelabel->setText(QString("%1:%2:%3")
                         .arg(t.hour())
                         .arg(t.min(), 2, 10, QChar('0'))
                         .arg(t.sec(), 2, 10, QChar('0')));
}

void SubtitleWindow::toggleVisibility()
{
    m_visible = !m_visible;

    if (!m_visible)
    {
        m_playback_controls->hide();
        m_btn_exit->hide();
        m_timelabel->hide();
    }
    else
    {
        m_playback_controls->show();
        m_btn_exit->show();
        m_timelabel->show();
    }

    emit visibilityChanged(m_visible);

    show();
}

void SubtitleWindow::mouseDoubleClickEvent(QMouseEvent *)
{
    toggleVisibility();
}

void SubtitleWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_drag_pos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    else if (event->buttons() & Qt::RightButton)
    {
        m_drag_pos = event->globalPos();
        m_drag_size = size();
        event->accept();
    }
}

void SubtitleWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - m_drag_pos);
        event->accept();
    }
    else if (event->buttons() & Qt::RightButton)
    {
        int x = m_drag_size.width() - m_drag_pos.x() + event->globalPos().x();
        int y = m_drag_size.height() - m_drag_pos.y() + event->globalPos().y();
        resize(x, y);
        event->accept();
    }
}
