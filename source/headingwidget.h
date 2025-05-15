#ifndef HEADINGWIDGET_H
#define HEADINGWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QtMath>
#include <QFontMetrics>

class HeadingWidget : public QWidget
{

    Q_OBJECT

public:
    HeadingWidget(QWidget *parent = nullptr);
    ~HeadingWidget();

private:
    float headings[2];
    float scaleFactor;
    int minHeight;

protected:
    void paintEvent(QPaintEvent *) override;

public slots:
    void SetTrueHeading(float value);
    void SetMagHeading(float value);
};

#endif // HEADINGWIDGET_H
