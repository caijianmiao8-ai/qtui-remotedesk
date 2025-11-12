#include "ToggleSwitch.h"
#include <QPainter>
#include <QMouseEvent>

ToggleSwitch::ToggleSwitch(QWidget *parent)
    : QWidget(parent), m_checked(false), m_sliderPosition(0)
{
    setFixedSize(48, 26);

    // 创建动画
    m_animation = new QPropertyAnimation(this, "sliderPosition");
    m_animation->setDuration(150); // 动画时长150毫秒
    m_animation->setEasingCurve(QEasingCurve::OutCubic);

    // 初始化滑块位置
    m_sliderPosition = m_checked ? travelDistance() : 0;
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
        m_animation->setEndValue(checked ? travelDistance() : 0);
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
    return QSize(48, 26);
}

qreal ToggleSwitch::travelDistance() const
{
    int gap = 3;
    int sliderSize = height() - 2 * gap;
    int travel = width() - sliderSize - 2 * gap;
    return qMax(0, travel);
}

void ToggleSwitch::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制背景椭圆
    QRect backgroundRect(0, 0, width(), height());
    QLinearGradient trackGradient(backgroundRect.topLeft(), backgroundRect.bottomRight());
    if (m_checked) {
        trackGradient.setColorAt(0.0, QColor(40, 146, 255, 240));
        trackGradient.setColorAt(1.0, QColor(10, 132, 255, 220));
    } else {
        trackGradient.setColorAt(0.0, QColor(245, 247, 250));
        trackGradient.setColorAt(1.0, QColor(225, 228, 235));
    }
    painter.setBrush(trackGradient);
    painter.setPen(QPen(m_checked ? QColor(10, 132, 255, 180) : QColor(209, 213, 219), 1.0));
    painter.drawRoundedRect(backgroundRect, 13, 13);

    // 间隙设置
    int gap = 3;  // 间隙大小，可以调整这个值
    int sliderSize = height() - 2 * gap;  // 滑块大小根据间隙计算
    qreal travel = travelDistance();

    // 计算滑块位置
    int minX = gap;
    int sliderX = minX;
    if (travel > 0) {
        qreal normalizedPosition = m_sliderPosition / travel;
        sliderX = minX + normalizedPosition * travel;
    }
    int sliderY = gap;

    // 绘制滑块
    QRect sliderRect(sliderX, sliderY, sliderSize, sliderSize);

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_checked ? QColor(10, 132, 255, 70) : QColor(15, 23, 42, 25));
    QRect shadowRect = sliderRect.adjusted(-2, 2, 2, 6);
    painter.drawEllipse(shadowRect);
    painter.restore();

    QRadialGradient knobGradient(sliderRect.center(), sliderRect.width() / 2.0);
    knobGradient.setColorAt(0.0, QColor(255, 255, 255, 255));
    knobGradient.setColorAt(1.0, QColor(235, 238, 245, 255));
    painter.setBrush(knobGradient);
    painter.setPen(QPen(QColor(255, 255, 255, 220), 0.8));
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
