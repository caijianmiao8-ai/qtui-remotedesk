#include "settings.h"
#include "ui_settings.h"
#include <QTimer>

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setStyleSheet("");
    initUi();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::initUi()
{
    setupWidget_1();
    setupWidget2();

}

void Settings::setupWidget_1()
{
    // 清除现有布局
    if (ui->widget_1->layout()) {
        delete ui->widget_1->layout();
    }

    // 创建新的垂直布局
    QVBoxLayout *layout = new QVBoxLayout(ui->widget_1);
    layout->setContentsMargins(0, 50, 0, 0);  // 上边距，让内容离顶部远

    // 设置 Welcome back 标签
    ui->label->setText("Settings");
    ui->label->setStyleSheet(
        "QLabel {"
        "    color: #000000;"
        "    font-size: 36px;"
        "    font-weight: bold;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background-color: transparent;"
        "    border: none;"
        "    margin: 0;"
        "    padding: 0;"
        "}");
    layout->addWidget(ui->label);
}

void Settings::setupWidget2()
{
    ui->widget_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // 设置 widget_2 的基本样式
    ui->widget_2->setStyleSheet(
        "QWidget#widget_2 {"
        "    background-color: #ffffff;"
        "    border-radius: 20px;"
        "    border: none;"
        "}");

    // 创建主阴影效果（底部阴影）
    QGraphicsDropShadowEffect *bottomShadow = new QGraphicsDropShadowEffect(this);
    bottomShadow->setBlurRadius(28);
    bottomShadow->setColor(QColor(0, 0, 0, 15));
    bottomShadow->setXOffset(0);
    bottomShadow->setYOffset(10);  // 主要向下偏移

    // 创建轻微的顶部阴影
    QGraphicsDropShadowEffect *topShadow = new QGraphicsDropShadowEffect(this);
    topShadow->setBlurRadius(20);
    topShadow->setColor(QColor(0, 0, 0, 15));
    topShadow->setXOffset(0);
    topShadow->setYOffset(10);     // 轻微的向上偏移

    // 应用阴影效果
    ui->widget_2->setGraphicsEffect(bottomShadow);

    setupWidget2Layout();
    setupSettingsItems();
}

void Settings::setupWidget2Layout()
{
    if (ui->widget_2->layout()) {
        delete ui->widget_2->layout();
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(ui->widget_2);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);  // 项之间没有额外间距，用分隔线控制
}

void Settings::setupSettingsItems()
{
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(ui->widget_2->layout());
    if (!mainLayout) return;

    mainLayout->setSpacing(0);

    // 第一项：开机启动
    mainLayout->addWidget(createSettingItem(
        "Launch at login",
        "Start in background after system login",
        "launch_at_login"
    ));

    // 添加分隔线
    mainLayout->addWidget(createSeparator());

    // 第二项：低延迟模式
    mainLayout->addWidget(createSettingItem(
        "Low latency mode",
        "Prioritize responsiveness over visual quality",
        "low_latency_mode"
    ));

    // 添加分隔线
    mainLayout->addWidget(createSeparator());

    // 第三项：允许局域网直连
    mainLayout->addWidget(createSettingItem(
        "Allow LAN direct",
        "Bypass relay when on same network",
        "allow_lan_direct"
    ));
}

QWidget* Settings::createSettingItem(const QString &title, const QString &description, const QString &settingKey)
{
    QWidget *itemWidget = new QWidget();
    itemWidget->setFixedHeight(54);
    itemWidget->setStyleSheet("background-color: #ffffff");

    QHBoxLayout *itemLayout = new QHBoxLayout(itemWidget);
    itemLayout->setContentsMargins(20, 4, 20, 4);
    itemLayout->setSpacing(0);

    // 左侧文字区域
    QWidget *textWidget = new QWidget();
    QVBoxLayout *textLayout = new QVBoxLayout(textWidget);
    textLayout->setContentsMargins(0, 0, 0, 0);
    textLayout->setSpacing(2);

    // 主标题
    QLabel *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet(
        "QLabel {"
        "    color: #000000;"
        "    font-size: 15px;"
        "    font-weight: normal;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background-color: transparent;"
        "    border: none;"
        "    margin: 0;"
        "    padding: 0;"
        "}");

    // 描述文字
    QLabel *descLabel = new QLabel(description);
    descLabel->setStyleSheet(
        "QLabel {"
        "    color: #666666;"
        "    font-size: 13px;"
        "    font-weight: normal;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background-color: transparent;"
        "    border: none;"
        "    margin: 0;"
        "    padding: 0;"
        "}");
    descLabel->setWordWrap(true);

    textLayout->addWidget(titleLabel);
    textLayout->addWidget(descLabel);
    textLayout->addStretch(1);

    // 右侧切换开关 - 使用自定义的 ToggleSwitch
    ToggleSwitch *toggleSwitch = createToggleSwitch(settingKey);

    // 添加到水平布局
    itemLayout->addWidget(textWidget, 1);
    itemLayout->addWidget(toggleSwitch, 0, Qt::AlignVCenter);

    return itemWidget;
}

ToggleSwitch* Settings::createToggleSwitch(const QString &settingKey)
{
    ToggleSwitch *toggle = new ToggleSwitch();
    toggle->setProperty("settingKey", settingKey);

    // 连接信号
    connect(toggle, &ToggleSwitch::toggled, this, &Settings::onToggleSwitchChanged);

    // 根据保存的设置初始化状态
    bool checked = loadSetting(settingKey, false);
    toggle->setChecked(checked);

    return toggle;
}

QWidget* Settings::createSeparator()
{
    QFrame *separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Plain);

    // 完全移除所有边距和内边距
    separator->setStyleSheet(
        "QFrame {"
        "    background-color: #e0e0e0;"
        "    border: none;"
        "    margin: 0px 20px;"
        "    padding: 0px;"
        "    max-height: 1px;"
        "    min-height: 1px;"
        "}");

    // 设置固定高度
    separator->setFixedHeight(0.5);

    // 设置大小策略，防止扩展
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
    if (key == "launch_at_login") {
        // 应用开机启动设置
        applyLaunchAtLogin(value);
    } else if (key == "low_latency_mode") {
        // 应用低延迟模式设置
        applyLowLatencyMode(value);
    } else if (key == "allow_lan_direct") {
        // 应用局域网直连设置
        applyAllowLanDirect(value);
    }
}

void Settings::applyLaunchAtLogin(bool enable)
{
    // 实现开机启动逻辑
    // 这取决于您的平台和具体实现
    qDebug() << "Launch at login:" << (enable ? "Enabled" : "Disabled");
}

void Settings::applyLowLatencyMode(bool enable)
{
    // 实现低延迟模式逻辑
    qDebug() << "Low latency mode:" << (enable ? "Enabled" : "Disabled");
}

void Settings::applyAllowLanDirect(bool enable)
{
    // 实现局域网直连逻辑
    qDebug() << "Allow LAN direct:" << (enable ? "Enabled" : "Disabled");
}
