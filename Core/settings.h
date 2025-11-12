#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QSettings>

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

private slots:
    void onToggleSwitchChanged(bool checked);

private:
    Ui::Settings *ui;

    void initUi();
    void setupScrollArea();
    QWidget *createHeader();
    QFrame *createSettingsCard();
    QWidget *createSettingRow(const QString &title, const QString &description, const QString &settingKey, bool defaultValue = false);
    QWidget *createSeparator() const;

    void saveSetting(const QString &key, bool value);
    bool loadSetting(const QString &key, bool defaultValue = false);
    void applySetting(const QString &key, bool value);
    void applyLaunchAtLogin(bool enable);
    void applyLowLatencyMode(bool enable);
    void applyAllowLanDirect(bool enable);
};

#endif // SETTINGS_H
