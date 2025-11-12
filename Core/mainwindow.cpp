#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupSoftwareInfo();
    setupNavigation();
    setupBottomButtons();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupNavigation()
{
    // 连接信号槽
    connect(ui->homeBtn, &QToolButton::clicked, this, &MainWindow::onHomeButtonClicked);
    connect(ui->deviceBtn, &QToolButton::clicked, this, &MainWindow::onDeviceButtonClicked);
    connect(ui->settingBtn, &QToolButton::clicked, this, &MainWindow::onSettingButtonClicked);
    connect(ui->aboutBtn, &QToolButton::clicked, this, &MainWindow::onAboutButtonClicked);

    // 设置按钮基础样式
    setupButtonWithIcon(ui->homeBtn, "Home", ":/qss/icon/logo_02.png");
    setupButtonWithIcon(ui->deviceBtn, "Devices", ":/qss/icon/logo_02.png");
    setupButtonWithIcon(ui->settingBtn, "Settings", ":/qss/icon/logo_02.png");
    setupButtonWithIcon(ui->aboutBtn, "About", ":/qss/icon/logo_02.png");

    // 默认选中首页
    onHomeButtonClicked();
}

void MainWindow::setupButtonWithIcon(QToolButton *button, const QString &text, const QString &iconPath)
{
    // 设置图标
    QIcon icon(iconPath);
    button->setIcon(icon);
    button->setIconSize(QSize(16, 16));

    // 关键：在文本前添加空格来强制间距
    button->setText("  " + text);

    button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    button->setAutoRaise(true);

    button->setStyleSheet(
        "QToolButton {"
        "    text-align: left;"
        "    padding: 10px 15px;"
        "    border: none;"                   // 无边框
        "    background-color: transparent;"
        "    color: #000000;"                 // 纯黑色字体
        "    font-size: 14px;"
        "    font-weight: bold;"              // 所有状态字体加粗
        "    border-radius: 15px;"
        "    margin: 1px 0px;"
        "}"
        "QToolButton:hover {"
        "    background-color: #f0f0f0;"      // 灰色悬停
        "    color: #000000;"
        "}"
        "QToolButton:pressed {"
        "    background-color: #f0f0f0;"      // 保持与悬停相同
        "    color: #000000;"
        "}");
}

void MainWindow::setButtonActive(QToolButton *button)
{
    if (m_currentActiveButton && m_currentActiveButton != button) {
        setButtonNormal(m_currentActiveButton);
    }

    // 结合边框和渐变背景的内嵌效果
    QString activeStyle =
        "QToolButton {"
        "    text-align: left;"
        "    padding: 10px 15px;"
        "    border: 1px solid #e0e0e0;"      // 基础边框颜色
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "                               stop:0 #f8f8f8, stop:0.5 #f0f0f0, "
        "                               stop:1 #e8e8e8);"  // 渐变背景
        "    color: #000000;"                 // 黑色字体
        "    font-size: 14px;"
        "    font-weight: bold;"              // 加粗
        "    border-radius: 15px;"
        "    margin: 1px 0px;"
        "    border-top: 1px  solid #d5d5d5;"
        "    border-left: 1px solid #d5d5d5;"
        "    border-right: 1px solid #f5f5f5;"
        "    border-bottom: 1px solid #f5f5f5;"
        "}";

    button->setStyleSheet(activeStyle);
    m_currentActiveButton = button;
}

void MainWindow::setButtonNormal(QToolButton *button)
{
    // 正常状态
    QString normalStyle =
            "QToolButton {"
            "    text-align: left;"
            "    padding: 10px 15px;"
            "    border: none;"                   // 无边框
            "    background-color: transparent;"
            "    color: #000000;"                 // 纯黑色字体
            "    font-size: 14px;"
            "    font-weight: bold;"              // 所有状态字体加粗
            "    border-radius: 15px;"
            "    margin: 1px 0px;"
            "}"
            "QToolButton:hover {"
            "    background-color: #f0f0f0;"      // 灰色悬停
            "    color: #000000;"
            "}"
            "QToolButton:pressed {"
            "    background-color: #f0f0f0;"      // 保持与悬停相同
            "    color: #000000;"
            "}";

    button->setStyleSheet(normalStyle);
}

void MainWindow::setupSoftwareInfo()
{
    // 设置 widget_3 的背景颜色
    ui->widget_3->setStyleSheet(
        "QWidget#widget_3 {"
        "    background-color: transparent;"  // 浅灰色背景
        "}");

    // 清除布局（如果存在）
    if (ui->widget_3->layout()) {
        QLayout *oldLayout = ui->widget_3->layout();
        delete oldLayout;
    }

    // 创建新布局
    QHBoxLayout *mainLayout = new QHBoxLayout(ui->widget_3);
    mainLayout->setContentsMargins(15, 10, 15, 10);
    mainLayout->setSpacing(12);

    // 设置软件图标
    QPixmap logoPixmap(":/qss/icon/logo_04.png");
    logoPixmap = logoPixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(logoPixmap);
    ui->label->setScaledContents(true);
    ui->label->setFixedSize(40, 40);
    ui->label->setStyleSheet(
        "QLabel {"
        "    background-color: transparent;"
        "}");

    // 设置软件名称
    ui->label_2->setText("RemoteDesktop");
    ui->label_2->setStyleSheet(
        "QLabel {"
        "    color: #333333;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    background-color: transparent;"
        "    margin: 0px;"
        "    padding: 0px;"
        "}");
    ui->label_2->setAlignment(Qt::AlignLeft | Qt::AlignBottom);  // 底部对齐

    // 设置软件版本
    ui->label_3->setText("v1.0.0");
    ui->label_3->setStyleSheet(
        "QLabel {"
        "    color: #666666;"
        "    font-size: 12px;"
        "    background-color: transparent;"
        "    margin: 0px;"
        "    padding: 0px;"
        "}");
    ui->label_3->setAlignment(Qt::AlignLeft | Qt::AlignTop);  // 顶部对齐

    // 创建文本布局 - 最小间距
    QVBoxLayout *textLayout = new QVBoxLayout();
    textLayout->setContentsMargins(0, 0, 0, 0);
    textLayout->setSpacing(5);  // 零间距

    textLayout->addWidget(ui->label_2);
    textLayout->addWidget(ui->label_3);

    // 添加到主布局
    mainLayout->addWidget(ui->label);
    mainLayout->addLayout(textLayout);

    // 设置拉伸
    mainLayout->setStretch(0, 0); // 图标固定
    mainLayout->setStretch(1, 1); // 文本拉伸
}

void MainWindow::setupBottomButtons()
{
    // 连接信号槽
    connect(ui->languageBtn, &QToolButton::clicked, this, &MainWindow::onLanguageButtonClicked);
    connect(ui->darkModeBtn, &QToolButton::clicked, this, &MainWindow::onDarkModeButtonClicked);
    connect(ui->signOutBtn, &QToolButton::clicked, this, &MainWindow::onSignOutButtonClicked);

    // 设置按钮样式
    setupBottomButtonWithIcon(ui->languageBtn, "Language:English", ":/qss/icon/logo_04.png");
    setupBottomButtonWithIcon(ui->darkModeBtn, "Dark Mode", ":/qss/icon/logo_04.png");
    setupBottomButtonWithIcon(ui->signOutBtn, "Sign Out", ":/qss/icon/logo_04.png");
}

void MainWindow::setupBottomButtonWithIcon(QToolButton *button, const QString &text, const QString &iconPath)
{
    // 设置图标
    QIcon icon(iconPath);
    button->setIcon(icon);
    button->setIconSize(QSize(16, 16));

    // 设置文本
    button->setText("  " + text);

    button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    button->setAutoRaise(true);

    // 根据按钮对象名判断是否是 Sign Out 按钮
    bool isSignOutButton = (button->objectName() == "signOutBtn");

    if (isSignOutButton) {
        // Sign Out 按钮的特殊样式
        button->setStyleSheet(
            "QToolButton {"
            "    text-align: left;"
            "    padding: 10px 15px;"
            "    border: none;"
            "    background-color: transparent;"
            "    color: #ff4444;"              // 红色字体
            "    font-size: 14px;"
            "    font-weight: normal;"
            "    border-radius: 10px;"
            "    margin: 1px 0px;"
            "}"
            "QToolButton:hover {"
            "    background-color: #ffeeee;"    // 浅红色背景悬停
            "    color: #cc0000;"               // 悬停时字体颜色加深
            "}"
            "QToolButton:pressed {"
            "    background-color: #ffdddd;"    // 按下时背景更深
            "    color: #aa0000;"               // 按下时字体颜色更深
            "}");
    } else {
        // 普通底部按钮样式
        button->setStyleSheet(
            "QToolButton {"
            "    text-align: left;"
            "    padding: 10px 15px;"
            "    border: none;"
            "    background-color: transparent;"
            "    color: #666666;"
            "    font-size: 14px;"
            "    font-weight: normal;"
            "    border-radius: 10px;"
            "    margin: 1px 0px;"
            "}"
            "QToolButton:hover {"
            "    background-color: #f0f0f0;"
            "    color: #333333;"
            "}"
            "QToolButton:pressed {"
            "    background-color: #e8e8e8;"
            "}");
    }
}

// 底部按钮的槽函数实现
void MainWindow::onLanguageButtonClicked()
{
    // 实现语言切换功能
    // 这里可以添加语言切换对话框或逻辑
}

void MainWindow::onDarkModeButtonClicked()
{

}

void MainWindow::onSignOutButtonClicked()
{
    // 实现退出登录
    // 这里可以添加退出登录逻辑
    QApplication::quit(); // 示例：退出应用
}

//上方切换页面按钮
void MainWindow::switchToPage(int pageIndex)
{
    ui->stackedWidget->setCurrentIndex(pageIndex);
}

void MainWindow::onHomeButtonClicked()
{
    switchToPage(0);
    setButtonActive(ui->homeBtn);
}

void MainWindow::onDeviceButtonClicked()
{
    switchToPage(1);
    setButtonActive(ui->deviceBtn);
}

void MainWindow::onSettingButtonClicked()
{
    switchToPage(2);
    setButtonActive(ui->settingBtn);
}

void MainWindow::onAboutButtonClicked()
{
    switchToPage(3);
    setButtonActive(ui->aboutBtn);
}

