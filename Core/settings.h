#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>  // 添加这行
#include <QLabel>                     // 确保包含 QLabel
#include <QHBoxLayout>                // 确保包含布局头文件
#include <QVBoxLayout>
#include <QCheckBox>
#include <QSettings>
#include <QDebug>
#include "toggleswitch.h"

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;
    void initUi();

    void setupWidget_1();
    void setupWidget2();
    void setupWidget2Layout();
    void setupSettingsItems();
    QWidget* createSettingItem(const QString &title, const QString &description, const QString &settingKey);
    QWidget* createSeparator();
    ToggleSwitch* createToggleSwitch(const QString &settingKey);
    void onToggleSwitchChanged(bool checked);
    void saveSetting(const QString &key, bool value);
    bool loadSetting(const QString &key, bool defaultValue);
    void applySetting(const QString &key, bool value);
    void applyLaunchAtLogin(bool enable);
    void applyLowLatencyMode(bool enable);
    void applyAllowLanDirect(bool enable);

};

#endif // SETTINGS_H
