#include "scrollareawithmask.h"
#include <QLinearGradient>
#include <QPaintEvent>

ScrollAreaWithMask::ScrollAreaWithMask(QWidget *parent)
    : QScrollArea(parent),
      m_maskHeight(24),      // h-6 = 24px
      m_topMaskEnabled(true),
      m_bottomMaskEnabled(true)
{
    // 设置为透明背景以便渐变遮罩可见
    setAttribute(Qt::WA_OpaquePaintEvent, false);
}

void ScrollAreaWithMask::setMaskHeight(int height)
{
    m_maskHeight = height;
    update();
}

void ScrollAreaWithMask::setTopMaskEnabled(bool enabled)
{
    m_topMaskEnabled = enabled;
    update();
}

void ScrollAreaWithMask::setBottomMaskEnabled(bool enabled)
{
    m_bottomMaskEnabled = enabled;
    update();
}

void ScrollAreaWithMask::paintEvent(QPaintEvent *event)
{
    // 先绘制滚动区域本身
    QScrollArea::paintEvent(event);

    // 然后在上面绘制渐变遮罩
    QPainter painter(viewport());
    painter.setRenderHint(QPainter::Antialiasing);

    paintGradientMask(painter);
}

void ScrollAreaWithMask::paintGradientMask(QPainter &painter)
{
    QRect viewportRect = viewport()->rect();

    // 顶部渐变遮罩: bg-gradient-to-b from-black/5 to-transparent
    if (m_topMaskEnabled) {
        QLinearGradient topGradient(
            viewportRect.topLeft(),
            QPoint(viewportRect.left(), m_maskHeight)
        );
        topGradient.setColorAt(0, QColor(0, 0, 0, 13));  // from-black/5 = rgba(0,0,0,0.05)
        topGradient.setColorAt(1, QColor(0, 0, 0, 0));   // to-transparent

        QRect topMaskRect(0, 0, viewportRect.width(), m_maskHeight);
        painter.fillRect(topMaskRect, topGradient);
    }

    // 底部渐变遮罩: bg-gradient-to-t from-black/5 to-transparent
    if (m_bottomMaskEnabled) {
        QLinearGradient bottomGradient(
            QPoint(viewportRect.left(), viewportRect.height() - m_maskHeight),
            viewportRect.bottomLeft()
        );
        bottomGradient.setColorAt(0, QColor(0, 0, 0, 0));   // to-transparent
        bottomGradient.setColorAt(1, QColor(0, 0, 0, 13));  // from-black/5

        QRect bottomMaskRect(
            0,
            viewportRect.height() - m_maskHeight,
            viewportRect.width(),
            m_maskHeight
        );
        painter.fillRect(bottomMaskRect, bottomGradient);
    }
}
