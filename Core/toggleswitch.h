#ifndef TOGGLESWITCH_H
#define TOGGLESWITCH_H

#include <QWidget>
#include <QPropertyAnimation>

class ToggleSwitch : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked NOTIFY toggled)
    Q_PROPERTY(qreal sliderPosition READ sliderPosition WRITE setSliderPosition) // 添加这一行

public:
    explicit ToggleSwitch(QWidget *parent = nullptr);

    bool isChecked() const;
    void setChecked(bool checked);

    qreal sliderPosition() const; // 添加getter
    void setSliderPosition(qreal position); // 添加setter

    QSize sizeHint() const override;

signals:
    void toggled(bool checked);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    bool m_checked;
    bool m_hovered;
    QPropertyAnimation *m_animation;
    qreal m_sliderPosition;
};

#endif // TOGGLESWITCH_H
