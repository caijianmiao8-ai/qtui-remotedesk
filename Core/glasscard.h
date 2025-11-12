#ifndef GLASSCARD_H
#define GLASSCARD_H

#include <QWidget>
#include <QString>

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

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    bool m_darkMode;
};

#endif // GLASSCARD_H
