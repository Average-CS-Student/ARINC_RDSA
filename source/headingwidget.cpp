#include "headingwidget.h"

HeadingWidget::HeadingWidget(QWidget *parent)
    : QWidget(parent)
    , headings{ 0, 0 }
    , scaleFactor(25.0f)
{
    QFontMetrics fm(font());
    minHeight = fm.height() * 2 + 20;
    setMinimumSize(400, minHeight);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
}

HeadingWidget::~HeadingWidget() {

}

void HeadingWidget::SetTrueHeading(float value) {
    value = fmod(value, 360.0f);
    value += 180.0f;

    if (qFuzzyCompare(headings[0], value))
        return;

    headings[0] = value;
    update();
}

void HeadingWidget::SetMagHeading(float value) {
    value = fmod(value, 360.0f);
    value += 180.0f;

    if (qFuzzyCompare(headings[1], value))
        return;

    headings[1] = value;
    update();
}

void HeadingWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int w = width();
    int h = height();
    const float centerX = w / 2.0f;

    painter.fillRect(rect(), QColor(QRgb(0x555555)));

    int rowHeight = h / 2;

    for (int i = 0; i < 2; i++) {
        int crt = h / (i + 1);
        int crb = crt - rowHeight;

        painter.setPen(QPen(Qt::cyan, 2));
        painter.drawLine(centerX, crt - 35, centerX, crt - 45);

        const float spreadIntensity = 0.0035f;
        const float minStep = 0.6f;
        const float maxStep = 15.0f;

        const float scaleGrowth = 0.0005f;

        painter.setPen(Qt::white);
        QFontMetrics fm(painter.font());
        const int textPadding = 8;

        for (float mark = 0.0f; mark < 360.0f; mark += 1.0f) {
            float diff = fmod(mark - headings[0] + 180.0f, 360.0f) - 180.0f;
            float absDiff = std::abs(diff);

            float spreadFactor = minStep + spreadIntensity * absDiff;
            float spacingDiff = diff * spreadFactor;

            float xPos = centerX + spacingDiff * (scaleFactor / 10.0f);
            if (xPos < -50 || xPos > w + 50) continue;

            const float decayPower = 3.5f;
            float decayRange = 200.0f;
            float t = (absDiff + 15) / decayRange;
            float sizeMultiplier = 1.0f - pow(t, decayPower);
            float markHeight = rowHeight / 4.0f * sizeMultiplier;
            markHeight = qMax(5.0f, markHeight);

            if (qFuzzyIsNull(fmod(mark, 10.0f))) {
                painter.setPen(QPen(Qt::white, 1.5f));
                painter.drawLine(xPos, (crt + crb) / 2 - markHeight, xPos, (crt + crb) / 2 + markHeight);

                if (absDiff < 180 && qFuzzyIsNull(fmod(mark, 30.0f))) {
                    QString text = QString::number(static_cast<int>(mark));
                    QRect textRect = fm.boundingRect(text);
                    textRect.adjust(0,0,5,0);
                    textRect.moveCenter(QPoint(xPos, (crt + crb) / 2 - markHeight - textPadding));
                    painter.drawText(textRect, Qt::AlignCenter, text);
                }
            }
        }

        QString text;
        if (i == 0) {
            text = QString("True Heading");
        }
        else {
            text = QString("Magnetic Heading");
        }
        QRect textRect = fm.boundingRect(text);
        textRect.adjust(0,0,5,0);
        textRect.moveTopRight(QPoint(w, crb));
        painter.drawText(textRect, Qt::AlignCenter, text);
    }


}
