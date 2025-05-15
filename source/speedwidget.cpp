#include "speedwidget.h"

SpeedWidget::SpeedWidget(QWidget *parent)
    : QWidget(parent)
    , speeds{0, 0, 0, 0}
    , scaleFactor(50.0f)
{
    QFontMetrics fm(font());
    minTextWidth = fm.horizontalAdvance("-0000") + 30;
    setMinimumSize(minTextWidth, 400);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    setMinimumSize(100, 400);
}

SpeedWidget::~SpeedWidget() {

}

void SpeedWidget::SetEAS(float value) {
    if (qFuzzyCompare(speeds[0], value))
        return;
    speeds[0] = value;
    update();
}

void SpeedWidget::SetCAS(float value) {
    if (qFuzzyCompare(speeds[1], value))
        return;
    speeds[1] = value;
    update();
}

void SpeedWidget::SetTAS(float value) {
    if (qFuzzyCompare(speeds[2], value))
        return;
    speeds[2] = value;
    update();
}

void SpeedWidget::SetGS(float value) {
    if (qFuzzyCompare(speeds[3], value))
        return;
    speeds[3] = value;
    update();
}

void SpeedWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int w = width();
    int h = height();

    // Draw background
    painter.fillRect(rect(), Qt::black);

    // Draw central line
    painter.setPen(QPen(Qt::cyan, 2));
    painter.drawLine(0, h / 2, w, h / 2);

    int columnWidth = w / 4;
    int offset = 0;
    if (columnWidth < 125) {
        offset = 125 - columnWidth;
    }

    for (int i = 0; i < 4; i++) {
        int cwr = (w / 4 * (i + 1));
        int cwl = cwr - w / 4;

        // Calculate visible range
        float unitsPerPixel = 10.0f / scaleFactor;
        float visibleRange = (h / 2.0f) * unitsPerPixel;
        float minVal = speeds[i] - visibleRange;
        float maxVal = speeds[i] + visibleRange;

        int minMark = qFloor(minVal / 10) * 10;
        minMark = minMark < 0 ? 0 : minMark;

        int maxMark = qCeil(maxVal / 10) * 10;

        painter.setPen(Qt::white);
        QFontMetrics fm(painter.font());
        const int textRightMargin = 5;

        for (int mark = minMark; mark <= maxMark; mark += 10) {
            float y = h / 2.0f - (mark - speeds[i]) * (scaleFactor / 10.0f);
            if (y < 0 || y > h) continue;

            // Draw mark
            painter.drawLine((cwr + cwl) / 2 - 10 - offset, y, (cwr + cwl) / 2 + 10 - offset, y);

            // Draw label
            QString text = QString::number(mark) + QString(" Knots");
            QRect textRect = painter.fontMetrics().boundingRect(text);
            textRect.adjust(0, 0, 5, 0);

            textRect.moveRight(cwr - textRightMargin);
            textRect.moveTop(y - textRect.height() / 2);
            textRect.moveTop(qBound(0, textRect.top(), h - textRect.height()));

            painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
        }

        QString text;
        switch(i) {
        case 0:
            text = QString("EAS");
            break;
        case 1:
            text = QString("CAS");
            break;
        case 2:
            text = QString("TAS");
            break;
        case 3:
            text = QString("GS");
            break;
        }

        QRect textRect = painter.fontMetrics().boundingRect(text);
        textRect.adjust(0, 0, 5, 0);
        textRect.moveRight((cwr + cwl) / 2 - textRect.width() / 2);
        textRect.moveBottom(h);

        painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
    }
}
