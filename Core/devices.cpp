#include "devices.h"
#include "ui_devices.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QFrame>

// 模拟设备数据结构
struct DeviceInfo {
    QString name;
    QString os;
    QString ip;
    QString lastConnect;
    QString network;
    QString delay;
    bool online;
    bool isController;  // 是否是控制端设备
};

Devices::Devices(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Devices)
{
    ui->setupUi(this);
    setStyleSheet("background: transparent;");

    buildLayout();
}

Devices::~Devices()
{
    delete ui;
}

void Devices::buildLayout()
{
    // 清空现有布局
    if (layout()) {
        QLayoutItem *item;
        while ((item = layout()->takeAt(0))) {
            if (item->widget()) item->widget()->deleteLater();
            delete item;
        }
        delete layout();
    }

    // 创建主滚动区域
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setStyleSheet(
        "QScrollArea { background: transparent; border: none; }"
        "QScrollBar:vertical {"
        "    background: transparent;"
        "    width: 4px;"
        "    margin: 0;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: rgba(60, 60, 67, 0.18);"
        "    border-radius: 2px;"
        "    min-height: 20px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "    background: rgba(60, 60, 67, 0.36);"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    height: 0px;"
        "    background: transparent;"
        "}"
    );

    // 内容容器
    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background: transparent;");

    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(32, 20, 32, 32);  // p-8 = 32px, mt-5 = 20px
    contentLayout->setSpacing(0);
    contentLayout->setAlignment(Qt::AlignTop);

    // 1. 标题和操作按钮区
    contentLayout->addWidget(createHeaderSection());
    contentLayout->addSpacing(16);  // mb-4

    // 2. 提示卡片
    contentLayout->addWidget(createPairingHintCard());
    contentLayout->addSpacing(32);  // mb-8

    // 3. 控制端设备区域
    contentLayout->addWidget(createControllersSection());
    contentLayout->addSpacing(48);  // mb-12

    // 4. 已注册主机设备区域
    contentLayout->addWidget(createRegisteredDevicesSection());

    contentLayout->addStretch(1);

    scrollArea->setWidget(contentWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(scrollArea);
}

QWidget* Devices::createHeaderSection()
{
    QWidget *header = new QWidget();
    header->setStyleSheet("background: transparent;");

    QHBoxLayout *layout = new QHBoxLayout(header);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(16);

    // 左侧标题区
    QWidget *titleArea = new QWidget();
    titleArea->setStyleSheet("background: transparent;");
    QVBoxLayout *titleLayout = new QVBoxLayout(titleArea);
    titleLayout->setContentsMargins(0, 0, 0, 0);
    titleLayout->setSpacing(8);  // mb-2

    QLabel *title = new QLabel("设备管理");
    title->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 36px;"
        "    font-weight: 600;"
        "    background: transparent;"
        "}"
    );

    QLabel *subtitle = new QLabel("本账号下所有已注册的设备。本PC当前为被控端（仅第一期提供被控功能）");
    subtitle->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 14px;"
        "    background: transparent;"
        "}"
    );

    titleLayout->addWidget(title);
    titleLayout->addWidget(subtitle);

    // 右侧按钮区
    QWidget *buttonsArea = new QWidget();
    buttonsArea->setStyleSheet("background: transparent;");
    QHBoxLayout *buttonsLayout = new QHBoxLayout(buttonsArea);
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsLayout->setSpacing(12);  // gap-3

    // 搜索按钮
    QPushButton *searchBtn = createToolButton("🔍 搜索");
    // 筛选按钮
    QPushButton *filterBtn = createToolButton("🎚️ 筛选");

    buttonsLayout->addWidget(searchBtn);
    buttonsLayout->addWidget(filterBtn);

    layout->addWidget(titleArea, 1);
    layout->addWidget(buttonsArea);

    return header;
}

QPushButton* Devices::createToolButton(const QString &text)
{
    QPushButton *btn = new QPushButton(text);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet(
        "QPushButton {"
        "    background: rgba(255, 255, 255, 0.6);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 14px;"
        "    color: #1e293b;"
        "    font-size: 14px;"
        "    font-weight: 500;"
        "    padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        "    background: rgba(0, 0, 0, 0.03);"
        "}"
        "QPushButton:pressed {"
        "    background: rgba(0, 0, 0, 0.05);"
        "}"
    );
    return btn;
}

QWidget* Devices::createPairingHintCard()
{
    QWidget *card = new QWidget();
    card->setStyleSheet(
        "QWidget {"
        "    background: rgba(255, 255, 255, 0.7);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 20px;"
        "}"
    );

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(60);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 30);
    card->setGraphicsEffect(shadow);

    QHBoxLayout *layout = new QHBoxLayout(card);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(12);

    QWidget *iconContainer = new QWidget();
    iconContainer->setFixedSize(32, 32);
    iconContainer->setStyleSheet(
        "QWidget {"
        "    background: rgba(10, 132, 255, 0.12);"
        "    border-radius: 14px;"
        "}"
    );

    QLabel *icon = new QLabel("ℹ️", iconContainer);
    icon->setGeometry(0, 0, 32, 32);
    icon->setAlignment(Qt::AlignCenter);
    icon->setStyleSheet("background: transparent; font-size: 16px;");

    QLabel *text = new QLabel("提示：请在手机端使用同一账号登录，即可从手机远程接管本电脑。");
    text->setWordWrap(true);
    text->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 12px;"
        "    line-height: 1.625;"
        "    background: transparent;"
        "}"
    );

    layout->addWidget(iconContainer);
    layout->addWidget(text, 1);

    return card;
}

QWidget* Devices::createControllersSection()
{
    QWidget *section = new QWidget();
    section->setStyleSheet("background: transparent;");

    QVBoxLayout *layout = new QVBoxLayout(section);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // 标题
    QLabel *title = new QLabel("可控制本机的设备");
    title->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 20px;"
        "    font-weight: 600;"
        "    background: transparent;"
        "}"
    );

    // 描述
    QLabel *desc = new QLabel("已登录同一账号的手机 / 平板，允许远程接管本机");
    desc->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 14px;"
        "    background: transparent;"
        "}"
    );

    layout->addWidget(title);
    layout->addSpacing(4);  // mb-1
    layout->addWidget(desc);
    layout->addSpacing(16);  // mb-4

    // 设备网格 (md:grid-cols-2)
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setHorizontalSpacing(24);  // gap-6
    gridLayout->setVerticalSpacing(24);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    // 模拟控制端设备数据
    QVector<DeviceInfo> controllers = {
        {"iPhone 15 Pro", "iOS 18", "", "刚刚", "", "", true, true},
        {"iPad Air", "iPadOS 18", "", "2小时前", "", "", false, true}
    };

    for (int i = 0; i < controllers.size(); i++) {
        int row = i / 2;
        int col = i % 2;
        gridLayout->addWidget(createControllerCard(controllers[i]), row, col);
    }

    layout->addLayout(gridLayout);

    return section;
}

QWidget* Devices::createControllerCard(const DeviceInfo &device)
{
    QWidget *card = new QWidget();
    card->setMinimumHeight(260);
    card->setStyleSheet(
        "QWidget {"
        "    background: rgba(255, 255, 255, 0.7);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 20px;"
        "}"
    );

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(60);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 30);
    card->setGraphicsEffect(shadow);

    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(24, 24, 24, 24);  // p-6
    layout->setSpacing(0);

    // 顶部：图标 + 名称 + 状态
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setSpacing(16);  // gap-4

    // 图标容器 (w-16 h-16 = 64x64)
    QWidget *iconContainer = new QWidget();
    iconContainer->setFixedSize(64, 64);
    QString iconBg = device.online
        ? "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #0A84FF, stop:1 #0051C7);"
        : "background: #94a3b8;";
    iconContainer->setStyleSheet(
        QString("QWidget {"
        "    %1"
        "    border-radius: 16px;"
        "}").arg(iconBg)
    );

    QLabel *icon = new QLabel("📱", iconContainer);
    icon->setGeometry(0, 0, 64, 64);
    icon->setAlignment(Qt::AlignCenter);
    icon->setStyleSheet("background: transparent; font-size: 32px;");

    // 名称和OS
    QWidget *infoArea = new QWidget();
    infoArea->setStyleSheet("background: transparent;");
    QVBoxLayout *infoLayout = new QVBoxLayout(infoArea);
    infoLayout->setContentsMargins(0, 0, 0, 0);
    infoLayout->setSpacing(4);

    QLabel *name = new QLabel(device.name);
    name->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 20px;"
        "    font-weight: 600;"
        "    background: transparent;"
        "}"
    );

    QLabel *os = new QLabel(device.os);
    os->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 14px;"
        "    background: transparent;"
        "}"
    );

    infoLayout->addWidget(name);
    infoLayout->addWidget(os);

    // 状态Badge
    QLabel *statusBadge = createStatusBadge(device.online);

    topLayout->addWidget(iconContainer);
    topLayout->addWidget(infoArea, 1);
    topLayout->addWidget(statusBadge);

    layout->addLayout(topLayout);
    layout->addSpacing(16);  // mt-4

    // 信息行
    QWidget *infoSection = new QWidget();
    infoSection->setStyleSheet("background: transparent;");
    QVBoxLayout *infoSectionLayout = new QVBoxLayout(infoSection);
    infoSectionLayout->setContentsMargins(0, 0, 0, 0);
    infoSectionLayout->setSpacing(8);  // space-y-2

    infoSectionLayout->addWidget(createInfoRow("最近活跃", device.lastConnect));

    layout->addWidget(infoSection, 1);
    layout->addSpacing(16);  // pt-4

    // 按钮区
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setSpacing(8);  // gap-2

    QPushButton *manageBtn = new QPushButton("管理");
    manageBtn->setCursor(Qt::PointingHandCursor);
    manageBtn->setStyleSheet(
        "QPushButton {"
        "    background: rgba(255, 255, 255, 0.6);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 14px;"
        "    color: #1e293b;"
        "    font-size: 14px;"
        "    font-weight: 500;"
        "    padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        "    background: rgba(0, 0, 0, 0.03);"
        "}"
    );

    QPushButton *deleteBtn = new QPushButton("🗑️");
    deleteBtn->setCursor(Qt::PointingHandCursor);
    deleteBtn->setFixedSize(40, 36);
    deleteBtn->setStyleSheet(
        "QPushButton {"
        "    background: transparent;"
        "    border: 1px solid rgba(239, 68, 68, 0.2);"
        "    border-radius: 14px;"
        "    color: #ef4444;"
        "    font-size: 16px;"
        "}"
        "QPushButton:hover {"
        "    background: rgba(239, 68, 68, 0.1);"
        "}"
    );

    buttonsLayout->addWidget(manageBtn, 1);
    buttonsLayout->addWidget(deleteBtn);

    layout->addLayout(buttonsLayout);

    return card;
}

QWidget* Devices::createRegisteredDevicesSection()
{
    QWidget *section = new QWidget();
    section->setStyleSheet("background: transparent;");

    QVBoxLayout *layout = new QVBoxLayout(section);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    QLabel *title = new QLabel("已注册的主机设备");
    title->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 20px;"
        "    font-weight: 600;"
        "    background: transparent;"
        "}"
    );

    QLabel *desc = new QLabel("同一账号下的电脑 / 服务器");
    desc->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 14px;"
        "    background: transparent;"
        "}"
    );

    layout->addWidget(title);
    layout->addSpacing(4);
    layout->addWidget(desc);
    layout->addSpacing(16);

    // 设备网格
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setHorizontalSpacing(24);
    gridLayout->setVerticalSpacing(24);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    // 模拟主机设备数据
    QVector<DeviceInfo> devices = {
        {"我的工作电脑", "Windows 11", "192.168.1.100", "2分钟前", "LAN", "5ms", true, false},
        {"家里的MacBook", "macOS 14", "192.168.1.105", "10分钟前", "P2P", "12ms", true, false},
        {"Windows台式机", "Windows 10", "120.76.xxx.xxx", "2小时前", "Relay", "-", false, false},
        {"办公室主机", "Windows 11", "10.0.0.50", "1天前", "LAN", "3ms", true, false}
    };

    for (int i = 0; i < devices.size(); i++) {
        int row = i / 2;
        int col = i % 2;
        gridLayout->addWidget(createDeviceCard(devices[i]), row, col);
    }

    layout->addLayout(gridLayout);

    return section;
}

QWidget* Devices::createDeviceCard(const DeviceInfo &device)
{
    QWidget *card = new QWidget();
    card->setMinimumHeight(260);
    card->setStyleSheet(
        "QWidget {"
        "    background: rgba(255, 255, 255, 0.7);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 20px;"
        "}"
    );

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(60);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 30);
    card->setGraphicsEffect(shadow);

    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(0);

    // 顶部：图标 + 名称 + 状态
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setSpacing(16);

    // 图标容器
    QWidget *iconContainer = new QWidget();
    iconContainer->setFixedSize(64, 64);
    QString iconBg = device.online
        ? "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #0A84FF, stop:1 #0051C7);"
        : "background: #94a3b8;";
    iconContainer->setStyleSheet(
        QString("QWidget {"
        "    %1"
        "    border-radius: 16px;"
        "}").arg(iconBg)
    );

    QLabel *icon = new QLabel("🖥️", iconContainer);
    icon->setGeometry(0, 0, 64, 64);
    icon->setAlignment(Qt::AlignCenter);
    icon->setStyleSheet("background: transparent; font-size: 32px;");

    // 名称和OS
    QWidget *infoArea = new QWidget();
    infoArea->setStyleSheet("background: transparent;");
    QVBoxLayout *infoLayout = new QVBoxLayout(infoArea);
    infoLayout->setContentsMargins(0, 0, 0, 0);
    infoLayout->setSpacing(4);

    QLabel *name = new QLabel(device.name);
    name->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 20px;"
        "    font-weight: 600;"
        "    background: transparent;"
        "}"
    );

    QLabel *os = new QLabel(device.os);
    os->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 14px;"
        "    background: transparent;"
        "}"
    );

    infoLayout->addWidget(name);
    infoLayout->addWidget(os);

    QLabel *statusBadge = createStatusBadge(device.online);

    topLayout->addWidget(iconContainer);
    topLayout->addWidget(infoArea, 1);
    topLayout->addWidget(statusBadge);

    layout->addLayout(topLayout);
    layout->addSpacing(16);

    // 信息行
    QWidget *infoSection = new QWidget();
    infoSection->setStyleSheet("background: transparent;");
    QVBoxLayout *infoSectionLayout = new QVBoxLayout(infoSection);
    infoSectionLayout->setContentsMargins(0, 0, 0, 0);
    infoSectionLayout->setSpacing(8);

    infoSectionLayout->addWidget(createInfoRow("IP地址", device.ip));
    infoSectionLayout->addWidget(createInfoRow("最后连接", device.lastConnect));

    if (device.online) {
        infoSectionLayout->addWidget(createInfoRow("网络模式", device.network, getNetworkColor(device.network)));
        infoSectionLayout->addWidget(createInfoRow("延迟", device.delay, "#22c55e"));
    }

    layout->addWidget(infoSection, 1);
    layout->addSpacing(16);

    // 按钮区
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setSpacing(8);

    QPushButton *manageBtn = new QPushButton("管理");
    manageBtn->setCursor(Qt::PointingHandCursor);
    manageBtn->setStyleSheet(
        "QPushButton {"
        "    background: rgba(255, 255, 255, 0.6);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 14px;"
        "    color: #1e293b;"
        "    font-size: 14px;"
        "    font-weight: 500;"
        "    padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        "    background: rgba(0, 0, 0, 0.03);"
        "}"
    );

    QPushButton *deleteBtn = new QPushButton("🗑️");
    deleteBtn->setCursor(Qt::PointingHandCursor);
    deleteBtn->setFixedSize(40, 36);
    deleteBtn->setStyleSheet(
        "QPushButton {"
        "    background: transparent;"
        "    border: 1px solid rgba(239, 68, 68, 0.2);"
        "    border-radius: 14px;"
        "    color: #ef4444;"
        "    font-size: 16px;"
        "}"
        "QPushButton:hover {"
        "    background: rgba(239, 68, 68, 0.1);"
        "}"
    );

    buttonsLayout->addWidget(manageBtn, 1);
    buttonsLayout->addWidget(deleteBtn);

    layout->addLayout(buttonsLayout);

    return card;
}

QLabel* Devices::createStatusBadge(bool online)
{
    QLabel *badge = new QLabel();
    if (online) {
        badge->setText("在线");
        badge->setStyleSheet(
            "QLabel {"
            "    background: rgba(16, 185, 129, 0.12);"
            "    color: #10b981;"
            "    border: 1px solid rgba(16, 185, 129, 0.2);"
            "    border-radius: 12px;"
            "    font-size: 11px;"
            "    font-weight: 500;"
            "    padding: 4px 8px;"
            "}"
        );
    } else {
        badge->setText("离线");
        badge->setStyleSheet(
            "QLabel {"
            "    background: rgba(0, 0, 0, 0.03);"
            "    color: #64748b;"
            "    border: 1px solid rgba(0, 0, 0, 0.1);"
            "    border-radius: 12px;"
            "    font-size: 11px;"
            "    font-weight: 500;"
            "    padding: 4px 8px;"
            "}"
        );
    }
    badge->setAlignment(Qt::AlignCenter);
    return badge;
}

QWidget* Devices::createInfoRow(const QString &label, const QString &value, const QString &valueColor)
{
    QWidget *row = new QWidget();
    row->setStyleSheet("background: transparent;");

    QHBoxLayout *layout = new QHBoxLayout(row);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    QLabel *labelWidget = new QLabel(label);
    labelWidget->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 14px;"
        "    background: transparent;"
        "}"
    );

    QLabel *valueWidget = new QLabel(value);
    QString color = valueColor.isEmpty() ? "#1e293b" : valueColor;
    QString fontFamily = (label == "IP地址" || label == "设备ID") ? "font-family: 'Courier New', monospace;" : "";
    QString fontWeight = valueColor.isEmpty() ? "" : "font-weight: 500;";

    valueWidget->setStyleSheet(
        QString("QLabel {"
        "    color: %1;"
        "    font-size: 14px;"
        "    %2"
        "    %3"
        "    background: transparent;"
        "}").arg(color, fontFamily, fontWeight)
    );

    layout->addWidget(labelWidget);
    layout->addStretch();
    layout->addWidget(valueWidget);

    return row;
}

QString Devices::getNetworkColor(const QString &network)
{
    if (network == "LAN") return "#22c55e";      // green
    if (network == "P2P") return "#06b6d4";      // cyan
    if (network == "Relay") return "#f97316";    // orange
    return "#1e293b";
}
