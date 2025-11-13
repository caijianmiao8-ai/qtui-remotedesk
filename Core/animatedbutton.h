#ifndef ANIMATEDBUTTON_H
#define ANIMATEDBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QColor>

/**
 * @brief AnimatedButton - 实现 React 的 transition-all duration-200 效果
 *
 * React 设计: transition-all duration-200 ease-in-out
 * Qt 实现: QPropertyAnimation 实现平滑的 hover 过渡动画
 */
class AnimatedButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(qreal hoverProgress READ hoverProgress WRITE setHoverProgress)

public:
    explicit AnimatedButton(const QString &text = QString(), QWidget *parent = nullptr);

    // 设置普通和hover状态的背景颜色
    void setColors(const QColor &normal, const QColor &hover);

    // 设置动画时长（默认200ms，对应 React 的 duration-200）
    void setAnimationDuration(int ms);

    qreal hoverProgress() const { return m_hoverProgress; }
    void setHoverProgress(qreal progress);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPropertyAnimation *m_hoverAnimation;
    qreal m_hoverProgress;  // 0.0 = normal, 1.0 = hover
    QColor m_normalColor;
    QColor m_hoverColor;
    int m_animationDuration;
};

#endif // ANIMATEDBUTTON_H
