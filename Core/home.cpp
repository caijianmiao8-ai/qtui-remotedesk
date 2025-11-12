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

Home::Home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);
    setStyleSheet("background: transparent;");

    // 完全重新构建布局
    buildCompleteLayout();
}

Home::~Home()
{
    delete ui;
}

void Home::buildCompleteLayout()
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
    scrollArea->setStyleSheet(
        "QScrollArea { background: transparent; border: none; }"
        "QScrollBar:vertical {"
        "    background: transparent; width: 4px; margin: 0;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: rgba(0,0,0,0.18); border-radius: 2px; min-height: 20px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "    background: rgba(0,0,0,0.36);"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    height: 0px;"
        "}"
    );

    // 创建滚动内容容器
    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background: transparent;");
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(32, 20, 32, 32);  // p-8 = 32px
    contentLayout->setSpacing(0);

    // 1. 添加标题区域
    contentLayout->addWidget(createHeaderSection());
    contentLayout->addSpacing(16);  // mb-4 = 16px

    // 2. 添加提示卡片
    contentLayout->addWidget(createTipCard());
    contentLayout->addSpacing(32);  // mb-8 = 32px

    // 3. 添加统计卡片
    contentLayout->addWidget(createStatsSection());
    contentLayout->addSpacing(24);  // mb-6 = 24px

    // 4. 添加本机信息卡片
    contentLayout->addWidget(createMachineInfoCard());
    contentLayout->addSpacing(24);  // mb-6 = 24px

    // 5. 添加快速操作卡片
    contentLayout->addWidget(createQuickActionsCard());

    contentLayout->addStretch(1);

    scrollArea->setWidget(contentWidget);

    // 设置主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(scrollArea);
}

QWidget* Home::createHeaderSection()
{
    QWidget *header = new QWidget();
    header->setStyleSheet("background: transparent;");
    QVBoxLayout *layout = new QVBoxLayout(header);
    layout->setContentsMargins(0, 20, 0, 0);
    layout->setSpacing(8);  // mb-2 = 8px

    // 主标题
    QLabel *title = new QLabel("欢迎回来");
    title->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 36px;"          // text-4xl
        "    font-weight: 600;"          // font-semibold
        "    background: transparent;"
        "}"
    );

    // 副标题
    QLabel *subtitle = new QLabel("此电脑已准备好被远程接管（被控端）");
    subtitle->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"           // text-secondary
        "    font-size: 14px;"
        "    background: transparent;"
        "}"
    );

    layout->addWidget(title);
    layout->addWidget(subtitle);

    return header;
}

QWidget* Home::createTipCard()
{
    QWidget *card = new QWidget();
    card->setStyleSheet(
        "QWidget {"
        "    background: rgba(255, 255, 255, 0.7);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 20px;"
        "}"
    );

    // 添加阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(60);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 30);
    card->setGraphicsEffect(shadow);

    QHBoxLayout *layout = new QHBoxLayout(card);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(12);

    // 图标容器
    QWidget *iconContainer = new QWidget();
    iconContainer->setFixedSize(32, 32);
    iconContainer->setStyleSheet(
        "QWidget {"
        "    background: rgba(10, 132, 255, 0.12);"
        "    border-radius: 14px;"
        "}"
    );

    // 图标（使用文字代替，实际应该用 SVG 图标）
    QLabel *icon = new QLabel("ℹ️", iconContainer);
    icon->setGeometry(0, 0, 32, 32);
    icon->setAlignment(Qt::AlignCenter);
    icon->setStyleSheet("background: transparent; color: #0A84FF; font-size: 16px;");

    // 提示文本
    QLabel *text = new QLabel("提示：请在手机端使用同一账号登录，即可从手机远程接管本电脑。");
    text->setWordWrap(true);
    text->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 12px;"
        "    line-height: 1.5;"
        "    background: transparent;"
        "}"
    );

    layout->addWidget(iconContainer);
    layout->addWidget(text, 1);

    return card;
}

QWidget* Home::createStatsSection()
{
    QWidget *section = new QWidget();
    section->setStyleSheet("background: transparent;");
    QHBoxLayout *layout = new QHBoxLayout(section);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(24);  // gap-6 = 24px

    // 在线设备统计卡片
    QWidget *statCard = new QWidget();
    statCard->setFixedSize(250, 140);
    statCard->setStyleSheet(
        "QWidget {"
        "    background: rgba(255, 255, 255, 0.7);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 20px;"
        "}"
    );

    // 添加阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(60);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 30);
    statCard->setGraphicsEffect(shadow);

    QVBoxLayout *cardLayout = new QVBoxLayout(statCard);
    cardLayout->setContentsMargins(24, 24, 24, 24);
    cardLayout->setSpacing(12);

    // 图标容器（橙色）
    QWidget *iconBg = new QWidget();
    iconBg->setFixedSize(48, 48);
    iconBg->setStyleSheet(
        "QWidget {"
        "    background: rgba(249, 115, 22, 0.1);"
        "    border-radius: 14px;"
        "}"
    );

    QLabel *icon = new QLabel("🖥️", iconBg);
    icon->setGeometry(0, 0, 48, 48);
    icon->setAlignment(Qt::AlignCenter);
    icon->setStyleSheet("background: transparent; font-size: 24px;");

    // 标签
    QLabel *label = new QLabel("在线设备");
    label->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 14px;"
        "    background: transparent;"
        "}"
    );

    // 数值
    QLabel *value = new QLabel("4");
    value->setStyleSheet(
        "QLabel {"
        "    color: #f97316;"           // text-orange-400
        "    font-size: 30px;"
        "    font-weight: 600;"
        "    background: transparent;"
        "}"
    );

    cardLayout->addWidget(iconBg);
    cardLayout->addWidget(label);
    cardLayout->addWidget(value);
    cardLayout->addStretch();

    layout->addWidget(statCard);
    layout->addStretch(1);

    return section;
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

    // 添加阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(60);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 30);
    card->setGraphicsEffect(shadow);

    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(32, 32, 32, 32);  // p-8 = 32px
    layout->setSpacing(24);  // gap-6 = 24px

    // 标题
    QLabel *title = new QLabel("本机信息");
    title->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 24px;"           // text-2xl
        "    font-weight: 600;"          // font-semibold
        "    background: transparent;"
        "}"
    );
    layout->addWidget(title);

    // 信息网格
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setHorizontalSpacing(24);
    gridLayout->setVerticalSpacing(24);

    // 设备名称
    gridLayout->addWidget(createInfoItem("设备名称", "我的工作电脑"), 0, 0);

    // 设备ID
    gridLayout->addWidget(createInfoItem("设备ID", "RD-2024-10241502"), 0, 1);

    // 本机IP
    gridLayout->addWidget(createInfoItem("本机IP", "192.168.1.100"), 1, 0);

    // 网络状态
    gridLayout->addWidget(createNetworkStatusItem(), 1, 1);

    layout->addLayout(gridLayout);

    return card;
}

QWidget* Home::createInfoItem(const QString &label, const QString &value)
{
    QWidget *item = new QWidget();
    item->setStyleSheet("background: transparent;");
    QVBoxLayout *layout = new QVBoxLayout(item);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(8);

    QLabel *labelWidget = new QLabel(label);
    labelWidget->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 14px;"
        "    background: transparent;"
        "}"
    );

    QLabel *valueWidget = new QLabel(value);
    valueWidget->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 18px;"
        "    font-weight: 500;"
        "    background: transparent;"
        "}"
    );

    layout->addWidget(labelWidget);
    layout->addWidget(valueWidget);

    return item;
}

QWidget* Home::createNetworkStatusItem()
{
    QWidget *item = new QWidget();
    item->setStyleSheet("background: transparent;");
    QVBoxLayout *layout = new QVBoxLayout(item);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(8);

    QLabel *label = new QLabel("网络状态");
    label->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 14px;"
        "    background: transparent;"
        "}"
    );

    // 状态容器
    QWidget *statusWidget = new QWidget();
    statusWidget->setStyleSheet("background: transparent;");
    QHBoxLayout *statusLayout = new QHBoxLayout(statusWidget);
    statusLayout->setContentsMargins(0, 0, 0, 0);
    statusLayout->setSpacing(8);

    // 绿色指示点
    QWidget *indicator = new QWidget();
    indicator->setFixedSize(10, 10);
    indicator->setStyleSheet(
        "QWidget {"
        "    background: #22c55e;"      // green-400
        "    border-radius: 5px;"
        "}"
    );

    // 状态文本
    QLabel *status = new QLabel("局域网在线");
    status->setStyleSheet(
        "QLabel {"
        "    color: #22c55e;"
        "    font-size: 18px;"
        "    font-weight: 500;"
        "    background: transparent;"
        "}"
    );

    statusLayout->addWidget(indicator);
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

    // 添加阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(60);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 30);
    card->setGraphicsEffect(shadow);

    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(24, 24, 24, 24);  // p-6 = 24px
    layout->setSpacing(16);

    // 标题
    QLabel *title = new QLabel("快速操作");
    title->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 18px;"          // text-lg
        "    font-weight: 600;"         // font-semibold
        "    background: transparent;"
        "}"
    );
    layout->addWidget(title);

    // 操作按钮网格
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setSpacing(16);  // gap-4 = 16px

    buttonsLayout->addWidget(createActionButton("设备管理", "查看已注册设备", "🖥️"));
    buttonsLayout->addWidget(createActionButton("系统设置", "配置参数", "⚙️"));

    layout->addLayout(buttonsLayout);

    return card;
}

QWidget* Home::createActionButton(const QString &title, const QString &description, const QString &icon)
{
    QPushButton *button = new QPushButton();
    button->setCursor(Qt::PointingHandCursor);
    button->setFixedHeight(120);
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
    );

    // 创建按钮内容
    QVBoxLayout *layout = new QVBoxLayout(button);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    layout->setSpacing(8);

    QLabel *iconLabel = new QLabel(icon);
    iconLabel->setStyleSheet("background: transparent; color: #0A84FF; font-size: 24px;");

    QLabel *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 16px;"
        "    font-weight: 500;"
        "    background: transparent;"
        "}"
    );

    QLabel *descLabel = new QLabel(description);
    descLabel->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 14px;"
        "    background: transparent;"
        "}"
    );

    layout->addWidget(iconLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(descLabel);
    layout->addStretch();

    return button;
}
