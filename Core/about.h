#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>
#include <QString>

namespace Ui {
class About;
}

class About : public QWidget
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();

private:
    Ui::About *ui;

    // 主布局函数
    void buildLayout();

    // 区域创建函数
    QWidget* createHeader();
    QWidget* createAppInfoCard();
    QWidget* createSystemInfoCard();
    QWidget* createLinksCard();
    QWidget* createInfoRow(const QString &label, const QString &value, bool mono = false);
    QWidget* createLinkButton(const QString &text, const QString &url);

    // 辅助函数
    QString getAppVersion();
    QString getBuildDate();
    QString getOSVersion();
    QString getQtVersion();
    QString getArchitecture();
    QString getBuildVersion();
};

#endif // ABOUT_H
