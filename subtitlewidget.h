#ifndef SUBTITLEWIDGET_H
#define SUBTITLEWIDGET_H

#include <QWidget>
#include <QPainterPath>

class SubtitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SubtitleWidget(QWidget *parent = 0);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

signals:
    
public slots:
    void clearTxt();
    void setTxt(QString txt);

private:
    QString txt;
    int penWidth;
    QPainterPath path;
    QColor fillColor1;
    QColor fillColor2;
    QColor penColor;

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // SUBTITLEWIDGET_H
