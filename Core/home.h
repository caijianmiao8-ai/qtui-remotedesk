#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QString>

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
    QWidget* m_networkIndicator;  // 网络状态指示点（用于pulse动画）

    // 主布局函数
    void buildLayout();

    // 区域创建函数
    QWidget* createHeader();
    QWidget* createPairingHintCard();
    QWidget* createStatsGrid();
    QWidget* createStatCard();
    QWidget* createMachineInfoCard();
    QWidget* createInfoItem(const QString &labelText, const QString &valueText, bool mono);
    QWidget* createNetworkStatusItem();
    QWidget* createQuickActionsCard();
    QWidget* createActionButton(const QString &titleText, const QString &descText, const QString &icon);
};

#endif // HOME_H
