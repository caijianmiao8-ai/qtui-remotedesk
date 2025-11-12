#ifndef DEVICES_H
#define DEVICES_H

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class Devices;
}

struct DeviceInfo;

class Devices : public QWidget
{
    Q_OBJECT

public:
    explicit Devices(QWidget *parent = nullptr);
    ~Devices();

private:
    Ui::Devices *ui;

    // 主布局函数
    void buildLayout();

    // 区域创建函数
    QWidget* createHeaderSection();
    QPushButton* createToolButton(const QString &text);
    QWidget* createPairingHintCard();
    QWidget* createControllersSection();
    QWidget* createRegisteredDevicesSection();

    // 卡片创建函数
    QWidget* createControllerCard(const DeviceInfo &device);
    QWidget* createDeviceCard(const DeviceInfo &device);

    // 辅助函数
    QLabel* createStatusBadge(bool online);
    QWidget* createInfoRow(const QString &label, const QString &value, const QString &valueColor = "");
    QString getNetworkColor(const QString &network);
};

#endif // DEVICES_H
