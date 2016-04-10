#include "subtitlewidget.h"
#include "time.h"

#include <QFont>
#include <QUrl>
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOption>
#include <QDragEnterEvent>
#include <QMimeData>

using namespace std;

const QString SubtitleWidget::ready_str1("Loaded succesfully");
const QString SubtitleWidget::ready_str2("Press Play");
const QString SubtitleWidget::promt_str1("Drop");
const QString SubtitleWidget::promt_str2("Subtitle File");

SubtitleWidget::SubtitleWidget(bool _visible, QWidget *parent) :
    QWidget(parent),
    m_visible(_visible),
    m_paused(true),
    m_sub_on(false),
    m_sub_index(0),
    m_time_offset(0)
{
    /* Set the default font */
    m_sub_font.setBold(true);
    m_sub_font.setPointSize(23);

    m_sub_lines.push_back(promt_str1);
    m_sub_lines.push_back(promt_str2);

    /* Timer responsible for update */
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(updateSubtitle()));
    m_timer.setSingleShot(true);

    setAcceptDrops(true);
}

QSize SubtitleWidget::minimumSizeHint() const
{
    return QSize(800, 200);
}

void SubtitleWidget::setVisibility(bool _visible)
{
    m_visible = _visible;
    update();
}

void SubtitleWidget::loadSrt(QString filename)
{
    vector<QString> lines;
    int id, h[2], m[2], s[2], ms[2];
    char c;
    QString str;

    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) return;

    // Shouldn't clear the previous subs before ensuring that we have a valid .srt file but anyway...
    m_subs.clear();

    QTextStream stream(&file);
    stream.setIntegerBase(10);

    while (!stream.atEnd()) {
        /* Read subtitle id */
        id = stream.readLine().toInt();
        stream.skipWhiteSpace();

        /* Read start/end time */
        stream >> h[0] >> c >> m[0] >> c >> s[0] >> c >> ms[0] >> str >> // Start time --> ...
                h[1] >> c >> m[1] >> c >> s[1] >> c >> ms[1]; // ... end time
        stream.skipWhiteSpace();

        /* Read subtitle text lines */
        while ((str=stream.readLine()).size()>0) lines.push_back(str);

        Subtitle sub(id, Time(h[0],m[0],s[0],ms[0]), Time(h[1],m[1],s[1],ms[1]), lines);
        m_subs.push_back(sub);
        lines.clear();
        stream.skipWhiteSpace();
    }

    file.close(); // when your done.

    rewind();
    m_sub_lines.push_back(ready_str1);
    m_sub_lines.push_back(ready_str2);
    update();
}

Time SubtitleWidget::timePlaying()
{
    if (m_paused)
    {
        return m_time_offset;
    }
    else
    {
        return m_time_offset.msecTotal() + m_time_live.elapsed();
    }
}

Time SubtitleWidget::totalTime()
{
    return m_subs.empty() ? 0 : m_subs.back().endTime();
}

void SubtitleWidget::play_pause()
{
    if (m_paused && !m_subs.empty())  // Play
    {
        m_paused = false;
        m_time_live.start();
        updateSubtitle();
        emit playStarted();
    }
    else if (!m_paused)               // Pause
    {
        m_timer.stop();
        m_time_offset = Time(m_time_offset.msecTotal() + m_time_live.elapsed());
        m_paused = true;
        emit playPaused();
    }
}

void SubtitleWidget::rewind()
{
    m_timer.stop();
    m_time_offset = 0;
    m_sub_index = 0;
    m_paused = true;
    m_sub_lines.clear();
    update();
    emit playPaused();
}

void SubtitleWidget::setTime(float a)
{
    const Time &tt = totalTime();
    if (tt.msecTotal() == 0) return;

    //TODO: Find subtitle index for this time moment
    m_time_offset = a * tt.msecTotal();
    m_time_live.start();
}

void SubtitleWidget::updateSubtitle()
{
    if (m_sub_index >= m_subs.size())
    {
        rewind();
        return;
    }

    const Subtitle &sub = m_subs[m_sub_index];
    const Time time = timePlaying();

    if (time <= sub.startTime())  // Schedule sub's appearence
    {
        m_timer.start(sub.startTime().msecTotal() - time.msecTotal() + 10);
        return;
    }
    else if (time >= sub.endTime())
    {
        m_sub_lines.clear();
        ++m_sub_index;
        updateSubtitle(); //! <<< Recursion...
    }
    else
    {
        /* We are inside the time span of a subtitle */
        m_sub_lines = sub.getLines();

        /* Schedule subtitle's disappearence */
        m_timer.start(sub.endTime().msecTotal() - time.msecTotal() + 10);
    }

    /* Request repaint */
    update();
}

void SubtitleWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), QColor(100,100,100,m_visible?200:1));

    QPainterPath path;
    painter.setFont(m_sub_font);
    QFontMetrics fm(m_sub_font);

    for (int i=0; i< m_sub_lines.size(); ++i) {
        path.addText(width()/2-fm.width(m_sub_lines[i])/2, fm.height()*(i+1.1), m_sub_font, m_sub_lines[i]);
    }

    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawPath(path);
}

void SubtitleWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void SubtitleWidget::dropEvent(QDropEvent *event)
{
    const QMimeData* mimeData = event->mimeData();

    if (mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();

        for (int i = 0; i < urlList.size() && i < 1; ++i) {
            loadSrt(urlList.at(i).toLocalFile());
        }
    }
}
