#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);
    initUi();
}

Home::~Home()
{
    delete ui;
}

void Home::initUi()
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
    setupWidget4();
}

void Home::setupHomeLayout()
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
    mainLayout->addSpacing(25);  // widget_3 和 widget_4 之间的间距
    mainLayout->addWidget(ui->widget_4);
    mainLayout->addStretch(1);   // 底部弹性空间
}

void Home::setupHomeHeader()
{
    // 清除现有布局
    if (ui->widget_1->layout()) {
        delete ui->widget_1->layout();
    }

    // 创建新的垂直布局
    QVBoxLayout *layout = new QVBoxLayout(ui->widget_1);
    layout->setContentsMargins(0, 50, 0, 18);  // 上边距，让内容离顶部远

    // 设置 Welcome back 标签
    ui->label->setText("Welcome back");
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
    ui->label_2->setText("This machine is available for remote control (host mode)");
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

void Home::setupWidget2()
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

void Home::setupIconLabel()
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

void Home::setupTipLabel()
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

void Home::setupWidget3()
{
    // 设置 widget_3 的基本样式（与 widget_2 保持一致）
    ui->widget_3->setStyleSheet(
        "QWidget#widget_3 {"
        "    background-color: #ffffff;"
        "    border-radius: 25px;"
        "    border: none;"
        "}");
    ui->widget_3->setAttribute(Qt::WA_StyledBackground, true);

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
    ui->widget_3->setGraphicsEffect(bottomShadow);

    // 设置 widget_3 的布局
    setupWidget3Layout();

    // 设置标题
    setupWidget3Title();

    // 设置信息网格
    setupWidget3InfoGrid();
}

void Home::setupWidget3Layout()
{
    if (ui->widget_3->layout()) {
        delete ui->widget_3->layout();
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(ui->widget_3);

    // 统一设置上下边距为30，保持对称
    mainLayout->setContentsMargins(50, 60, 50, 55);  // 上下都是30
    mainLayout->setSpacing(30);  // 标题与网格间距也是30

    mainLayout->setAlignment(Qt::AlignTop);
}

void Home::setupWidget3Title()
{
    // 设置标题
    ui->label_5->setText("This Machine");
    ui->label_5->setStyleSheet(
        "QLabel {"
        "    color: #000000;"
        "    font-size: 18px;"
        "    font-weight: bold;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background-color: transparent;"
        "    border: none;"
        "    margin: 0;"
        "    padding: 0;"
        "}");

    // 将标题添加到布局
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(ui->widget_3->layout());
    if (mainLayout) {
        mainLayout->addWidget(ui->label_5);
    }
}

void Home::setupWidget3InfoGrid()
{
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setHorizontalSpacing(330);

    // 减小行间距，主要控制信息项之间的垂直距离
    gridLayout->setVerticalSpacing(45);  // 从30减小到15

    // 第一行第一列：设备名称
    setupInfoItem(gridLayout, 0, 0, ui->label_6, ui->label_7, "Device Name", "My-Desktop-PC", 15);  // 添加内部间距参数

    // 第一行第二列：设备ID
    setupInfoItem(gridLayout, 0, 1, ui->label_8, ui->label_9, "Device Id", "PC-001-2024", 15);

    // 第二行第一列：本地IP
    setupInfoItem(gridLayout, 1, 0, ui->label_10, ui->label_11, "Local Ip", "192.168.1.100", 15);

    // 第二行第二列：网络状态
    setupNetworkStatusItem(gridLayout, 1, 1, ui->label_12, 15);  // 添加内部间距参数

    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(ui->widget_3->layout());
    if (mainLayout) {
        mainLayout->addLayout(gridLayout);

        // 添加底部弹性空间，确保内容顶部对齐
        mainLayout->addStretch(1);
    }
}

void Home::setupInfoItem(QGridLayout *gridLayout, int row, int col,
                         QLabel *titleLabel, QLabel *valueLabel,
                         const QString &title, const QString &value, int verticalSpacing)
{
    // 创建容器widget来控制内部间距
    QWidget *itemContainer = new QWidget();
    // 设置容器背景色为白色
    itemContainer->setStyleSheet("background-color: #ffffff;");
    QVBoxLayout *itemLayout = new QVBoxLayout(itemContainer);
    itemLayout->setContentsMargins(0, 0, 0, 0);
    itemLayout->setSpacing(verticalSpacing);  // 控制标题与值的间距

    // 设置标题标签
    titleLabel->setText(title);
    titleLabel->setStyleSheet(
        "QLabel {"
        "    color: #666666;"
        "    font-size: 15px;"
        "    font-weight: normal;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background-color: #ffffff;"
        "    border: null;"
        "    margin: 0;"
        "    padding: 0;"
        "}");

    // 设置值标签
    valueLabel->setText(value);
    valueLabel->setStyleSheet(
        "QLabel {"
        "    color: #000000;"
        "    font-size: 14px;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background-color: #ffffff;"
        "    border: none;"
        "    margin: 0;"
        "    padding: 0;"
        "}");

    // 添加到item布局
    itemLayout->addWidget(titleLabel);
    itemLayout->addWidget(valueLabel);

    // 设置容器左对齐
    itemLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // 将整个容器添加到网格布局
    gridLayout->addWidget(itemContainer, row, col);
}

void Home::setupNetworkStatusItem(QGridLayout *gridLayout, int row, int col, QLabel *titleLabel, int verticalSpacing)
{
    // 创建主容器
    QWidget *mainContainer = new QWidget();
    // 设置容器背景色为白色
    mainContainer->setStyleSheet("background-color: #ffffff;");
    QVBoxLayout *mainLayout = new QVBoxLayout(mainContainer);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(verticalSpacing);
    mainLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // 设置标题
    titleLabel->setText("Network Status");
    titleLabel->setStyleSheet(
        "QLabel {"
        "    color: #666666;"
        "    font-size: 15px;"
        "    font-weight: normal;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background-color: #ffffff;"
        "    border: none;"
        "    margin: 0;"
        "    padding: 0;"
        "}");

    // 创建网络状态显示容器
    QWidget *statusContainer = new QWidget();
    QHBoxLayout *statusLayout = new QHBoxLayout(statusContainer);
    statusLayout->setContentsMargins(0, 0, 0, 0);
    statusLayout->setSpacing(8);

    // 创建绿色状态指示器
    QLabel *statusIndicator = new QLabel();
    statusIndicator->setFixedSize(10, 10);
    statusIndicator->setStyleSheet(
        "QLabel {"
        "    background-color: #22c55e;"
        "    border-radius: 5px;"
        "    border: none;"
        "}");

    // 创建状态文本
    QLabel *statusText = new QLabel("LAN ONLINE");
    statusText->setStyleSheet(
        "QLabel {"
        "    color: #22c55e;"
        "    font-size: 14px;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background-color: #ffffff;"
        "    border: none;"
        "    margin: 0;"
        "    padding: 0;"
        "}");

    // 添加到状态容器
    statusLayout->addWidget(statusIndicator);
    statusLayout->addWidget(statusText);
    statusLayout->addStretch(1);

    // 添加到主容器
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(statusContainer);

    // 添加到网格布局
    gridLayout->addWidget(mainContainer, row, col);
}

void Home::setupWidget4()
{
    // 设置 widget_4 的基本样式（与 widget_2、widget_3 保持一致）
    ui->widget_4->setStyleSheet(
        "QWidget#widget_4 {"
        "    background-color: #ffffff;"
        "    border-radius: 25px;"
        "    border: none;"
        "}");
    ui->widget_4->setAttribute(Qt::WA_StyledBackground, true);

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
    ui->widget_4->setGraphicsEffect(bottomShadow);

    setupWidget4Layout();
    setupWidget4Title();
    setupWidget4QuickActions();
}

void Home::setupWidget4Layout()
{
    if (ui->widget_4->layout()) {
        delete ui->widget_4->layout();
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(ui->widget_4);
    mainLayout->setContentsMargins(50, 30, 50, 30);
    mainLayout->setSpacing(30);
    mainLayout->setAlignment(Qt::AlignTop);
}

void Home::setupWidget4Title()
{
    QLabel *titleLabel = new QLabel("Quick Actions");
    titleLabel->setStyleSheet(
        "QLabel {"
        "    color: #000000;"
        "    font-size: 18px;"
        "    font-weight: bold;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background-color: transparent;"
        "    border: none;"
        "    margin: 0;"
        "    padding: 0;"
        "}");

    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(ui->widget_4->layout());
    if (mainLayout) {
        mainLayout->addWidget(titleLabel);
    }
}

void Home::setupWidget4QuickActions()
{
    QHBoxLayout *actionsLayout = new QHBoxLayout();
    actionsLayout->setContentsMargins(0, 0, 0, 0);
    actionsLayout->setSpacing(20);  // 左右两部分之间的间距

    // 创建左侧快速操作项
    QWidget *leftAction = createQuickActionItem(
        "Device List",
        "View registered devices",
        ":/qss/icon/logo_04.png"  // 替换为实际图标路径
    );

    // 创建右侧快速操作项
    QWidget *rightAction = createQuickActionItem(
        "System Settings",
        "Configure parameters",
        ":/qss/icon/logo_04.png"  // 替换为实际图标路径
    );

    actionsLayout->addWidget(leftAction);
    actionsLayout->addWidget(rightAction);

    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(ui->widget_4->layout());
    if (mainLayout) {
        mainLayout->addLayout(actionsLayout);
        //mainLayout->addStretch(1);
    }
}

QWidget* Home::createQuickActionItem(const QString &title, const QString &description, const QString &iconPath)
{
    // 创建可点击的容器
    QWidget *actionItem = new QWidget();
    actionItem->setCursor(Qt::PointingHandCursor);
    actionItem->setFixedSize(415, 150);

    // 设置样式表
    actionItem->setStyleSheet(
        "QWidget {"
        "    background-color: #ffffff;"
        "    border: 1px solid #f0f0f0;"
        "    border-radius: 12px;"
        "    padding: 20px;"
        "}"
        "QWidget:hover {"
        "    background-color: #f8f9fa;"
        "    border-color: #e0e0e0;"
        "}");

    // 创建垂直布局
    QVBoxLayout *itemLayout = new QVBoxLayout(actionItem);
    itemLayout->setContentsMargins(25, 20, 0, 0);
    itemLayout->setSpacing(10);
    itemLayout->setAlignment(Qt::AlignTop);

    // 创建图标 - 修复样式问题
    QLabel *iconLabel = new QLabel();

    // 设置图标标签样式 - 透明背景，无边框
    iconLabel->setStyleSheet(
        "QLabel {"
        "    background-color: transparent;"
        "    border: none;"
        "    margin: 0;"
        "    padding: 0;"
        "}");

    // 尝试加载图标
    QPixmap iconPixmap(iconPath);

    iconLabel->setPixmap(iconPixmap.scaled(23, 23, Qt::KeepAspectRatio, Qt::SmoothTransformation));


    iconLabel->setAlignment(Qt::AlignLeft);

    // 创建标题标签
    QLabel *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet(
        "QLabel {"
        "    color: #000000;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background-color: transparent;"
        "    border: none;"
        "    margin: 0;"
        "    padding: 0;"
        "}");
    titleLabel->setAlignment(Qt::AlignLeft);

    // 创建描述标签
    QLabel *descLabel = new QLabel(description);
    descLabel->setStyleSheet(
        "QLabel {"
        "    color: #666666;"
        "    font-size: 14px;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background-color: transparent;"
        "    border: none;"
        "    margin: 0;"
        "    padding: 0;"
        "}");
    descLabel->setAlignment(Qt::AlignLeft);
    descLabel->setWordWrap(true);

    // 添加到布局
    itemLayout->addWidget(iconLabel);
    itemLayout->addSpacing(20);
    itemLayout->addWidget(titleLabel);
    itemLayout->addWidget(descLabel);
    itemLayout->addStretch(1);

    return actionItem;
}
