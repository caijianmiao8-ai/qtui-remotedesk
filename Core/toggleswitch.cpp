#include "ToggleSwitch.h"
#include <QPainter>
#include <QMouseEvent>

ToggleSwitch::ToggleSwitch(QWidget *parent)
    : QWidget(parent), m_checked(false), m_sliderPosition(0)
{
    setFixedSize(44, 24);

    // 创建动画
    m_animation = new QPropertyAnimation(this, "sliderPosition");
    m_animation->setDuration(150); // 动画时长150毫秒
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

        update(); // 重绘
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
        update(); // 重绘
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

    // 绘制背景椭圆
    QRect backgroundRect(0, 0, width(), height());
    QColor backgroundColor = m_checked ? QColor("#2196F3") : QColor("#e5e5e5");
    painter.setBrush(backgroundColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(backgroundRect, 12, 12);

    // 间隙设置
    int gap = 3;  // 间隙大小，可以调整这个值
    int sliderSize = height() - 2 * gap;  // 滑块大小根据间隙计算

    // 计算滑块位置
    int minX = gap;
    int maxX = width() - sliderSize - gap;

    // 将0-20的动画位置映射到实际像素位置
    qreal normalizedPosition = m_sliderPosition / 20.0;
    int sliderX = minX + normalizedPosition * (maxX - minX);
    int sliderY = gap;

    // 绘制滑块
    QRect sliderRect(sliderX, sliderY, sliderSize, sliderSize);

    // 为滑块添加轻微的阴影效果，增强立体感
    QLinearGradient gradient(sliderRect.topLeft(), sliderRect.bottomRight());
    gradient.setColorAt(0, QColor(255, 255, 255));
    gradient.setColorAt(1, QColor(245, 245, 245));
    painter.setBrush(gradient);

    // 添加轻微的边框
    painter.setPen(QPen(QColor(220, 220, 220), 0.5));
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
