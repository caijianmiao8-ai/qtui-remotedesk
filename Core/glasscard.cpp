#include "glasscard.h"
#include <QPainter>
#include <QPainterPath>

GlassCard::GlassCard(QWidget *parent, bool darkMode)
    : QWidget(parent), m_darkMode(darkMode)
{
    setStyleSheet(getCardStyle(darkMode));
}

void GlassCard::setDarkMode(bool darkMode)
{
    m_darkMode = darkMode;
    setStyleSheet(getCardStyle(darkMode));
    update();
}

QString GlassCard::getCardStyle(bool darkMode)
{
    if (darkMode) {
        return
            "QWidget {"
            "    background: rgba(255, 255, 255, 0.05);"
            "    border: 1px solid rgba(255, 255, 255, 0.1);"
            "    border-radius: 20px;"
            "}";
    } else {
        return
            "QWidget {"
            "    background: rgba(255, 255, 255, 0.7);"
            "    border: 1px solid rgba(0, 0, 0, 0.05);"
            "    border-radius: 20px;"
            "}";
    }
}

QString GlassCard::getButtonStyle(bool darkMode)
{
    if (darkMode) {
        return
            "QPushButton {"
            "    background: rgba(255, 255, 255, 0.04);"
            "    border: 1px solid rgba(255, 255, 255, 0.1);"
            "    border-radius: 14px;"
            "    color: #f1f5f9;"
            "    padding: 12px 16px;"
            "    font-size: 14px;"
            "    font-weight: 500;"
            "}"
            "QPushButton:hover {"
            "    background: rgba(255, 255, 255, 0.07);"
            "}";
    } else {
        return
            "QPushButton {"
            "    background: rgba(255, 255, 255, 0.6);"
            "    border: 1px solid rgba(0, 0, 0, 0.05);"
            "    border-radius: 14px;"
            "    color: #1e293b;"
            "    padding: 12px 16px;"
            "    font-size: 14px;"
            "    font-weight: 500;"
            "}"
            "QPushButton:hover {"
            "    background: rgba(0, 0, 0, 0.03);"
            "}";
    }
}

QString GlassCard::getAccentButtonStyle(bool darkMode)
{
    return
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "        stop:0 #0A84FF, stop:1 #0051C7);"
        "    border: none;"
        "    border-radius: 14px;"
        "    color: white;"
        "    padding: 12px 24px;"
        "    font-size: 14px;"
        "    font-weight: 600;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "        stop:0 #1A94FF, stop:1 #1061D7);"
        "}";
}

void GlassCard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制毛玻璃效果的背景
    QPainterPath path;
    path.addRoundedRect(rect(), 20, 20);

    painter.fillPath(path, Qt::transparent);

    QWidget::paintEvent(event);
}
