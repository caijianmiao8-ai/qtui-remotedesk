#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>  // 添加这行
#include <QLabel>                     // 确保包含 QLabel
#include <QHBoxLayout>                // 确保包含布局头文件
#include <QVBoxLayout>

namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();

private:
    Ui::Home *ui;

    void initUi();

    void setupHomeLayout();

    void setupHomeHeader();

    void setupWidget2();
    void setupIconLabel();
    void setupTipLabel();

    void setupWidget3();
    void setupWidget3Layout();
    void setupWidget3Title();
    void setupWidget3InfoGrid();
    void setupInfoItem(QGridLayout *gridLayout, int row, int col,
                             QLabel *titleLabel, QLabel *valueLabel,
                             const QString &title, const QString &value, int verticalSpacing);
    void setupNetworkStatusItem(QGridLayout *gridLayout, int row, int col, QLabel *titleLabel, int verticalSpacing);

    void setupWidget4();
    void setupWidget4Layout();
    void setupWidget4Title();
    void setupWidget4QuickActions();
    QWidget* createQuickActionItem(const QString &title, const QString &description, const QString &iconPath);

};

#endif // HOME_H
