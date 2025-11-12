#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QString>

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

    // 主布局函数
    void buildLayout();

    // 区域创建函数
    QWidget* createHeader();
    QWidget* createSettingsCard();
    QWidget* createSettingItem(const QString &title, const QString &description, const QString &settingKey);
    QWidget* createSeparator();

    // 设置管理
    void onToggleSwitchChanged(bool checked);
    void saveSetting(const QString &key, bool value);
    bool loadSetting(const QString &key, bool defaultValue);
    void applySetting(const QString &key, bool value);
};

#endif // SETTINGS_H
