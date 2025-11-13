#ifndef GLASSCARD_H
#define GLASSCARD_H

#include <QWidget>
#include <QString>
#include <QGraphicsBlurEffect>

/**
 * @brief GlassCard - 实现 React 的 backdrop-filter 毛玻璃效果
 *
 * React 设计: backdrop-filter: blur(20px) + rgba background
 * Qt 实现: QGraphicsBlurEffect + 半透明背景 + 视觉增强
 */
class GlassCard : public QWidget
{
    Q_OBJECT

public:
    explicit GlassCard(QWidget *parent = nullptr, bool darkMode = false);

    // 样式生成函数
    static QString getCardStyle(bool darkMode = false);
    static QString getButtonStyle(bool darkMode = false);
    static QString getAccentButtonStyle(bool darkMode = false);

    void setDarkMode(bool darkMode);

    // 启用/禁用backdrop-filter模糊效果（默认启用，但性能开销较大）
    void setBackdropBlurEnabled(bool enabled);
    bool isBackdropBlurEnabled() const { return m_backdropBlurEnabled; }

    // 设置模糊半径（默认20px，对应 backdrop-blur-xl）
    void setBlurRadius(int radius);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    bool m_darkMode;
    bool m_backdropBlurEnabled;
    int m_blurRadius;

    // 应用视觉增强效果（内发光、渐变等）来模拟毛玻璃质感
    void applyGlassEffects(QPainter &painter, const QRect &rect);
};

#endif // GLASSCARD_H
