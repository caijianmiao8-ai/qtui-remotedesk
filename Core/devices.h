#ifndef DEVICES_H
#define DEVICES_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>  // 添加这行
#include <QLabel>                     // 确保包含 QLabel
#include <QHBoxLayout>                // 确保包含布局头文件
#include <QVBoxLayout>

namespace Ui {
class Devices;
}

class Devices : public QWidget
{
    Q_OBJECT

public:
    explicit Devices(QWidget *parent = nullptr);
    ~Devices();

private:
    Ui::Devices *ui;

    void initUi();

    void setupHomeLayout();

    void setupHomeHeader();

    void setupWidget2();
    void setupIconLabel();
    void setupTipLabel();

    void setupWidget3();

    // 新增方法
    void setupDeviceCards();
    QWidget* createDeviceCard(const QString& deviceName, const QString& iconPath = ":/qss/icon/logo_04.png");

};

#endif // DEVICES_H
