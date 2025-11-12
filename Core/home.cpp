#include "home.h"
#include "ui_home.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QFrame>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

Home::Home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home),
    m_networkIndicator(nullptr)
{
    ui->setupUi(this);
    setStyleSheet("background: transparent;");

    // 完全重建布局
    buildLayout();
}

Home::~Home()
{
    delete ui;
}

void Home::buildLayout()
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
        "    border-radius: 999px;"
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

    // 内容容器 - 实现 max-w-6xl (1152px) 限制
    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background: transparent;");

    // 外层容器：用于实现 max-width 和水平居中
    QHBoxLayout *outerLayout = new QHBoxLayout(contentWidget);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->setSpacing(0);

    // 左侧弹性空间
    outerLayout->addStretch(1);

    // 中间内容区域 (max-width: 1152px)
    QWidget *innerContent = new QWidget();
    innerContent->setStyleSheet("background: transparent;");
    innerContent->setMaximumWidth(1152);  // max-w-6xl = 1152px

    QVBoxLayout *contentLayout = new QVBoxLayout(innerContent);
    // p-8 = 32px, mt-5 = 20px
    contentLayout->setContentsMargins(32, 20, 32, 32);
    contentLayout->setSpacing(0);
    contentLayout->setAlignment(Qt::AlignTop);

    // 1. 标题区 (mb-2 = 8px, mb-4 = 16px)
    contentLayout->addWidget(createHeader());
    contentLayout->addSpacing(16);  // mb-4

    // 2. 提示卡片 (mb-8 = 32px)
    contentLayout->addWidget(createPairingHintCard());
    contentLayout->addSpacing(32);  // mb-8

    // 3. 统计卡片网格 (mb-8 = 32px)
    contentLayout->addWidget(createStatsGrid());
    contentLayout->addSpacing(32);  // mb-8

    // 4. 本机信息卡片 (mb-6 = 24px)
    contentLayout->addWidget(createMachineInfoCard());
    contentLayout->addSpacing(24);  // mb-6

    // 5. 快速操作卡片
    contentLayout->addWidget(createQuickActionsCard());

    // 底部弹性空间
    contentLayout->addStretch(1);

    // 添加内容区域到外层布局
    outerLayout->addWidget(innerContent);

    // 右侧弹性空间
    outerLayout->addStretch(1);

    scrollArea->setWidget(contentWidget);

    // 设置主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(scrollArea);
}

QWidget* Home::createHeader()
{
    QWidget *header = new QWidget();
    header->setStyleSheet("background: transparent;");

    QVBoxLayout *layout = new QVBoxLayout(header);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(8);  // mb-2 = 8px

    // 主标题: text-4xl = 36px, font-semibold = 600
    QLabel *title = new QLabel("欢迎回来");
    title->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 36px;"
        "    font-weight: 600;"
        "    line-height: 1.2;"
        "    font-family: 'Segoe UI', 'PingFang SC', 'Microsoft YaHei', Arial, sans-serif;"
        "    background: transparent;"
        "}"
    );

    // 副标题: text-base = 16px
    QLabel *subtitle = new QLabel("此电脑已准备好被远程接管（被控端）");
    subtitle->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 16px;"
        "    line-height: 1.5;"
        "    font-family: 'Segoe UI', 'PingFang SC', 'Microsoft YaHei', Arial, sans-serif;"
        "    background: transparent;"
        "}"
    );

    layout->addWidget(title);
    layout->addWidget(subtitle);

    return header;
}

QWidget* Home::createPairingHintCard()
{
    QWidget *card = new QWidget();
    card->setStyleSheet(
        "QWidget {"
        "    background: rgba(255, 255, 255, 0.7);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 20px;"
        "}"
    );

    // 阴影: shadow-[0_30px_60px_rgba(0,0,0,0.06)]
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(60);
    shadow->setColor(QColor(0, 0, 0, 15));  // 0.06 * 255 ≈ 15
    shadow->setOffset(0, 30);
    card->setGraphicsEffect(shadow);

    QHBoxLayout *layout = new QHBoxLayout(card);
    layout->setContentsMargins(16, 16, 16, 16);  // p-4 = 16px
    layout->setSpacing(12);  // gap-3 = 12px

    // 图标容器: w-8 h-8 = 32x32px, rounded-[14px]
    QWidget *iconContainer = new QWidget();
    iconContainer->setFixedSize(32, 32);
    iconContainer->setStyleSheet(
        "QWidget {"
        "    background: rgba(10, 132, 255, 0.12);"
        "    border-radius: 14px;"
        "}"
    );

    // 图标: size={16}
    QLabel *icon = new QLabel("ℹ️", iconContainer);
    icon->setGeometry(0, 0, 32, 32);
    icon->setAlignment(Qt::AlignCenter);
    icon->setStyleSheet("background: transparent; font-size: 16px;");

    // 文本: text-[12px], leading-relaxed
    QLabel *text = new QLabel("提示：请在手机端使用同一账号登录，即可从手机远程接管本电脑。");
    text->setWordWrap(true);
    text->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 12px;"
        "    line-height: 1.625;"  // leading-relaxed
        "    background: transparent;"
        "}"
    );

    layout->addWidget(iconContainer);
    layout->addWidget(text, 1);

    return card;
}

QWidget* Home::createStatsGrid()
{
    QWidget *grid = new QWidget();
    grid->setStyleSheet("background: transparent;");

    // React: grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4 gap-6
    // 使用 QHBoxLayout 实现水平网格布局
    QHBoxLayout *layout = new QHBoxLayout(grid);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(24);  // gap-6 = 24px

    // 1. 在线设备 (橙色, Monitor 图标)
    layout->addWidget(createStatCard("在线设备", "4", "🖥️", "#fb923c", "rgba(249, 115, 22, 0.1)"));

    // 2. 设备总数 (蓝色, Grid 图标)
    layout->addWidget(createStatCard("设备总数", "8", "📱", "#3b82f6", "rgba(59, 130, 246, 0.1)"));

    // 3. 今日连接 (绿色, Activity 图标)
    layout->addWidget(createStatCard("今日连接", "15", "📊", "#22c55e", "rgba(34, 197, 94, 0.1)"));

    // 4. 平均延迟 (紫色, Zap 图标)
    layout->addWidget(createStatCard("平均延迟", "8ms", "⚡", "#a855f7", "rgba(168, 85, 247, 0.1)"));

    return grid;
}

QWidget* Home::createStatCard(const QString &labelText, const QString &valueText,
                               const QString &iconText, const QString &valueColor,
                               const QString &iconBgColor)
{
    QWidget *card = new QWidget();
    card->setStyleSheet(
        "QWidget {"
        "    background: rgba(255, 255, 255, 0.7);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 20px;"
        "}"
    );

    // 阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(60);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 30);
    card->setGraphicsEffect(shadow);

    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(24, 24, 24, 24);  // p-6 = 24px
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignTop);

    // 图标容器: w-12 h-12 = 48x48px, rounded-[14px], mb-3 = 12px
    QWidget *iconBg = new QWidget();
    iconBg->setFixedSize(48, 48);
    iconBg->setStyleSheet(
        QString("QWidget {"
        "    background: %1;"
        "    border-radius: 14px;"
        "}").arg(iconBgColor)
    );

    QLabel *icon = new QLabel(iconText, iconBg);
    icon->setGeometry(0, 0, 48, 48);
    icon->setAlignment(Qt::AlignCenter);
    icon->setStyleSheet("background: transparent; font-size: 24px;");

    layout->addWidget(iconBg);
    layout->addSpacing(12);  // mb-3

    // 标签: text-sm = 14px, mb-1 = 4px
    QLabel *label = new QLabel(labelText);
    label->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 14px;"
        "    line-height: 1.4;"
        "    font-family: 'Segoe UI', 'PingFang SC', 'Microsoft YaHei', Arial, sans-serif;"
        "    background: transparent;"
        "}"
    );

    layout->addWidget(label);
    layout->addSpacing(4);  // mb-1

    // 数值: text-3xl = 30px, font-semibold = 600
    QLabel *value = new QLabel(valueText);
    value->setStyleSheet(
        QString("QLabel {"
        "    color: %1;"
        "    font-size: 30px;"
        "    font-weight: 600;"
        "    line-height: 1.2;"
        "    font-family: 'Segoe UI', 'PingFang SC', 'Microsoft YaHei', Arial, sans-serif;"
        "    background: transparent;"
        "}").arg(valueColor)
    );

    layout->addWidget(value);
    layout->addStretch(1);

    return card;
}

QWidget* Home::createMachineInfoCard()
{
    QWidget *card = new QWidget();
    card->setStyleSheet(
        "QWidget {"
        "    background: rgba(255, 255, 255, 0.7);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 20px;"
        "}"
    );

    // 阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(60);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 30);
    card->setGraphicsEffect(shadow);

    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(32, 32, 32, 32);  // p-8 = 32px
    layout->setSpacing(0);

    // 标题: text-2xl = 24px, font-semibold = 600, mb-6 = 24px
    QLabel *title = new QLabel("本机信息");
    title->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 24px;"
        "    font-weight: 600;"
        "    line-height: 1.3;"
        "    font-family: 'Segoe UI', 'PingFang SC', 'Microsoft YaHei', Arial, sans-serif;"
        "    background: transparent;"
        "}"
    );

    layout->addWidget(title);
    layout->addSpacing(24);  // mb-6

    // 信息网格: grid grid-cols-2, gap-6 = 24px
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setHorizontalSpacing(24);  // gap-6
    gridLayout->setVerticalSpacing(24);    // gap-6
    gridLayout->setContentsMargins(0, 0, 0, 0);

    // 第一行
    gridLayout->addWidget(createInfoItem("设备名称", "我的工作电脑", false), 0, 0);
    gridLayout->addWidget(createInfoItem("设备ID", "RD-2024-10241502", true), 0, 1);

    // 第二行
    gridLayout->addWidget(createInfoItem("本机IP", "192.168.1.100", true), 1, 0);
    gridLayout->addWidget(createNetworkStatusItem(), 1, 1);

    layout->addLayout(gridLayout);

    return card;
}

QWidget* Home::createInfoItem(const QString &labelText, const QString &valueText, bool mono)
{
    QWidget *item = new QWidget();
    item->setStyleSheet("background: transparent;");

    QVBoxLayout *layout = new QVBoxLayout(item);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(8);  // mb-2 = 8px
    layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // 标签: text-sm = 14px
    QLabel *label = new QLabel(labelText);
    label->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 14px;"
        "    line-height: 1.4;"
        "    font-family: 'Segoe UI', 'PingFang SC', 'Microsoft YaHei', Arial, sans-serif;"
        "    background: transparent;"
        "}"
    );

    // 数值: text-lg = 18px, font-medium = 500
    QLabel *value = new QLabel(valueText);
    QString fontFamily = mono ? "font-family: 'Courier New', monospace;" : "font-family: 'Segoe UI', 'PingFang SC', 'Microsoft YaHei', Arial, sans-serif;";
    value->setStyleSheet(
        QString("QLabel {"
        "    color: #1e293b;"
        "    font-size: 18px;"
        "    font-weight: 500;"
        "    line-height: 1.4;"
        "    %1"
        "    background: transparent;"
        "}").arg(fontFamily)
    );

    layout->addWidget(label);
    layout->addWidget(value);

    return item;
}

QWidget* Home::createNetworkStatusItem()
{
    QWidget *item = new QWidget();
    item->setStyleSheet("background: transparent;");

    QVBoxLayout *layout = new QVBoxLayout(item);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(8);  // mb-2 = 8px
    layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // 标签
    QLabel *label = new QLabel("网络状态");
    label->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 14px;"
        "    line-height: 1.4;"
        "    font-family: 'Segoe UI', 'PingFang SC', 'Microsoft YaHei', Arial, sans-serif;"
        "    background: transparent;"
        "}"
    );

    // 状态容器
    QWidget *statusWidget = new QWidget();
    statusWidget->setStyleSheet("background: transparent;");

    QHBoxLayout *statusLayout = new QHBoxLayout(statusWidget);
    statusLayout->setContentsMargins(0, 0, 0, 0);
    statusLayout->setSpacing(8);  // gap-2 = 8px

    // 指示点: w-2.5 h-2.5 = 10x10px, bg-green-400 = #4ade80, rounded-full, animate-pulse
    m_networkIndicator = new QWidget();
    m_networkIndicator->setFixedSize(10, 10);
    m_networkIndicator->setStyleSheet(
        "QWidget {"
        "    background: #4ade80;"
        "    border-radius: 5px;"
        "}"
    );

    // Apple风格pulse动画：opacity 1.0 ↔ 0.3
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(m_networkIndicator);
    m_networkIndicator->setGraphicsEffect(opacityEffect);

    QPropertyAnimation *pulseAnimation = new QPropertyAnimation(opacityEffect, "opacity");
    pulseAnimation->setDuration(1500);  // 1.5秒周期
    pulseAnimation->setStartValue(1.0);
    pulseAnimation->setKeyValueAt(0.5, 0.3);  // 中间降到0.3
    pulseAnimation->setEndValue(1.0);
    pulseAnimation->setEasingCurve(QEasingCurve::InOutSine);  // 平滑呼吸效果
    pulseAnimation->setLoopCount(-1);  // 无限循环
    pulseAnimation->start();

    // 状态文本: text-lg = 18px, font-medium = 500, text-green-400 = #4ade80
    QLabel *status = new QLabel("局域网在线");
    status->setStyleSheet(
        "QLabel {"
        "    color: #4ade80;"
        "    font-size: 18px;"
        "    font-weight: 500;"
        "    line-height: 1.4;"
        "    font-family: 'Segoe UI', 'PingFang SC', 'Microsoft YaHei', Arial, sans-serif;"
        "    background: transparent;"
        "}"
    );

    statusLayout->addWidget(m_networkIndicator);
    statusLayout->addWidget(status);
    statusLayout->addStretch();

    layout->addWidget(label);
    layout->addWidget(statusWidget);

    return item;
}

QWidget* Home::createQuickActionsCard()
{
    QWidget *card = new QWidget();
    card->setStyleSheet(
        "QWidget {"
        "    background: rgba(255, 255, 255, 0.7);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 20px;"
        "}"
    );

    // 阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(60);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 30);
    card->setGraphicsEffect(shadow);

    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(24, 24, 24, 24);  // p-6 = 24px
    layout->setSpacing(0);

    // 标题: text-lg = 18px, font-semibold = 600, mb-4 = 16px
    QLabel *title = new QLabel("快速操作");
    title->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 18px;"
        "    font-weight: 600;"
        "    line-height: 1.4;"
        "    font-family: 'Segoe UI', 'PingFang SC', 'Microsoft YaHei', Arial, sans-serif;"
        "    background: transparent;"
        "}"
    );

    layout->addWidget(title);
    layout->addSpacing(16);  // mb-4

    // 按钮网格: grid grid-cols-2, gap-4 = 16px
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsLayout->setSpacing(16);  // gap-4

    buttonsLayout->addWidget(createActionButton("设备管理", "查看已注册设备", "🖥️"));
    buttonsLayout->addWidget(createActionButton("系统设置", "配置参数", "⚙️"));

    layout->addLayout(buttonsLayout);

    return card;
}

QWidget* Home::createActionButton(const QString &titleText, const QString &descText, const QString &icon)
{
    QPushButton *button = new QPushButton();
    button->setCursor(Qt::PointingHandCursor);
    button->setMinimumHeight(100);
    button->setStyleSheet(
        "QPushButton {"
        "    background: rgba(255, 255, 255, 0.6);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 14px;"
        "    text-align: left;"
        "    padding: 16px;"
        "}"
        "QPushButton:hover {"
        "    background: rgba(0, 0, 0, 0.03);"
        "}"
        "QPushButton:pressed {"
        "    background: rgba(0, 0, 0, 0.05);"
        "}"
    );

    // 按钮内容布局
    QVBoxLayout *layout = new QVBoxLayout(button);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(8);  // gap-2 = 8px
    layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // 图标: size = 24px, mb-2 = 8px
    QLabel *iconLabel = new QLabel(icon);
    iconLabel->setStyleSheet(
        "QLabel {"
        "    color: #0A84FF;"
        "    font-size: 24px;"
        "    background: transparent;"
        "}"
    );

    // 标题: font-medium
    QLabel *titleLabel = new QLabel(titleText);
    titleLabel->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 14px;"
        "    font-weight: 500;"
        "    line-height: 1.4;"
        "    font-family: 'Segoe UI', 'PingFang SC', 'Microsoft YaHei', Arial, sans-serif;"
        "    background: transparent;"
        "}"
    );

    // 描述: text-sm = 14px, mt-1 = 4px
    QLabel *descLabel = new QLabel(descText);
    descLabel->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 14px;"
        "    line-height: 1.5;"
        "    font-family: 'Segoe UI', 'PingFang SC', 'Microsoft YaHei', Arial, sans-serif;"
        "    background: transparent;"
        "}"
    );

    layout->addWidget(iconLabel);
    layout->addSpacing(8);  // mb-2
    layout->addWidget(titleLabel);
    layout->addSpacing(4);  // mt-1
    layout->addWidget(descLabel);
    layout->addStretch();

    return button;
}
