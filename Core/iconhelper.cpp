#include "iconhelper.h"

#include <QPainter>
#include <QPainterPath>
#include <QtMath>

QPixmap IconHelper::draw(IconGlyph glyph, const QSize &size, const QColor &color)
{
    QSize finalSize = size.isValid() ? size : QSize(24, 24);
    QPixmap pixmap(finalSize);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(color);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setWidthF(qMax(1.2, finalSize.width() / 12.0));
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);

    QRectF rect = pixmap.rect();
    rect.adjust(pen.widthF() / 2.0, pen.widthF() / 2.0, -pen.widthF() / 2.0, -pen.widthF() / 2.0);

    switch (glyph) {
    case IconGlyph::Monitor:
        drawMonitor(painter, rect);
        break;
    case IconGlyph::Smartphone:
        drawSmartphone(painter, rect);
        break;
    case IconGlyph::Settings:
        drawSettings(painter, rect);
        break;
    case IconGlyph::Info:
        drawInfo(painter, rect);
        break;
    case IconGlyph::Grid:
        drawGrid(painter, rect);
        break;
    case IconGlyph::Home:
        drawHome(painter, rect);
        break;
    case IconGlyph::Search:
        drawSearch(painter, rect);
        break;
    case IconGlyph::Filter:
        drawFilter(painter, rect);
        break;
    case IconGlyph::Logout:
        drawLogout(painter, rect);
        break;
    case IconGlyph::Moon:
        drawMoon(painter, rect);
        break;
    case IconGlyph::Sun:
        drawSun(painter, rect);
        break;
    case IconGlyph::Globe:
        drawGlobe(painter, rect);
        break;
    case IconGlyph::Trash:
        drawTrash(painter, rect);
        break;
    }

    return pixmap;
}

void IconHelper::drawMonitor(QPainter &painter, const QRectF &rect)
{
    painter.save();
    QRectF screen = rect.adjusted(rect.width() * 0.06, rect.height() * 0.06, -rect.width() * 0.06, -rect.height() * 0.35);
    painter.drawRoundedRect(screen, rect.width() * 0.08, rect.width() * 0.08);

    QPointF baseTop(screen.center().x(), screen.bottom());
    qreal stemHeight = rect.height() * 0.16;
    painter.drawLine(baseTop, QPointF(baseTop.x(), baseTop.y() + stemHeight));
    painter.drawLine(QPointF(rect.center().x() - rect.width() * 0.24, rect.bottom() - rect.height() * 0.05),
                     QPointF(rect.center().x() + rect.width() * 0.24, rect.bottom() - rect.height() * 0.05));
    painter.restore();
}

void IconHelper::drawSmartphone(QPainter &painter, const QRectF &rect)
{
    painter.save();
    QRectF body = rect.adjusted(rect.width() * 0.28, rect.height() * 0.08, -rect.width() * 0.28, -rect.height() * 0.08);
    painter.drawRoundedRect(body, rect.width() * 0.12, rect.width() * 0.12);

    QRectF notch(body.left() + body.width() * 0.25, body.top(), body.width() * 0.5, painter.pen().widthF());
    painter.drawLine(QPointF(notch.left(), notch.center().y()), QPointF(notch.right(), notch.center().y()));
    painter.drawPoint(QPointF(body.center().x(), body.bottom() - rect.height() * 0.04));
    painter.restore();
}

void IconHelper::drawSettings(QPainter &painter, const QRectF &rect)
{
    painter.save();
    QPointF center = rect.center();
    qreal radius = qMin(rect.width(), rect.height()) / 2.6;
    painter.drawEllipse(center, radius, radius);

    qreal inner = radius * 0.55;
    painter.drawEllipse(center, inner, inner);

    for (int i = 0; i < 6; ++i) {
        qreal angle = qDegreesToRadians(60.0 * i);
        QPointF start = center + QPointF(qCos(angle) * inner * 1.1, qSin(angle) * inner * 1.1);
        QPointF end = center + QPointF(qCos(angle) * radius * 1.3, qSin(angle) * radius * 1.3);
        painter.drawLine(start, end);
    }
    painter.restore();
}

void IconHelper::drawInfo(QPainter &painter, const QRectF &rect)
{
    painter.save();
    QPointF center = rect.center();
    qreal radius = qMin(rect.width(), rect.height()) / 2.4;
    painter.drawEllipse(center, radius, radius);
    painter.drawLine(QPointF(center.x(), center.y() - radius * 0.2), QPointF(center.x(), center.y() + radius * 0.55));
    painter.drawPoint(QPointF(center.x(), center.y() - radius * 0.55));
    painter.restore();
}

void IconHelper::drawGrid(QPainter &painter, const QRectF &rect)
{
    painter.save();
    qreal gap = rect.width() * 0.08;
    qreal cellW = (rect.width() - gap) / 2.0;
    qreal cellH = (rect.height() - gap) / 2.0;

    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 2; ++col) {
            QRectF cell(rect.left() + col * (cellW + gap), rect.top() + row * (cellH + gap), cellW, cellH);
            painter.drawRoundedRect(cell, cellW * 0.15, cellW * 0.15);
        }
    }
    painter.restore();
}

void IconHelper::drawHome(QPainter &painter, const QRectF &rect)
{
    painter.save();
    QPainterPath path;
    QPointF top(rect.center().x(), rect.top() + rect.height() * 0.2);
    QPointF left(rect.left() + rect.width() * 0.2, rect.top() + rect.height() * 0.45);
    QPointF right(rect.right() - rect.width() * 0.2, left.y());

    path.moveTo(top);
    path.lineTo(left);
    path.lineTo(left.x(), rect.bottom() - rect.height() * 0.1);
    path.lineTo(right.x(), rect.bottom() - rect.height() * 0.1);
    path.lineTo(right.x(), left.y());
    path.closeSubpath();

    painter.drawPath(path);
    painter.restore();
}

void IconHelper::drawSearch(QPainter &painter, const QRectF &rect)
{
    painter.save();
    QRectF circle = rect.adjusted(rect.width() * 0.1, rect.height() * 0.1, -rect.width() * 0.35, -rect.height() * 0.35);
    painter.drawEllipse(circle);
    painter.drawLine(circle.bottomRight(), QPointF(rect.right() - rect.width() * 0.08, rect.bottom() - rect.height() * 0.08));
    painter.restore();
}

void IconHelper::drawFilter(QPainter &painter, const QRectF &rect)
{
    painter.save();
    QPainterPath path;
    path.moveTo(rect.left(), rect.top() + rect.height() * 0.15);
    path.lineTo(rect.right(), rect.top() + rect.height() * 0.15);
    path.lineTo(rect.center().x() + rect.width() * 0.12, rect.center().y());
    path.lineTo(rect.center().x() + rect.width() * 0.04, rect.center().y());
    path.lineTo(rect.center().x() + rect.width() * 0.04, rect.bottom() - rect.height() * 0.1);
    path.lineTo(rect.center().x() - rect.width() * 0.04, rect.bottom() - rect.height() * 0.1);
    path.lineTo(rect.center().x() - rect.width() * 0.04, rect.center().y());
    path.lineTo(rect.center().x() - rect.width() * 0.12, rect.center().y());
    path.closeSubpath();
    painter.drawPath(path);
    painter.restore();
}

void IconHelper::drawLogout(QPainter &painter, const QRectF &rect)
{
    painter.save();
    QRectF body = rect.adjusted(rect.width() * 0.2, rect.height() * 0.2, -rect.width() * 0.45, -rect.height() * 0.2);
    painter.drawRoundedRect(body, rect.width() * 0.08, rect.width() * 0.08);

    QPointF mid(body.center().x(), rect.center().y());
    painter.drawLine(QPointF(body.right(), mid.y()), QPointF(rect.right() - rect.width() * 0.18, mid.y()));

    QPointF arrowTip(rect.right() - rect.width() * 0.1, mid.y());
    QPointF arrowTop(rect.right() - rect.width() * 0.2, mid.y() - rect.height() * 0.12);
    QPointF arrowBottom(rect.right() - rect.width() * 0.2, mid.y() + rect.height() * 0.12);
    painter.drawLine(QPointF(body.right(), mid.y()), arrowTip);
    painter.drawLine(arrowTop, arrowTip);
    painter.drawLine(arrowBottom, arrowTip);
    painter.restore();
}

void IconHelper::drawMoon(QPainter &painter, const QRectF &rect)
{
    painter.save();
    QColor strokeColor = painter.pen().color();
    QPainterPath moon;
    moon.addEllipse(rect.adjusted(rect.width() * 0.12, rect.height() * 0.12, -rect.width() * 0.12, -rect.height() * 0.12));
    QPainterPath cut;
    cut.addEllipse(rect.adjusted(rect.width() * 0.32, rect.height() * 0.04, -rect.width() * 0.02, -rect.height() * 0.04));
    painter.setPen(Qt::NoPen);
    painter.setBrush(strokeColor);
    painter.drawPath(moon.subtracted(cut));
    painter.setBrush(Qt::NoBrush);
    painter.restore();
}

void IconHelper::drawSun(QPainter &painter, const QRectF &rect)
{
    painter.save();
    QPointF center = rect.center();
    qreal radius = qMin(rect.width(), rect.height()) / 4.0;
    painter.drawEllipse(center, radius, radius);

    for (int i = 0; i < 8; ++i) {
        qreal angle = qDegreesToRadians(45.0 * i);
        QPointF start = center + QPointF(qCos(angle) * radius * 1.6, qSin(angle) * radius * 1.6);
        QPointF end = center + QPointF(qCos(angle) * radius * 2.4, qSin(angle) * radius * 2.4);
        painter.drawLine(start, end);
    }
    painter.restore();
}

void IconHelper::drawGlobe(QPainter &painter, const QRectF &rect)
{
    painter.save();
    QPointF center = rect.center();
    qreal radius = qMin(rect.width(), rect.height()) / 2.4;
    painter.drawEllipse(center, radius, radius);

    painter.drawEllipse(center, radius * 0.6, radius * 0.6);
    painter.drawLine(QPointF(center.x() - radius, center.y()), QPointF(center.x() + radius, center.y()));
    painter.drawArc(QRectF(center.x() - radius, center.y() - radius, radius * 2, radius * 2), 30 * 16, 120 * 16);
    painter.drawArc(QRectF(center.x() - radius, center.y() - radius, radius * 2, radius * 2), 210 * 16, 120 * 16);
    painter.restore();
}

void IconHelper::drawTrash(QPainter &painter, const QRectF &rect)
{
    painter.save();
    QRectF lid = rect.adjusted(rect.width() * 0.2, rect.height() * 0.1, -rect.width() * 0.2, -rect.height() * 0.72);
    painter.drawLine(QPointF(lid.left(), lid.bottom()), QPointF(lid.right(), lid.bottom()));
    painter.drawLine(QPointF(rect.center().x() - rect.width() * 0.12, lid.top()), QPointF(rect.center().x() + rect.width() * 0.12, lid.top()));

    QRectF body = rect.adjusted(rect.width() * 0.25, rect.height() * 0.18, -rect.width() * 0.25, -rect.height() * 0.08);
    painter.drawRoundedRect(body, rect.width() * 0.08, rect.width() * 0.08);

    painter.drawLine(QPointF(body.center().x(), body.top() + body.height() * 0.18), QPointF(body.center().x(), body.bottom() - body.height() * 0.18));
    painter.drawLine(QPointF(body.left() + body.width() * 0.25, body.top() + body.height() * 0.18),
                     QPointF(body.left() + body.width() * 0.25, body.bottom() - body.height() * 0.18));
    painter.drawLine(QPointF(body.right() - body.width() * 0.25, body.top() + body.height() * 0.18),
                     QPointF(body.right() - body.width() * 0.25, body.bottom() - body.height() * 0.18));
    painter.restore();
}
