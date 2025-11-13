#include "animatedbutton.h"
#include <QPainter>
#include <QPainterPath>
#include <QEvent>

AnimatedButton::AnimatedButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent),
      m_hoverProgress(0.0),
      m_normalColor(255, 255, 255, 153),   // rgba(255,255,255,0.6)
      m_hoverColor(0, 0, 0, 8),             // rgba(0,0,0,0.03)
      m_animationDuration(200)              // React: duration-200 = 200ms
{
    // 创建hover动画
    m_hoverAnimation = new QPropertyAnimation(this, "hoverProgress");
    m_hoverAnimation->setDuration(m_animationDuration);
    m_hoverAnimation->setEasingCurve(QEasingCurve::InOutCubic);  // ease-in-out

    // 启用鼠标追踪以检测enter/leave事件
    setMouseTracking(true);

    // 设置cursor为pointer（对应 cursor: pointer）
    setCursor(Qt::PointingHandCursor);
}

void AnimatedButton::setColors(const QColor &normal, const QColor &hover)
{
    m_normalColor = normal;
    m_hoverColor = hover;
    update();
}

void AnimatedButton::setAnimationDuration(int ms)
{
    m_animationDuration = ms;
    m_hoverAnimation->setDuration(ms);
}

void AnimatedButton::setHoverProgress(qreal progress)
{
    m_hoverProgress = progress;
    update();  // 触发重绘
}

void AnimatedButton::enterEvent(QEvent *event)
{
    QPushButton::enterEvent(event);

    // 动画到hover状态
    m_hoverAnimation->stop();
    m_hoverAnimation->setStartValue(m_hoverProgress);
    m_hoverAnimation->setEndValue(1.0);
    m_hoverAnimation->start();
}

void AnimatedButton::leaveEvent(QEvent *event)
{
    QPushButton::leaveEvent(event);

    // 动画回到normal状态
    m_hoverAnimation->stop();
    m_hoverAnimation->setStartValue(m_hoverProgress);
    m_hoverAnimation->setEndValue(0.0);
    m_hoverAnimation->start();
}

void AnimatedButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 计算当前颜色（在normal和hover之间插值）
    QColor currentBg;
    currentBg.setRedF(m_normalColor.redF() + (m_hoverColor.redF() - m_normalColor.redF()) * m_hoverProgress);
    currentBg.setGreenF(m_normalColor.greenF() + (m_hoverColor.greenF() - m_normalColor.greenF()) * m_hoverProgress);
    currentBg.setBlueF(m_normalColor.blueF() + (m_hoverColor.blueF() - m_normalColor.blueF()) * m_hoverProgress);
    currentBg.setAlphaF(m_normalColor.alphaF() + (m_hoverColor.alphaF() - m_normalColor.alphaF()) * m_hoverProgress);

    // 绘制圆角矩形背景
    QPainterPath path;
    path.addRoundedRect(rect(), 14, 14);  // border-radius: 14px
    painter.fillPath(path, currentBg);

    // 绘制边框
    QPen pen(QColor(0, 0, 0, 13));  // rgba(0,0,0,0.05)
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawPath(path);

    // 绘制文本
    painter.setPen(QColor(30, 41, 59));  // text-slate-900 = #1e293b
    QFont font = painter.font();
    font.setPixelSize(14);
    font.setWeight(QFont::Medium);  // font-weight: 500
    font.setFamily("Segoe UI");
    painter.setFont(font);
    painter.drawText(rect(), Qt::AlignCenter, text());
}
