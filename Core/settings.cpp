#include "settings.h"
#include "ui_settings.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>

Settings::Settings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);
    initUi();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::initUi()
{
    setupScrollArea();

    QWidget *content = ui->scrollAreaWidgetContents;
    if (content->layout()) {
        delete content->layout();
    }

    auto *rootLayout = new QVBoxLayout(content);
    rootLayout->setContentsMargins(48, 48, 48, 64);
    rootLayout->setSpacing(32);

    rootLayout->addWidget(createHeader());
    rootLayout->addWidget(createSettingsCard());
    rootLayout->addStretch();
}

void Settings::setupScrollArea()
{
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setStyleSheet(
        "QScrollArea {"
        "    border: none;"
        "    background: transparent;"
        "}" 
        "QScrollBar:vertical {"
        "    background: transparent;"
        "    width: 6px;"
        "}" 
        "QScrollBar::handle:vertical {"
        "    background: rgba(15,23,42,0.18);"
        "    border-radius: 3px;"
        "}" 
        "QScrollBar::handle:vertical:hover {"
        "    background: rgba(15,23,42,0.28);"
        "}" 
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    height: 0px;"
        "}");
}

QWidget *Settings::createHeader()
{
    auto *header = new QWidget;
    auto *layout = new QVBoxLayout(header);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(8);

    auto *title = new QLabel(tr("设置"), header);
    title->setStyleSheet("QLabel { color: rgba(15,23,42,0.92); font-size: 34px; font-weight: 600; }");

    auto *subtitle = new QLabel(tr("调整远控体验与通知偏好"), header);
    subtitle->setStyleSheet("QLabel { color: rgba(15,23,42,0.58); font-size: 14px; font-weight: 500; }");

    layout->addWidget(title);
    layout->addWidget(subtitle);

    return header;
}

QFrame *Settings::createSettingsCard()
{
    auto *card = new QFrame;
    card->setObjectName("settingsCard");
    card->setAttribute(Qt::WA_StyledBackground, true);
    card->setStyleSheet(
        "QFrame#settingsCard {"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "        stop:0 rgba(255,255,255,0.9),"
        "        stop:0.55 rgba(255,255,255,0.66),"
        "        stop:1 rgba(240,244,255,0.5));"
        "    border: 1px solid rgba(255,255,255,0.7);"
        "    border-top-color: rgba(255,255,255,0.86);"
        "    border-left-color: rgba(255,255,255,0.8);"
        "    border-right-color: rgba(15,23,42,0.08);"
        "    border-bottom-color: rgba(15,23,42,0.12);"
        "    border-radius: 24px;"
        "}");

    auto *shadow = new QGraphicsDropShadowEffect(card);
    shadow->setBlurRadius(48);
    shadow->setOffset(0, 16);
    shadow->setColor(QColor(15, 23, 42, 30));
    card->setGraphicsEffect(shadow);

    auto *layout = new QVBoxLayout(card);
    layout->setContentsMargins(24, 18, 24, 18);
    layout->setSpacing(0);

    layout->addWidget(createSettingRow(tr("开机自启动"), tr("登录系统后自动在后台运行"), QStringLiteral("launch_at_login"), true));
    layout->addWidget(createSeparator());
    layout->addWidget(createSettingRow(tr("允许局域网直连"), tr("同一网络下不经中转服务器"), QStringLiteral("allow_lan_direct"), true));
    layout->addWidget(createSeparator());
    layout->addWidget(createSettingRow(tr("低延迟模式"), tr("优先帧率，画质可能下降"), QStringLiteral("low_latency_mode"), false));
    layout->addWidget(createSeparator());
    layout->addWidget(createSettingRow(tr("允许通知"), tr("连接请求、异常提醒"), QStringLiteral("allow_notifications"), true));

    return card;
}

QWidget *Settings::createSettingRow(const QString &title, const QString &description, const QString &settingKey, bool defaultValue)
{
    auto *row = new QWidget;
    auto *layout = new QHBoxLayout(row);
    layout->setContentsMargins(8, 12, 8, 12);
    layout->setSpacing(16);

    auto *textContainer = new QWidget(row);
    auto *textLayout = new QVBoxLayout(textContainer);
    textLayout->setContentsMargins(8, 4, 8, 4);
    textLayout->setSpacing(6);

    auto *titleLabel = new QLabel(title, textContainer);
    titleLabel->setStyleSheet("QLabel { color: rgba(15,23,42,0.9); font-size: 15px; font-weight: 600; }");

    auto *descLabel = new QLabel(description, textContainer);
    descLabel->setWordWrap(true);
    descLabel->setStyleSheet("QLabel { color: rgba(15,23,42,0.58); font-size: 13px; font-weight: 500; }");

    textLayout->addWidget(titleLabel);
    textLayout->addWidget(descLabel);

    layout->addWidget(textContainer, 1);

    auto *toggle = new ToggleSwitch(row);
    toggle->setProperty("settingKey", settingKey);
    toggle->setChecked(loadSetting(settingKey, defaultValue));

    connect(toggle, &ToggleSwitch::toggled, this, &Settings::onToggleSwitchChanged);

    layout->addWidget(toggle, 0, Qt::AlignVCenter);

    return row;
}

QWidget *Settings::createSeparator() const
{
    auto *separator = new QFrame;
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Plain);
    separator->setStyleSheet(
        "QFrame {"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "        stop:0 rgba(255,255,255,0),"
        "        stop:0.5 rgba(148,163,184,0.28),"
        "        stop:1 rgba(255,255,255,0));"
        "    max-height: 1px;"
        "    min-height: 1px;"
        "    border: none;"
        "}");
    return separator;
}

void Settings::onToggleSwitchChanged(bool checked)
{
    auto *toggle = qobject_cast<ToggleSwitch *>(sender());
    if (!toggle)
        return;

    const QString key = toggle->property("settingKey").toString();
    saveSetting(key, checked);
    applySetting(key, checked);
}

void Settings::saveSetting(const QString &key, bool value)
{
    QSettings settings;
    settings.setValue(key, value);
}

bool Settings::loadSetting(const QString &key, bool defaultValue)
{
    QSettings settings;
    return settings.value(key, defaultValue).toBool();
}

void Settings::applySetting(const QString &key, bool value)
{
    if (key == QLatin1String("launch_at_login")) {
        applyLaunchAtLogin(value);
    } else if (key == QLatin1String("allow_lan_direct")) {
        applyAllowLanDirect(value);
    } else if (key == QLatin1String("low_latency_mode")) {
        applyLowLatencyMode(value);
    } else if (key == QLatin1String("allow_notifications")) {
        qDebug() << "Allow notifications:" << value;
    }
}

void Settings::applyLaunchAtLogin(bool enable)
{
    qDebug() << "Launch at login:" << (enable ? "Enabled" : "Disabled");
}

void Settings::applyLowLatencyMode(bool enable)
{
    qDebug() << "Low latency mode:" << (enable ? "Enabled" : "Disabled");
}

void Settings::applyAllowLanDirect(bool enable)
{
    qDebug() << "Allow LAN direct:" << (enable ? "Enabled" : "Disabled");
}
