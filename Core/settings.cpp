#include "settings.h"
#include "ui_settings.h"
#include "toggleswitch.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QSettings>
#include <QDebug>

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    buildLayout();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::buildLayout()
{
    // 清除现有布局
    if (ui->widget->layout()) {
        QLayout *oldLayout = ui->widget->layout();
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }

    // 创建主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(ui->widget);
    mainLayout->setContentsMargins(32, 32, 32, 32);  // p-8 = 32px
    mainLayout->setSpacing(0);

    // 1. 标题区
    mainLayout->addWidget(createHeader());
    mainLayout->addSpacing(32);  // mb-8 = 32px

    // 2. 设置卡片
    mainLayout->addWidget(createSettingsCard());

    // 添加弹性空间
    mainLayout->addStretch(1);
}

QWidget* Settings::createHeader()
{
    QWidget *header = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(header);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(8);  // mb-2 = 8px

    // 主标题: "Settings"
    QLabel *title = new QLabel("Settings");
    title->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"           // text-slate-900
        "    font-size: 36px;"           // text-4xl
        "    font-weight: 600;"          // font-semibold
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "    border: none;"
        "    padding: 0;"
        "    margin: 0;"
        "}");

    // 副标题: "Customize your experience"
    QLabel *subtitle = new QLabel("Customize your experience");
    subtitle->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"             // text-slate-500
        "    font-size: 16px;"            // text-base
        "    font-weight: 400;"           // normal
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "    border: none;"
        "    padding: 0;"
        "    margin: 0;"
        "}");

    layout->addWidget(title);
    layout->addWidget(subtitle);

    return header;
}

QWidget* Settings::createSettingsCard()
{
    QWidget *card = new QWidget();
    card->setStyleSheet(
        "QWidget {"
        "    background: rgba(255, 255, 255, 0.7);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 20px;"
        "}");

    // 添加阴影效果: shadow-[0_30px_60px_rgba(0,0,0,0.06)]
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(60);           // 60px blur
    shadow->setColor(QColor(0, 0, 0, 15));  // 0.06 * 255 ≈ 15
    shadow->setOffset(0, 30);            // 30px offset
    card->setGraphicsEffect(shadow);

    // 卡片内容布局
    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // 添加所有设置项
    // 1. Launch at login
    layout->addWidget(createSettingItem(
        "Launch at login",
        "Start in background after system login",
        "launch_at_login"
    ));

    layout->addWidget(createSeparator());

    // 2. Allow LAN direct
    layout->addWidget(createSettingItem(
        "Allow LAN direct",
        "Bypass relay when on same network",
        "allow_lan_direct"
    ));

    layout->addWidget(createSeparator());

    // 3. Low latency mode
    layout->addWidget(createSettingItem(
        "Low latency mode",
        "Prioritize responsiveness over visual quality",
        "low_latency_mode"
    ));

    layout->addWidget(createSeparator());

    // 4. Allow notifications
    layout->addWidget(createSettingItem(
        "Allow notifications",
        "Show system notifications for events",
        "allow_notifications"
    ));

    return card;
}

QWidget* Settings::createSettingItem(const QString &title, const QString &description, const QString &settingKey)
{
    QWidget *item = new QWidget();
    item->setStyleSheet("background: transparent;");

    QHBoxLayout *layout = new QHBoxLayout(item);
    layout->setContentsMargins(24, 16, 24, 16);  // px-6 py-4 = 24px/16px
    layout->setSpacing(16);  // gap-4 = 16px

    // 左侧文本区域
    QWidget *textContainer = new QWidget();
    textContainer->setStyleSheet("background: transparent;");
    QVBoxLayout *textLayout = new QVBoxLayout(textContainer);
    textLayout->setContentsMargins(0, 0, 0, 0);
    textLayout->setSpacing(4);  // space-y-1 = 4px

    // 标题
    QLabel *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"              // text-slate-900
        "    font-size: 15px;"             // text-[15px]
        "    font-weight: 500;"            // font-medium
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "    border: none;"
        "    padding: 0;"
        "    margin: 0;"
        "}");

    // 描述
    QLabel *descLabel = new QLabel(description);
    descLabel->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"              // text-slate-500
        "    font-size: 14px;"             // text-sm
        "    font-weight: 400;"            // normal
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "    border: none;"
        "    padding: 0;"
        "    margin: 0;"
        "}");
    descLabel->setWordWrap(true);

    textLayout->addWidget(titleLabel);
    textLayout->addWidget(descLabel);

    // 右侧 ToggleSwitch
    ToggleSwitch *toggle = new ToggleSwitch();
    toggle->setProperty("settingKey", settingKey);

    // 连接信号
    connect(toggle, &ToggleSwitch::toggled, this, &Settings::onToggleSwitchChanged);

    // 从设置中加载初始状态
    bool checked = loadSetting(settingKey, false);
    toggle->setChecked(checked);

    // 添加到布局
    layout->addWidget(textContainer, 1);
    layout->addWidget(toggle, 0, Qt::AlignVCenter);

    return item;
}

QWidget* Settings::createSeparator()
{
    QFrame *separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Plain);
    separator->setStyleSheet(
        "QFrame {"
        "    background: rgba(0, 0, 0, 0.05);"  // border-black/5
        "    border: none;"
        "    margin-left: 24px;"               // mx-6 = 24px
        "    margin-right: 24px;"
        "    padding: 0;"
        "}");
    separator->setFixedHeight(1);
    separator->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    return separator;
}

void Settings::onToggleSwitchChanged(bool checked)
{
    ToggleSwitch *toggle = qobject_cast<ToggleSwitch*>(sender());
    if (!toggle) return;

    QString settingKey = toggle->property("settingKey").toString();

    // 保存设置
    saveSetting(settingKey, checked);

    // 应用设置变化
    applySetting(settingKey, checked);
}

void Settings::saveSetting(const QString &key, bool value)
{
    QSettings settings("RemoteDesk", "Application");
    settings.setValue(key, value);
    qDebug() << "Setting saved:" << key << "=" << value;
}

bool Settings::loadSetting(const QString &key, bool defaultValue)
{
    QSettings settings("RemoteDesk", "Application");
    return settings.value(key, defaultValue).toBool();
}

void Settings::applySetting(const QString &key, bool value)
{
    if (key == "launch_at_login") {
        qDebug() << "Launch at login:" << (value ? "Enabled" : "Disabled");
        // TODO: 实现开机启动逻辑（平台相关）
        // Windows: 注册表 HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
        // macOS: Launch Agents
        // Linux: ~/.config/autostart/
    }
    else if (key == "allow_lan_direct") {
        qDebug() << "Allow LAN direct:" << (value ? "Enabled" : "Disabled");
        // TODO: 实现局域网直连逻辑
        // 启用/禁用局域网发现和点对点连接
    }
    else if (key == "low_latency_mode") {
        qDebug() << "Low latency mode:" << (value ? "Enabled" : "Disabled");
        // TODO: 实现低延迟模式逻辑
        // 调整视频编码参数，降低视觉质量以减少延迟
    }
    else if (key == "allow_notifications") {
        qDebug() << "Allow notifications:" << (value ? "Enabled" : "Disabled");
        // TODO: 实现通知逻辑
        // 启用/禁用系统通知
    }
}
