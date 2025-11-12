#ifndef HOME_H
#define HOME_H

#include <QWidget>

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

    // 主要布局函数
    void buildCompleteLayout();

    // 各部分创建函数
    QWidget* createHeaderSection();
    QWidget* createTipCard();
    QWidget* createStatsSection();
    QWidget* createMachineInfoCard();
    QWidget* createInfoItem(const QString &label, const QString &value);
    QWidget* createNetworkStatusItem();
    QWidget* createQuickActionsCard();
    QWidget* createActionButton(const QString &title, const QString &description, const QString &icon);
};

#endif // HOME_H
