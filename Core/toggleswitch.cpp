#include "ToggleSwitch.h"
#include <QPainter>
#include <QMouseEvent>

ToggleSwitch::ToggleSwitch(QWidget *parent)
    : QWidget(parent), m_checked(false), m_sliderPosition(0), m_hovered(false)
{
    setFixedSize(44, 24);  // React: w-11 h-6 = 44x24px
    setCursor(Qt::PointingHandCursor);  // Apple风格：手型光标
    setMouseTracking(true);  // 启用鼠标追踪以检测hover

    // React: transition duration 200ms
    m_animation = new QPropertyAnimation(this, "sliderPosition");
    m_animation->setDuration(200);  // React默认transition时长
    m_animation->setEasingCurve(QEasingCurve::OutCubic);

    // 初始化滑块位置
    m_sliderPosition = m_checked ? 20 : 0;
}

bool ToggleSwitch::isChecked() const
{
    return m_checked;
}

void ToggleSwitch::setChecked(bool checked)
{
    if (m_checked != checked) {
        m_checked = checked;

        // 启动动画
        m_animation->stop();
        m_animation->setStartValue(m_sliderPosition);
        m_animation->setEndValue(checked ? 20 : 0);
        m_animation->start();

        update();
        emit toggled(m_checked);
    }
}

qreal ToggleSwitch::sliderPosition() const
{
    return m_sliderPosition;
}

void ToggleSwitch::setSliderPosition(qreal position)
{
    if (m_sliderPosition != position) {
        m_sliderPosition = position;
        update();
    }
}

QSize ToggleSwitch::sizeHint() const
{
    return QSize(44, 24);
}

void ToggleSwitch::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // React背景颜色：
    // 开启: bg-[rgba(10,132,255,0.6)]
    // 关闭: bg-slate-500/30 = rgba(100,116,139,0.3)
    // Hover时背景色轻微加深
    QColor backgroundColor;
    if (m_checked) {
        if (m_hovered) {
            backgroundColor = QColor(10, 132, 255, 178);  // hover: 0.7 * 255 = 178
        } else {
            backgroundColor = QColor(10, 132, 255, 153);  // 0.6 * 255 = 153
        }
    } else {
        if (m_hovered) {
            backgroundColor = QColor(100, 116, 139, 102);  // hover: 0.4 * 255 = 102
        } else {
            backgroundColor = QColor(100, 116, 139, 77);   // 0.3 * 255 = 77
        }
    }

    // 绘制背景椭圆 - React: rounded-full
    QRect backgroundRect(0, 0, width(), height());
    painter.setBrush(backgroundColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(backgroundRect, 12, 12);

    // React滑块尺寸: w-4 h-4 = 16x16px
    // React间距: px-1 = 4px
    int gap = 4;  // px-1 = 4px
    int sliderSize = 16;  // w-4 h-4 = 16px

    // 计算滑块位置
    int minX = gap;
    int maxX = width() - sliderSize - gap;

    // 将0-20的动画位置映射到实际像素位置
    qreal normalizedPosition = m_sliderPosition / 20.0;
    int sliderX = minX + normalizedPosition * (maxX - minX);
    int sliderY = gap;

    // 绘制滑块 - React: bg-white shadow
    QRect sliderRect(sliderX, sliderY, sliderSize, sliderSize);

    // 纯白色滑块，添加阴影
    painter.setBrush(QColor(255, 255, 255));
    painter.setPen(Qt::NoPen);

    // 简单的阴影效果（Qt无法像CSS那样做box-shadow，用描边模拟）
    painter.save();
    painter.setPen(QPen(QColor(0, 0, 0, 20), 1));
    painter.drawEllipse(sliderRect);
    painter.restore();

    painter.setBrush(QColor(255, 255, 255));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(sliderRect);
}

void ToggleSwitch::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setChecked(!m_checked);
        event->accept();
    } else {
        QWidget::mousePressEvent(event);
    }
}

void ToggleSwitch::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_hovered = true;
    update();
}

void ToggleSwitch::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_hovered = false;
    update();
}
