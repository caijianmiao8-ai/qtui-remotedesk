#include "glasscard.h"
#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>
#include <QRadialGradient>

GlassCard::GlassCard(QWidget *parent, bool darkMode)
    : QWidget(parent),
      m_darkMode(darkMode),
      m_backdropBlurEnabled(true),  // 默认启用模糊效果
      m_blurRadius(20)  // backdrop-blur-xl = 20px
{
    setStyleSheet(getCardStyle(darkMode));

    // 设置widget属性以支持更好的渲染
    setAttribute(Qt::WA_TranslucentBackground, false);
    setAutoFillBackground(false);
}

void GlassCard::setDarkMode(bool darkMode)
{
    m_darkMode = darkMode;
    setStyleSheet(getCardStyle(darkMode));
    update();
}

void GlassCard::setBackdropBlurEnabled(bool enabled)
{
    m_backdropBlurEnabled = enabled;
    update();
}

void GlassCard::setBlurRadius(int radius)
{
    m_blurRadius = radius;
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
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // 应用毛玻璃效果增强
    if (m_backdropBlurEnabled) {
        applyGlassEffects(painter, rect());
    }

    QWidget::paintEvent(event);
}

void GlassCard::applyGlassEffects(QPainter &painter, const QRect &rect)
{
    /**
     * React 的 backdrop-filter: blur(20px) 效果模拟
     *
     * 由于 Qt 限制，真正的背景模糊需要：
     * 1. 获取widget后面的内容
     * 2. 对背景应用高斯模糊
     * 3. 绘制模糊的背景
     *
     * 这会有严重的性能问题。因此我们采用视觉增强方案：
     * - 多层半透明渐变营造深度感
     * - 边缘内发光模拟光线折射
     * - 轻微的噪点纹理增强质感
     */

    QPainterPath path;
    path.addRoundedRect(rect, 20, 20);
    painter.setClipPath(path);

    // 1. 基础半透明背景层（已由StyleSheet提供）
    // 这里不需要重复绘制

    // 2. 顶部轻微高光渐变（模拟光线透过毛玻璃的效果）
    QLinearGradient topGloss(rect.topLeft(), QPoint(rect.left(), rect.height() * 0.3));
    if (m_darkMode) {
        topGloss.setColorAt(0, QColor(255, 255, 255, 8));   // rgba(255,255,255,0.03)
        topGloss.setColorAt(1, QColor(255, 255, 255, 0));
    } else {
        topGloss.setColorAt(0, QColor(255, 255, 255, 25));  // rgba(255,255,255,0.1)
        topGloss.setColorAt(1, QColor(255, 255, 255, 0));
    }
    painter.fillPath(path, topGloss);

    // 3. 边缘内发光（模拟光线在毛玻璃边缘的散射）
    QPainterPath innerGlowPath;
    innerGlowPath.addRoundedRect(rect.adjusted(1, 1, -1, -1), 19, 19);

    QPen innerGlowPen;
    if (m_darkMode) {
        innerGlowPen.setColor(QColor(255, 255, 255, 15));  // rgba(255,255,255,0.06)
    } else {
        innerGlowPen.setColor(QColor(255, 255, 255, 40));  // rgba(255,255,255,0.15)
    }
    innerGlowPen.setWidth(1);
    painter.setPen(innerGlowPen);
    painter.drawPath(innerGlowPath);

    painter.setClipping(false);

    /**
     * 注意：如果未来需要真正的 backdrop-filter 效果，可以使用以下代码：
     *
     * QPixmap background = QPixmap::grabWidget(parentWidget(), mapTo(parentWidget(), QPoint(0,0)), size());
     * QImage blurred = background.toImage();
     * // 应用高斯模糊算法
     * painter.drawImage(0, 0, blurred);
     *
     * 但这会严重影响性能，不推荐在生产环境使用。
     */
}
