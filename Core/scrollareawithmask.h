#ifndef SCROLLAREAWITHMASK_H
#define SCROLLAREAWITHMASK_H

#include <QScrollArea>
#include <QWidget>
#include <QPainter>

/**
 * @brief ScrollAreaWithMask - 实现 React 的 ScrollArea gradient masks 效果
 *
 * React 设计: 在滚动区域顶部和底部添加渐变遮罩
 * ```jsx
 * <div className="pointer-events-none absolute inset-x-0 top-0 h-6
 *               bg-gradient-to-b from-black/5 to-transparent" />
 * <div className="pointer-events-none absolute inset-x-0 bottom-0 h-6
 *               bg-gradient-to-t from-black/5 to-transparent" />
 * ```
 *
 * Qt 实现: 在QScrollArea上叠加渐变遮罩层
 */
class ScrollAreaWithMask : public QScrollArea
{
    Q_OBJECT

public:
    explicit ScrollAreaWithMask(QWidget *parent = nullptr);

    // 设置渐变遮罩的高度（默认24px，对应 React 的 h-6）
    void setMaskHeight(int height);

    // 启用/禁用顶部/底部遮罩
    void setTopMaskEnabled(bool enabled);
    void setBottomMaskEnabled(bool enabled);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_maskHeight;
    bool m_topMaskEnabled;
    bool m_bottomMaskEnabled;

    void paintGradientMask(QPainter &painter);
};

#endif // SCROLLAREAWITHMASK_H
