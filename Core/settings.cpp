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

    // React: 添加Cupertino风格滚动条
    ui->widget->setStyleSheet(
        "QScrollArea {"
        "    border: none;"
        "    background: transparent;"
        "}"
        "QScrollBar:vertical {"
        "    background: transparent;"
        "    width: 4px;"  // React: width: 4px
        "    margin: 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: rgba(60, 60, 67, 0.18);"  // React: cupertino-scroll--light
        "    border-radius: 999px;"               // React: border-radius: 999px
        "    min-height: 20px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "    background: rgba(60, 60, 67, 0.36);"  // React: hover效果
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    border: none;"
        "    background: none;"
        "    height: 0px;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: transparent;"
        "}"
        "QScrollBar:horizontal {"
        "    background: transparent;"
        "    height: 4px;"  // React: height: 4px
        "    margin: 0px;"
        "}"
        "QScrollBar::handle:horizontal {"
        "    background: rgba(60, 60, 67, 0.18);"
        "    border-radius: 999px;"
        "    min-width: 20px;"
        "}"
        "QScrollBar::handle:horizontal:hover {"
        "    background: rgba(60, 60, 67, 0.36);"
        "}"
        "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {"
        "    border: none;"
        "    background: none;"
        "    width: 0px;"
        "}"
        "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {"
        "    background: transparent;"
        "}"
    );

    // 创建主布局 - 严格按照React代码
    QVBoxLayout *mainLayout = new QVBoxLayout(ui->widget);
    mainLayout->setContentsMargins(32, 32, 32, 32);  // p-8 = 32px
    mainLayout->setSpacing(0);

    // 1. 标题（React: 只有一个大标题，没有副标题！）
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
    layout->setSpacing(0);

    // React: 只有一个大标题 "设置" / "Settings"
    QLabel *title = new QLabel("设置");  // 或使用多语言
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

    layout->addWidget(title);

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

    // 添加阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(60);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 30);
    card->setGraphicsEffect(shadow);

    // 卡片内容布局 - React: px-6 (24px 左右边距)
    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(24, 0, 24, 0);  // px-6
    layout->setSpacing(0);

    // React代码中的四个设置项（顺序严格一致）
    layout->addWidget(createSettingItem(
        "开机自启动",                    // autoLaunch
        "登录系统后自动在后台运行",       // autoLaunchDesc
        "launch_at_login"
    ));

    layout->addWidget(createSeparator());

    layout->addWidget(createSettingItem(
        "允许局域网直连",                 // allowLanDirect
        "同一网络下不经中转服务器",       // allowLanDirectDesc
        "allow_lan_direct"
    ));

    layout->addWidget(createSeparator());

    layout->addWidget(createSettingItem(
        "低延迟模式",                     // lowLatencyMode
        "优先帧率，画质可能下降",         // lowLatencyModeDesc
        "low_latency_mode"
    ));

    layout->addWidget(createSeparator());

    layout->addWidget(createSettingItem(
        "允许通知",                       // allowNotifications
        "连接请求、异常提醒",             // allowNotificationsDesc
        "allow_notifications"
    ));

    return card;
}

QWidget* Settings::createSettingItem(const QString &title, const QString &description, const QString &settingKey)
{
    QWidget *item = new QWidget();
    item->setStyleSheet("background: transparent;");

    // React: py-4 = 垂直16px
    QHBoxLayout *layout = new QHBoxLayout(item);
    layout->setContentsMargins(0, 16, 0, 16);  // py-4
    layout->setSpacing(16);  // 左右间距

    // 左侧文本区域
    QWidget *textContainer = new QWidget();
    textContainer->setStyleSheet("background: transparent;");
    QVBoxLayout *textLayout = new QVBoxLayout(textContainer);
    textLayout->setContentsMargins(0, 0, 0, 0);
    textLayout->setSpacing(4);  // React: mt-1 = 4px

    // 标题 - React: text-[14px] font-medium
    QLabel *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"              // text-slate-900
        "    font-size: 14px;"             // text-[14px]
        "    font-weight: 500;"            // font-medium
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "    border: none;"
        "    padding: 0;"
        "    margin: 0;"
        "}");

    // 描述 - React: text-[12px]
    QLabel *descLabel = new QLabel(description);
    descLabel->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"              // text-slate-500
        "    font-size: 12px;"             // text-[12px]
        "    font-weight: 400;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "    border: none;"
        "    padding: 0;"
        "    margin: 0;"
        "}");
    descLabel->setWordWrap(true);

    textLayout->addWidget(titleLabel);
    textLayout->addWidget(descLabel);

    // 右侧 ToggleSwitch (React: w-11 h-6 = 44x24px)
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
    // React: border-b 分隔线
    QFrame *separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Plain);
    separator->setStyleSheet(
        "QFrame {"
        "    background: rgba(0, 0, 0, 0.05);"  // theme.divider
        "    border: none;"
        "    padding: 0;"
        "    margin: 0;"
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
        // TODO: 实现开机启动逻辑
    }
    else if (key == "allow_lan_direct") {
        qDebug() << "Allow LAN direct:" << (value ? "Enabled" : "Disabled");
        // TODO: 实现局域网直连逻辑
    }
    else if (key == "low_latency_mode") {
        qDebug() << "Low latency mode:" << (value ? "Enabled" : "Disabled");
        // TODO: 实现低延迟模式逻辑
    }
    else if (key == "allow_notifications") {
        qDebug() << "Allow notifications:" << (value ? "Enabled" : "Disabled");
        // TODO: 实现通知逻辑
    }
}
