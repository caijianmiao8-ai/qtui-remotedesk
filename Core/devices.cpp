#include "devices.h"
#include "ui_devices.h"
#include <QDebug>

Devices::Devices(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Devices)
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
    // 超浅色透明滚动条设置
    ui->scrollArea->setStyleSheet(
        "QScrollArea {"
        "    border: none;"
        "    background-color: transparent;"
        "}"
        "QScrollBar:vertical {"
        "    background: transparent;"  // 垂直滚动条背景透明
        "    width: 8px;"
        "    margin: 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: rgba(0, 0, 0, 0.15);"  // 更浅的颜色，透明度降低
        "    border-radius: 4px;"
        "    min-height: 20px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "    background: rgba(0, 0, 0, 0.25);"  // 悬停时稍微加深
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    border: none;"
        "    background: none;"
        "    height: 0px;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: transparent;"  // 滑块前后区域也透明
        "}"
        "QScrollBar:horizontal {"
        "    background: transparent;"  // 水平滚动条背景透明
        "    height: 8px;"
        "    margin: 0px;"
        "}"
        "QScrollBar::handle:horizontal {"
        "    background: rgba(0, 0, 0, 0.15);"  // 更浅的颜色，透明度降低
        "    border-radius: 4px;"
        "    min-width: 20px;"
        "}"
        "QScrollBar::handle:horizontal:hover {"
        "    background: rgba(0, 0, 0, 0.25);"  // 悬停时稍微加深
        "}"
        "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {"
        "    border: none;"
        "    background: none;"
        "    width: 0px;"
        "}"
        "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {"
        "    background: transparent;"  // 滑块前后区域也透明
        "}");

    setupHomeLayout();
    setupHomeHeader();
    setupWidget2();
    setupWidget3();
}

void Devices::setupHomeLayout()
{
    // 获取包含所有 widget 的父布局
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
    if (!mainLayout) return;

    // 清除现有内容
    QLayoutItem *child;
    while ((child = mainLayout->takeAt(0)) != nullptr) {
        delete child;
    }

    // 重新添加 widget 和间隔
    mainLayout->addWidget(ui->widget_1);
    mainLayout->addSpacing(0);  // widget_1 和 widget_2 之间的间距
    mainLayout->addWidget(ui->widget_2);
    mainLayout->addSpacing(25);  // widget_2 和 widget_3 之间的间距
    mainLayout->addWidget(ui->widget_3);
    mainLayout->addStretch(1);   // 底部弹性空间
}

void Devices::setupHomeHeader()
{
    // 清除现有布局
    if (ui->widget_1->layout()) {
        delete ui->widget_1->layout();
    }

    // 创建新的垂直布局
    QVBoxLayout *layout = new QVBoxLayout(ui->widget_1);
    layout->setContentsMargins(0, 50, 0, 18);  // 上边距，让内容离顶部远

    // 设置 Welcome back 标签
    ui->label->setText("Devices");
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

    // 设置描述标签
    ui->label_2->setText("All devices registered under this account. This desktop acts as a controlled host only (Phase 1).");
    ui->label_2->setStyleSheet(
        "QLabel {"
        "    color: #666666;"
        "    font-size: 16px;"
        "    font-weight: normal;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background-color: transparent;"
        "    border: none;"
        "    margin: 0;"
        "    padding: 0;"
        "}");

    // 添加标签到布局，使用很小的间距
    layout->addWidget(ui->label);
    layout->addSpacing(0);  // 3px间距，让两个标签很近
    layout->addWidget(ui->label_2);
}

void Devices::setupWidget2()
{
    ui->widget_2->setStyleSheet(
        "QWidget#widget_2 {"
        "    background-color: #ffffff;"
        "    border-radius: 15px;"
        "    border: none;"
        "}");

    // 创建主阴影效果（底部阴影）
    QGraphicsDropShadowEffect *bottomShadow = new QGraphicsDropShadowEffect(this);
    bottomShadow->setBlurRadius(28);
    bottomShadow->setColor(QColor(0, 0, 0, 15));
    bottomShadow->setXOffset(0);
    bottomShadow->setYOffset(8);  // 主要向下偏移

    // 创建轻微的顶部阴影
    QGraphicsDropShadowEffect *topShadow = new QGraphicsDropShadowEffect(this);
    topShadow->setBlurRadius(15);
    topShadow->setColor(QColor(0, 0, 0, 15));
    topShadow->setXOffset(0);
    topShadow->setYOffset(2);     // 轻微的向上偏移

    // 应用阴影效果
    ui->widget_2->setGraphicsEffect(bottomShadow);

    if (!ui->widget_2->layout()) {
        QHBoxLayout *layout = new QHBoxLayout(ui->widget_2);
        layout->setContentsMargins(20, 12, 15, 20);
        layout->setSpacing(12);
    }

    setupIconLabel();
    setupTipLabel();

    QHBoxLayout *layout = qobject_cast<QHBoxLayout*>(ui->widget_2->layout());
    if (layout && layout->count() == 0) {
        layout->addWidget(ui->label_3);
        layout->addWidget(ui->label_4, 1);
    }
}

void Devices::setupIconLabel()
{
    // 设置图标 - 使用你的图标路径
    QPixmap iconPixmap(":/qss/icon/logo_04.png");  // 替换为你的图标路径
    iconPixmap = iconPixmap.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_3->setPixmap(iconPixmap);
    ui->label_3->setScaledContents(true);
    ui->label_3->setFixedSize(24, 24);  // 固定图标大小

    // 图标标签样式
    ui->label_3->setStyleSheet(
        "QLabel {"
        "    background-color: transparent;"
        "    border: none;"
        "    margin: 0;"
        "    padding: 0;"
        "}");
}

void Devices::setupTipLabel()
{
    // 设置提示文字
    ui->label_4->setText("Tip: Sign in with the same account on your phone to remotely control this computer.");

    // 设置文字样式
    ui->label_4->setStyleSheet(
        "QLabel {"
        "    color: #555555;"           // 深灰色文字
        "    font-size: 13px;"          // 稍小的字体
        "    font-weight: normal;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background-color: transparent;"
        "    border: none;"
        "    margin: 0;"
        "    padding: 0;"
        "    line-height: 1.4;"         // 行高，改善多行文本阅读
        "}");

    // 允许文字换行
    ui->label_4->setWordWrap(true);
    ui->label_4->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

void Devices::setupWidget3()
{
    if(ui->widget_3->layout()){
        delete ui->widget_3->layout();
    }

    // 创建新的垂直布局
    QVBoxLayout *layout = new QVBoxLayout(ui->widget_3);
    layout->setContentsMargins(0, 0, 0, 18);

    // 设置标题标签
    ui->label_5->setText("Devices that can control this machine");
    ui->label_5->setStyleSheet(
        "QLabel {"
        "    color: #000000;"
        "    font-size: 20px;"
        "    font-weight: bold;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background-color: transparent;"
        "    border: none;"
        "    margin: 0;"
        "    padding: 0;"
        "}");

    // 设置描述标签
    ui->label_6->setText("Phones / tablets logged into the same account can take remote control of this host.");
    ui->label_6->setStyleSheet(
        "QLabel {"
        "    color: #666666;"
        "    font-size: 16px;"
        "    font-weight: normal;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background-color: transparent;"
        "    border: none;"
        "    margin: 0;"
        "    padding: 0;"
        "}");

    // 添加标签到布局
    layout->addWidget(ui->label_5);
    layout->addSpacing(0);
    layout->addWidget(ui->label_6);
    layout->addSpacing(20);  // 增加间距

    // 设置设备卡片区域
    setupDeviceCards();
}

void Devices::setupDeviceCards()
{
    // 创建设备卡片容器
    QWidget *cardsContainer = new QWidget();
    cardsContainer->setObjectName("cardsContainer");
    cardsContainer->setStyleSheet("QWidget#cardsContainer { background-color: transparent; border: none; }");

    // 使用网格布局
    QGridLayout *gridLayout = new QGridLayout(cardsContainer);
    gridLayout->setContentsMargins(0, 0, 0, 10);
    gridLayout->setHorizontalSpacing(50);  // 卡片之间的水平间距
    gridLayout->setVerticalSpacing(20);    // 卡片之间的垂直间距
    gridLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // 模拟设备数据 - 在实际应用中这里应该从数据源获取
    QVector<QString> devices = {
        "iPhone 13 Pro",
        "Samsung Galaxy S22",
        "Samsung Galaxy S23",
        // 可以添加或删除设备来测试不同数量
    };

    // 动态添加设备卡片
    for (int i = 0; i < devices.size(); ++i) {
        QWidget *card = createDeviceCard(devices[i]);

        // 计算网格位置：每行2列
        int row = i / 2;
        int column = i % 2;

        gridLayout->addWidget(card, row, column);
    }

    // 将卡片容器添加到 widget_3 的布局中
    QVBoxLayout *parentLayout = qobject_cast<QVBoxLayout*>(ui->widget_3->layout());
    if (parentLayout) {
        parentLayout->addWidget(cardsContainer);
    }
}

QWidget* Devices::createDeviceCard(const QString& deviceName, const QString& iconPath)
{
    // 创建卡片容器
    QWidget *card = new QWidget();
    card->setFixedSize(300, 100);  // 固定卡片大小
    card->setObjectName("deviceCard");

    // 卡片样式 - 白色背景，圆角，阴影
    card->setStyleSheet(
        "QWidget#deviceCard {"
        "    background-color: #ffffff;"
        "    border-radius: 15px;"
        "    border: none;"
        "}");

    // 添加阴影效果
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(20);
    shadowEffect->setColor(QColor(0, 0, 0, 25));
    shadowEffect->setXOffset(0);
    shadowEffect->setYOffset(4);
    card->setGraphicsEffect(shadowEffect);

    // 创建卡片内部布局
    QHBoxLayout *cardLayout = new QHBoxLayout(card);
    cardLayout->setContentsMargins(20, 15, 20, 15);
    cardLayout->setSpacing(15);

    // 创建图标标签
    QLabel *iconLabel = new QLabel();
    QPixmap iconPixmap(iconPath);
    if (iconPixmap.isNull()) {
        // 如果图标加载失败，使用默认样式创建圆形图标
        iconLabel->setStyleSheet(
            "QLabel {"
            "    background-color: #f0f0f0;"
            "    border-radius: 20px;"
            "    border: 2px solid #e0e0e0;"
            "    min-width: 40px;"
            "    min-height: 40px;"
            "    max-width: 40px;"
            "    max-height: 40px;"
            "}");
    } else {
        // 缩放图标
        iconPixmap = iconPixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        iconLabel->setPixmap(iconPixmap);
        iconLabel->setFixedSize(40, 40);
        iconLabel->setStyleSheet("QLabel { background-color: transparent; border: none; }");
    }

    // 创建设备名称标签
    QLabel *nameLabel = new QLabel(deviceName);
    nameLabel->setStyleSheet(
        "QLabel {"
        "    color: #333333;"
        "    font-size: 16px;"
        "    font-weight: 500;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background-color: transparent;"
        "    border: none;"
        "}");
    nameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    // 添加到卡片布局
    cardLayout->addWidget(iconLabel);
    cardLayout->addWidget(nameLabel);
    cardLayout->setStretch(1, 1);  // 让名称标签占据剩余空间

    return card;
}

