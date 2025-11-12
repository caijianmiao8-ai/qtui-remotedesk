#include "devices.h"
#include "ui_devices.h"
#include "iconhelper.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

Devices::Devices(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Devices)
{
    ui->setupUi(this);
    initUi();
}

Devices::~Devices()
{
    delete ui;
}

void Devices::initUi()
{
    setupScrollArea();

    QWidget *content = ui->scrollAreaWidgetContents;
    if (content->layout()) {
        delete content->layout();
    }

    auto *rootLayout = new QVBoxLayout(content);
    rootLayout->setContentsMargins(48, 48, 48, 64);
    rootLayout->setSpacing(32);

    rootLayout->addWidget(createHeaderSection());
    rootLayout->addWidget(createPairingHintCard());
    rootLayout->addWidget(createControllersSection());
    rootLayout->addWidget(createRegisteredDevicesSection());
    rootLayout->addStretch();
}

void Devices::setupScrollArea()
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

QWidget *Devices::createHeaderSection()
{
    auto *section = new QWidget;
    auto *layout = new QHBoxLayout(section);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(20);

    auto *textContainer = new QWidget(section);
    auto *textLayout = new QVBoxLayout(textContainer);
    textLayout->setContentsMargins(0, 0, 0, 0);
    textLayout->setSpacing(8);
    textLayout->addWidget(createTitleLabel(tr("设备管理"), 34));
    textLayout->addWidget(createSecondaryLabel(tr("本账号下所有已注册的设备。本PC当前为被控端（仅第一期提供被控功能）"), 14, 0.58));

    layout->addWidget(textContainer, 1);

    auto createActionButton = [&](const QString &text, IconGlyph glyph) {
        auto *button = new QPushButton(text, section);
        button->setCursor(Qt::PointingHandCursor);
        button->setStyleSheet(
            "QPushButton {"
            "    background-color: rgba(255,255,255,0.55);"
            "    border: 1px solid rgba(15,23,42,0.05);"
            "    border-radius: 16px;"
            "    padding: 10px 18px;"
            "    color: rgba(15,23,42,0.85);"
            "    font-size: 14px;"
            "    font-weight: 600;"
            "}" 
            "QPushButton:hover {"
            "    background-color: rgba(255,255,255,0.72);"
            "}" 
            "QPushButton:pressed {"
            "    background-color: rgba(10,132,255,0.12);"
            "}");
        button->setIcon(QIcon(IconHelper::draw(glyph, QSize(20, 20), QColor(10, 132, 255))));
        button->setIconSize(QSize(20, 20));
        return button;
    };

    auto *actionsContainer = new QWidget(section);
    auto *actionsLayout = new QHBoxLayout(actionsContainer);
    actionsLayout->setContentsMargins(0, 0, 0, 0);
    actionsLayout->setSpacing(12);
    actionsLayout->addWidget(createActionButton(tr("搜索"), IconGlyph::Search));
    actionsLayout->addWidget(createActionButton(tr("筛选"), IconGlyph::Filter));

    layout->addWidget(actionsContainer, 0, Qt::AlignRight | Qt::AlignTop);

    return section;
}

QFrame *Devices::createPairingHintCard()
{
    auto *card = createGlassCard("devicesPairingHint");
    card->setGraphicsEffect(createShadow(card, 36.0, 12.0));

    auto *layout = new QHBoxLayout(card);
    layout->setContentsMargins(24, 20, 24, 20);
    layout->setSpacing(18);

    auto *iconWrapper = new QLabel(card);
    iconWrapper->setFixedSize(44, 44);
    iconWrapper->setAlignment(Qt::AlignCenter);
    iconWrapper->setPixmap(IconHelper::draw(IconGlyph::Info, QSize(20, 20), QColor(10, 132, 255)));
    iconWrapper->setStyleSheet("QLabel { background-color: rgba(10,132,255,0.12); border-radius: 16px; }");

    auto *text = createSecondaryLabel(tr("提示：请在手机端使用同一账号登录，即可从手机远程接管本电脑。"), 12, 0.6);
    text->setWordWrap(true);

    layout->addWidget(iconWrapper, 0, Qt::AlignTop);
    layout->addWidget(text, 1);

    return card;
}

QWidget *Devices::createControllersSection()
{
    QVector<ControllerInfo> controllers = {
        {tr("iPhone 15 Pro"), tr("iOS 18"), true, tr("刚刚"), QStringLiteral("82%")},
        {tr("iPad Air"), tr("iPadOS 18"), false, tr("2小时前"), QStringLiteral("57%")}
    };

    auto *section = new QWidget;
    auto *layout = new QVBoxLayout(section);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(16);

    layout->addWidget(createTitleLabel(tr("可控制本机的设备"), 22));
    layout->addWidget(createSecondaryLabel(tr("已登录同一账号的手机 / 平板，允许远程接管本机"), 13, 0.6));

    auto *gridWidget = new QWidget(section);
    auto *grid = new QGridLayout(gridWidget);
    grid->setContentsMargins(0, 0, 0, 0);
    grid->setHorizontalSpacing(24);
    grid->setVerticalSpacing(24);

    for (int i = 0; i < controllers.size(); ++i) {
        auto *card = buildControllerCard(controllers.at(i));
        grid->addWidget(card, i / 2, i % 2);
    }

    layout->addWidget(gridWidget);

    return section;
}

QWidget *Devices::createRegisteredDevicesSection()
{
    QVector<DeviceInfo> devices = {
        {tr("我的工作电脑"), tr("Windows 11"), QStringLiteral("192.168.1.100"), tr("2分钟前"), QStringLiteral("LAN"), QStringLiteral("5ms"), true},
        {tr("家里的MacBook"), QStringLiteral("macOS 14"), QStringLiteral("192.168.1.105"), tr("10分钟前"), QStringLiteral("P2P"), QStringLiteral("12ms"), true},
        {tr("Windows台式机"), QStringLiteral("Windows 10"), QStringLiteral("120.76.xxx.xxx"), tr("2小时前"), QStringLiteral("Relay"), QStringLiteral("-"), false},
        {tr("办公室主机"), QStringLiteral("Windows 11"), QStringLiteral("10.0.0.50"), tr("1天前"), QStringLiteral("LAN"), QStringLiteral("3ms"), true}
    };

    auto *section = new QWidget;
    auto *layout = new QVBoxLayout(section);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(16);

    layout->addWidget(createTitleLabel(tr("已注册的主机设备"), 22));
    layout->addWidget(createSecondaryLabel(tr("同一账号下的电脑 / 服务器"), 13, 0.6));

    auto *gridWidget = new QWidget(section);
    auto *grid = new QGridLayout(gridWidget);
    grid->setContentsMargins(0, 0, 0, 0);
    grid->setHorizontalSpacing(24);
    grid->setVerticalSpacing(24);

    for (int i = 0; i < devices.size(); ++i) {
        auto *card = buildDeviceCard(devices.at(i));
        grid->addWidget(card, i / 2, i % 2);
    }

    layout->addWidget(gridWidget);

    return section;
}

QFrame *Devices::createGlassCard(const QString &objectName) const
{
    auto *card = new QFrame;
    card->setObjectName(objectName);
    card->setAttribute(Qt::WA_StyledBackground, true);
    card->setStyleSheet(QString(
        "QFrame#%1 {"
        "    background-color: rgba(255,255,255,0.74);"
        "    border: 1px solid rgba(15,23,42,0.05);"
        "    border-radius: 22px;"
        "}").arg(objectName));
    return card;
}

QGraphicsDropShadowEffect *Devices::createShadow(QObject *parent, qreal blur, qreal yOffset) const
{
    auto *effect = new QGraphicsDropShadowEffect(parent);
    effect->setBlurRadius(blur);
    effect->setOffset(0, yOffset);
    effect->setColor(QColor(15, 23, 42, 26));
    return effect;
}

QLabel *Devices::createTitleLabel(const QString &text, int size, bool bold) const
{
    auto *label = new QLabel(text);
    label->setStyleSheet(QString(
        "QLabel {"
        "    color: rgba(15,23,42,0.9);"
        "    font-size: %1px;"
        "    font-weight: %2;"
        "}" ).arg(size).arg(bold ? 600 : 500));
    return label;
}

QLabel *Devices::createSecondaryLabel(const QString &text, int size, qreal opacity) const
{
    auto *label = new QLabel(text);
    label->setStyleSheet(QString(
        "QLabel {"
        "    color: rgba(15,23,42,%1);"
        "    font-size: %2px;"
        "    font-weight: 500;"
        "}" ).arg(opacity).arg(size));
    label->setWordWrap(true);
    return label;
}

QWidget *Devices::createStatusBadge(bool online) const
{
    QColor color = online ? QColor(34, 197, 94) : QColor(148, 163, 184);
    auto *badge = new QWidget;
    badge->setObjectName("deviceStatusBadge");
    badge->setStyleSheet(QString(
        "QWidget#deviceStatusBadge {"
        "    background-color: rgba(%1,%2,%3,%4);"
        "    border-radius: 999px;"
        "    border: 1px solid rgba(%1,%2,%3,%5);"
        "}" )
        .arg(color.red())
        .arg(color.green())
        .arg(color.blue())
        .arg(online ? "0.16" : "0.12")
        .arg(online ? "0.28" : "0.18"));

    auto *layout = new QHBoxLayout(badge);
    layout->setContentsMargins(10, 6, 14, 6);
    layout->setSpacing(6);

    auto *dot = new QLabel(badge);
    dot->setFixedSize(8, 8);
    dot->setStyleSheet(QString("QLabel { background-color: rgb(%1,%2,%3); border-radius: 4px; }")
                           .arg(color.red())
                           .arg(color.green())
                           .arg(color.blue()));

    auto *label = new QLabel(online ? tr("在线") : tr("离线"), badge);
    label->setStyleSheet(QString("QLabel { color: rgb(%1,%2,%3); font-size: 12px; font-weight: 600; }")
                             .arg(color.red())
                             .arg(color.green())
                             .arg(color.blue()));

    layout->addWidget(dot);
    layout->addWidget(label);

    return badge;
}

QFrame *Devices::buildControllerCard(const ControllerInfo &info) const
{
    auto *card = createGlassCard("controllerCard");
    card->setGraphicsEffect(createShadow(card, 38.0, 12.0));

    auto *layout = new QVBoxLayout(card);
    layout->setContentsMargins(28, 28, 28, 24);
    layout->setSpacing(18);

    auto *header = new QWidget(card);
    auto *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->setSpacing(16);

    auto *iconBadge = new QLabel(header);
    iconBadge->setFixedSize(60, 60);
    iconBadge->setAlignment(Qt::AlignCenter);
    iconBadge->setPixmap(IconHelper::draw(IconGlyph::Smartphone, QSize(30, 30), Qt::white));
    iconBadge->setStyleSheet(QString(
        "QLabel {"
        "    border-radius: 20px;"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1, stop:0 #0A84FF, stop:1 #0051C7);"
        "    box-shadow: 0px 20px 40px rgba(10,132,255,0.18);"
        "}"));

    auto *infoContainer = new QWidget(header);
    auto *infoLayout = new QVBoxLayout(infoContainer);
    infoLayout->setContentsMargins(0, 0, 0, 0);
    infoLayout->setSpacing(6);
    infoLayout->addWidget(createTitleLabel(info.name, 20));
    infoLayout->addWidget(createSecondaryLabel(info.os, 13, 0.58));

    headerLayout->addWidget(iconBadge, 0, Qt::AlignTop);
    headerLayout->addWidget(infoContainer, 1);
    headerLayout->addWidget(createStatusBadge(info.online));

    layout->addWidget(header);

    auto *meta = new QWidget(card);
    auto *metaLayout = new QVBoxLayout(meta);
    metaLayout->setContentsMargins(0, 0, 0, 0);
    metaLayout->setSpacing(8);
    metaLayout->addWidget(createSecondaryLabel(tr("最近活跃"), 12, 0.58));
    metaLayout->addWidget(createTitleLabel(info.lastActive, 16, false));

    layout->addWidget(meta);

    auto *footer = new QWidget(card);
    auto *footerLayout = new QHBoxLayout(footer);
    footerLayout->setContentsMargins(0, 0, 0, 0);
    footerLayout->setSpacing(12);

    auto buildGhostButton = [&](const QString &text) {
        auto *button = new QPushButton(text, footer);
        button->setCursor(Qt::PointingHandCursor);
        button->setStyleSheet(
            "QPushButton {"
            "    background-color: rgba(255,255,255,0.55);"
            "    border-radius: 14px;"
            "    border: 1px solid rgba(15,23,42,0.06);"
            "    padding: 10px 16px;"
            "    color: rgba(15,23,42,0.85);"
            "    font-size: 13px;"
            "    font-weight: 600;"
            "}" 
            "QPushButton:hover {"
            "    background-color: rgba(10,132,255,0.12);"
            "    border-color: rgba(10,132,255,0.28);"
            "}");
        return button;
    };

    footerLayout->addWidget(buildGhostButton(tr("管理")), 1);

    auto *dangerButton = new QPushButton(footer);
    dangerButton->setCursor(Qt::PointingHandCursor);
    dangerButton->setIcon(QIcon(IconHelper::draw(IconGlyph::Trash, QSize(18, 18), QColor(239, 68, 68))));
    dangerButton->setIconSize(QSize(18, 18));
    dangerButton->setStyleSheet(
        "QPushButton {"
        "    background-color: rgba(239,68,68,0.12);"
        "    border-radius: 14px;"
        "    border: 1px solid rgba(239,68,68,0.2);"
        "    padding: 10px;"
        "}" 
        "QPushButton:hover {"
        "    background-color: rgba(239,68,68,0.18);"
        "}");

    footerLayout->addWidget(dangerButton, 0);

    layout->addWidget(footer);

    return card;
}

QFrame *Devices::buildDeviceCard(const DeviceInfo &info) const
{
    auto *card = createGlassCard("registeredDeviceCard");
    card->setGraphicsEffect(createShadow(card, 38.0, 12.0));

    auto *layout = new QVBoxLayout(card);
    layout->setContentsMargins(28, 28, 28, 24);
    layout->setSpacing(16);

    auto *header = new QWidget(card);
    auto *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->setSpacing(16);

    auto *iconBadge = new QLabel(header);
    iconBadge->setFixedSize(60, 60);
    iconBadge->setAlignment(Qt::AlignCenter);
    iconBadge->setPixmap(IconHelper::draw(IconGlyph::Monitor, QSize(30, 30), Qt::white));
    iconBadge->setStyleSheet(QString(
        "QLabel {"
        "    border-radius: 20px;"
        "    background: %1;"
        "}" )
        .arg(info.online
                 ? "qlineargradient(x1:0,y1:0,x2:1,y2:1, stop:0 #0A84FF, stop:1 #0051C7)"
                 : "rgba(148,163,184,0.45)"));

    auto *infoContainer = new QWidget(header);
    auto *infoLayout = new QVBoxLayout(infoContainer);
    infoLayout->setContentsMargins(0, 0, 0, 0);
    infoLayout->setSpacing(6);
    infoLayout->addWidget(createTitleLabel(info.name, 20));
    infoLayout->addWidget(createSecondaryLabel(info.os, 13, 0.58));

    headerLayout->addWidget(iconBadge, 0, Qt::AlignTop);
    headerLayout->addWidget(infoContainer, 1);
    headerLayout->addWidget(createStatusBadge(info.online));

    layout->addWidget(header);

    auto addRow = [&](const QString &caption, const QString &value, qreal opacity, bool monospace = false) {
        auto *rowWidget = new QWidget(card);
        auto *rowLayout = new QHBoxLayout(rowWidget);
        rowLayout->setContentsMargins(0, 0, 0, 0);
        rowLayout->setSpacing(12);
        rowLayout->addWidget(createSecondaryLabel(caption, 12, opacity));
        auto *valueLabel = new QLabel(value, rowWidget);
        valueLabel->setStyleSheet(QString(
            "QLabel {"
            "    color: rgba(15,23,42,0.9);"
            "    font-size: 14px;"
            "    font-weight: 600;"
            "    %1"
            "}" ).arg(monospace ? "font-family: 'SFMono-Regular','Consolas','Courier New';" : ""));
        rowLayout->addWidget(valueLabel, 1, Qt::AlignRight);
        return rowWidget;
    };

    layout->addWidget(addRow(tr("IP地址"), info.ip, 0.55, true));
    layout->addWidget(addRow(tr("最后连接"), info.lastSeen, 0.55));

    if (info.online) {
        layout->addWidget(addRow(tr("网络模式"), info.networkMode, 0.55));
        layout->addWidget(addRow(tr("延迟"), info.latency, 0.55));
    }

    auto *footer = new QWidget(card);
    auto *footerLayout = new QHBoxLayout(footer);
    footerLayout->setContentsMargins(0, 8, 0, 0);
    footerLayout->setSpacing(12);

    auto *manageButton = new QPushButton(tr("管理"), footer);
    manageButton->setCursor(Qt::PointingHandCursor);
    manageButton->setStyleSheet(
        "QPushButton {"
        "    background-color: rgba(255,255,255,0.55);"
        "    border-radius: 14px;"
        "    border: 1px solid rgba(15,23,42,0.06);"
        "    padding: 10px 16px;"
        "    color: rgba(15,23,42,0.85);"
        "    font-size: 13px;"
        "    font-weight: 600;"
        "}" 
        "QPushButton:hover {"
        "    background-color: rgba(10,132,255,0.12);"
        "    border-color: rgba(10,132,255,0.28);"
        "}");

    auto *removeButton = new QPushButton(footer);
    removeButton->setCursor(Qt::PointingHandCursor);
    removeButton->setIcon(QIcon(IconHelper::draw(IconGlyph::Trash, QSize(18, 18), QColor(239, 68, 68))));
    removeButton->setIconSize(QSize(18, 18));
    removeButton->setStyleSheet(
        "QPushButton {"
        "    background-color: rgba(239,68,68,0.12);"
        "    border-radius: 14px;"
        "    border: 1px solid rgba(239,68,68,0.2);"
        "    padding: 10px;"
        "}" 
        "QPushButton:hover {"
        "    background-color: rgba(239,68,68,0.18);"
        "}");

    footerLayout->addWidget(manageButton, 1);
    footerLayout->addWidget(removeButton, 0);

    layout->addWidget(footer);

    return card;
}
