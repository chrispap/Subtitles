#include "subtitlewidget.h"

SubtitleWidget::SubtitleWidget(QWidget *parent) :
    QWidget(parent)
{
}

QSize SubtitleWidget::minimumSizeHint() const
{
    return QSize(200, 50);
}

QSize SubtitleWidget::sizeHint() const
{
    return QSize(200, 50);
}

void SubtitleWidget::clearTxt()
{

}

void SubtitleWidget::setTxt(QString txt)
{

}

void SubtitleWidget::paintEvent(QPaintEvent *event)
{

}
