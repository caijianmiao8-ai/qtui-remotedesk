#ifndef DEVICES_H
#define DEVICES_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QVector>
#include <QGraphicsDropShadowEffect>
#include <QColor>

namespace Ui {
class Devices;
}

struct ControllerInfo {
    QString name;
    QString os;
    bool online;
    QString lastActive;
    QString battery;
};

struct DeviceInfo {
    QString name;
    QString os;
    QString ip;
    QString lastSeen;
    QString networkMode;
    QString latency;
    bool online;
};

class Devices : public QWidget
{
    Q_OBJECT

public:
    explicit Devices(QWidget *parent = nullptr);
    ~Devices();

private:
    Ui::Devices *ui;

    void initUi();
    void setupScrollArea();

    QWidget *createHeaderSection();
    QFrame *createPairingHintCard();
    QWidget *createControllersSection();
    QWidget *createRegisteredDevicesSection();

    QFrame *createGlassCard(const QString &objectName) const;
    QGraphicsDropShadowEffect *createShadow(QObject *parent, qreal blur = 44.0, qreal yOffset = 16.0) const;
    QLabel *createTitleLabel(const QString &text, int size, bool bold = true) const;
    QLabel *createSecondaryLabel(const QString &text, int size = 14, qreal opacity = 0.62) const;
    QWidget *createStatusBadge(bool online) const;
    QFrame *buildControllerCard(const ControllerInfo &info) const;
    QFrame *buildDeviceCard(const DeviceInfo &info) const;
};

#endif // DEVICES_H
