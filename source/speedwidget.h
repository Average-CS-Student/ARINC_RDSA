#ifndef SPEEDWIDGET_H
#define SPEEDWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QtMath>
#include <limits>

class SpeedWidget : public QWidget
{
    Q_OBJECT

public:
    SpeedWidget(QWidget *parent = nullptr);
    ~SpeedWidget();

private:
    float speeds[4];
    float scaleFactor;
    int minTextWidth = 0;

protected:
    void paintEvent(QPaintEvent *) override;

public slots:
    void SetEAS(float value);
    void SetCAS(float value);
    void SetTAS(float value);
    void SetGS(float value);

};

#endif // SPEEDWIDGET_H
