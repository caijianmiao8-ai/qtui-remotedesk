#ifndef ICONHELPER_H
#define ICONHELPER_H

#include <QPixmap>
#include <QColor>
#include <QSize>

class QPainter;
class QRectF;

enum class IconGlyph {
    Monitor,
    Smartphone,
    Settings,
    Info,
    Grid,
    Home,
    Search,
    Filter,
    Logout,
    Moon,
    Sun,
    Globe,
    Trash
};

class IconHelper
{
public:
    static QPixmap draw(IconGlyph glyph, const QSize &size, const QColor &color = QColor(15, 23, 42, 220));

private:
    static void drawMonitor(QPainter &painter, const QRectF &rect);
    static void drawSmartphone(QPainter &painter, const QRectF &rect);
    static void drawSettings(QPainter &painter, const QRectF &rect);
    static void drawInfo(QPainter &painter, const QRectF &rect);
    static void drawGrid(QPainter &painter, const QRectF &rect);
    static void drawHome(QPainter &painter, const QRectF &rect);
    static void drawSearch(QPainter &painter, const QRectF &rect);
    static void drawFilter(QPainter &painter, const QRectF &rect);
    static void drawLogout(QPainter &painter, const QRectF &rect);
    static void drawMoon(QPainter &painter, const QRectF &rect);
    static void drawSun(QPainter &painter, const QRectF &rect);
    static void drawGlobe(QPainter &painter, const QRectF &rect);
    static void drawTrash(QPainter &painter, const QRectF &rect);
};

#endif // ICONHELPER_H
