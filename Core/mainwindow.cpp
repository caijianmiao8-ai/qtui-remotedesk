#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗口属性
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumSize(1280, 800);

    setupUI();
    setupWindowControls();
    setupNavigation();
    setupBottomButtons();
    applyTheme();

    // 默认选中首页
    onHomeButtonClicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    // 设置中心部件的样式
    ui->centralwidget->setStyleSheet("background: transparent;");
    ui->widget->setStyleSheet("background: transparent;");

    // 给整个容器（widget）添加阴影效果
    QGraphicsDropShadowEffect *containerShadow = new QGraphicsDropShadowEffect(this);
    containerShadow->setBlurRadius(60);
    containerShadow->setColor(QColor(0, 0, 0, 15));  // rgba(0,0,0,0.06) = 0.06 * 255 ≈ 15
    containerShadow->setOffset(0, 30);
    ui->widget->setGraphicsEffect(containerShadow);

    // 设置左侧边栏样式 - 使用更强的毛玻璃效果
    ui->leftWidget->setStyleSheet(
        "#leftWidget {"
        "    background: rgba(255, 255, 255, 0.6);"
        "    border-top-left-radius: 24px;"
        "    border-bottom-left-radius: 24px;"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-right: none;"
        "}"
    );

    // 设置 stackedWidget 样式 - 使用更强的毛玻璃效果
    ui->stackedWidget->setStyleSheet(
        "QStackedWidget {"
        "    background: rgba(255, 255, 255, 0.6);"
        "    border-top-right-radius: 24px;"
        "    border-bottom-right-radius: 24px;"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-left: none;"
        "}"
    );

    // 设置品牌区样式
    ui->widget_3->setStyleSheet("background: transparent;");

    // 设置品牌信息
    QPixmap logoPixmap(":/qss/icon/logo_04.png");
    logoPixmap = logoPixmap.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(logoPixmap);
    ui->label->setFixedSize(48, 48);
    ui->label->setStyleSheet(
        "QLabel {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "        stop:0 #0A84FF, stop:1 #0051C7);"
        "    border-radius: 16px;"
        "}"
    );

    ui->label_2->setText("RemoteDesktop");
    ui->label_2->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 16px;"
        "    font-weight: 600;"
        "    line-height: 1.4;"
        "    font-family: 'Segoe UI', 'PingFang SC', 'Microsoft YaHei', Arial, sans-serif;"
        "    background: transparent;"
        "}"
    );

    ui->label_3->setText("v2.0.1");
    ui->label_3->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"
        "    font-size: 11px;"
        "    line-height: 1.4;"
        "    font-family: 'Segoe UI', 'PingFang SC', 'Microsoft YaHei', Arial, sans-serif;"
        "    background: transparent;"
        "}"
    );
}

void MainWindow::setupWindowControls()
{
    // 创建窗口控制按钮容器
    m_controlsWidget = new QWidget(ui->stackedWidget);
    m_controlsWidget->setFixedSize(120, 40);
    m_controlsWidget->move(ui->stackedWidget->width() - 140, 20);
    m_controlsWidget->setStyleSheet("background: transparent;");
    m_controlsWidget->raise();

    QHBoxLayout* controlsLayout = new QHBoxLayout(m_controlsWidget);
    controlsLayout->setContentsMargins(0, 0, 0, 0);
    controlsLayout->setSpacing(8);

    // 最小化按钮
    m_minimizeBtn = new QPushButton("−", m_controlsWidget);
    m_minimizeBtn->setFixedSize(32, 32);
    m_minimizeBtn->setCursor(Qt::PointingHandCursor);
    connect(m_minimizeBtn, &QPushButton::clicked, this, &MainWindow::onMinimizeClicked);

    // 最大化按钮
    m_maximizeBtn = new QPushButton("□", m_controlsWidget);
    m_maximizeBtn->setFixedSize(32, 32);
    m_maximizeBtn->setCursor(Qt::PointingHandCursor);
    connect(m_maximizeBtn, &QPushButton::clicked, this, &MainWindow::onMaximizeClicked);

    // 关闭按钮
    m_closeBtn = new QPushButton("✕", m_controlsWidget);
    m_closeBtn->setFixedSize(32, 32);
    m_closeBtn->setCursor(Qt::PointingHandCursor);
    m_closeBtn->setStyleSheet(
        "QPushButton {"
        "    background: rgba(0, 0, 0, 0.02);"
        "    color: #ef4444;"
        "    border: none;"
        "    border-radius: 10px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background: rgba(239, 68, 68, 0.1);"
        "    color: #dc2626;"
        "}"
        "QPushButton:pressed {"
        "    transform: scale(0.9);"
        "}"
    );
    connect(m_closeBtn, &QPushButton::clicked, this, &MainWindow::onCloseClicked);

    QString btnStyle =
        "QPushButton {"
        "    background: rgba(0, 0, 0, 0.02);"
        "    color: #64748b;"
        "    border: none;"
        "    border-radius: 10px;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "    background: rgba(0, 0, 0, 0.05);"
        "}"
        "QPushButton:pressed {"
        "    transform: scale(0.9);"
        "}";

    m_minimizeBtn->setStyleSheet(btnStyle);
    m_maximizeBtn->setStyleSheet(btnStyle);

    controlsLayout->addWidget(m_minimizeBtn);
    controlsLayout->addWidget(m_maximizeBtn);
    controlsLayout->addWidget(m_closeBtn);
}

void MainWindow::setupNavigation()
{
    // 连接信号槽
    connect(ui->homeBtn, &QToolButton::clicked, this, &MainWindow::onHomeButtonClicked);
    connect(ui->deviceBtn, &QToolButton::clicked, this, &MainWindow::onDeviceButtonClicked);
    connect(ui->settingBtn, &QToolButton::clicked, this, &MainWindow::onSettingButtonClicked);
    connect(ui->aboutBtn, &QToolButton::clicked, this, &MainWindow::onAboutButtonClicked);

    // 设置按钮文本
    ui->homeBtn->setText(m_currentLang == "zh" ? "  主页" : "  Home");
    ui->deviceBtn->setText(m_currentLang == "zh" ? "  设备管理" : "  Devices");
    ui->settingBtn->setText(m_currentLang == "zh" ? "  设置" : "  Settings");
    ui->aboutBtn->setText(m_currentLang == "zh" ? "  关于" : "  About");

    // 设置按钮样式
    for (auto btn : {ui->homeBtn, ui->deviceBtn, ui->settingBtn, ui->aboutBtn}) {
        btn->setToolButtonStyle(Qt::ToolButtonTextOnly);
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        btn->setMinimumHeight(44);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet(getSidebarButtonStyle(false));
    }
}

void MainWindow::setupBottomButtons()
{
    // 语言切换按钮
    ui->languageBtn->setText(m_currentLang == "zh" ? "  语言: 中文" : "  Language: English");
    ui->languageBtn->setMinimumHeight(44);
    ui->languageBtn->setCursor(Qt::PointingHandCursor);
    ui->languageBtn->setStyleSheet(getBottomButtonStyle(false));
    connect(ui->languageBtn, &QToolButton::clicked, this, &MainWindow::onLanguageButtonClicked);

    // 深浅色模式切换按钮
    ui->darkModeBtn->setText(m_darkMode ? (m_currentLang == "zh" ? "  浅色模式" : "  Light Mode")
                                        : (m_currentLang == "zh" ? "  深色模式" : "  Dark Mode"));
    ui->darkModeBtn->setMinimumHeight(44);
    ui->darkModeBtn->setCursor(Qt::PointingHandCursor);
    ui->darkModeBtn->setStyleSheet(getBottomButtonStyle(false));
    connect(ui->darkModeBtn, &QToolButton::clicked, this, &MainWindow::onDarkModeButtonClicked);

    // 退出登录按钮
    ui->signOutBtn->setText(m_currentLang == "zh" ? "  退出登录" : "  Sign Out");
    ui->signOutBtn->setMinimumHeight(44);
    ui->signOutBtn->setCursor(Qt::PointingHandCursor);
    ui->signOutBtn->setStyleSheet(getBottomButtonStyle(true));
    connect(ui->signOutBtn, &QToolButton::clicked, this, &MainWindow::onSignOutButtonClicked);
}

QString MainWindow::getSidebarButtonStyle(bool isActive)
{
    if (m_darkMode) {
        if (isActive) {
            return
                "QToolButton {"
                "    background: rgba(255, 255, 255, 0.08);"
                "    color: #f1f5f9;"
                "    border: none;"
                "    border-radius: 14px;"
                "    padding: 12px 16px;"
                "    text-align: left;"
                "    font-size: 14px;"
                "    font-weight: 500;"
                "}"
                "QToolButton:hover {"
                "    background: rgba(255, 255, 255, 0.12);"
                "}";
        } else {
            return
                "QToolButton {"
                "    background: transparent;"
                "    color: #f1f5f9;"
                "    border: none;"
                "    border-radius: 14px;"
                "    padding: 12px 16px;"
                "    text-align: left;"
                "    font-size: 14px;"
                "    font-weight: 500;"
                "}"
                "QToolButton:hover {"
                "    background: rgba(255, 255, 255, 0.07);"
                "}";
        }
    } else {
        if (isActive) {
            return
                "QToolButton {"
                "    background: rgba(0, 0, 0, 0.04);"
                "    color: #1e293b;"
                "    border: none;"
                "    border-radius: 14px;"
                "    padding: 12px 16px;"
                "    text-align: left;"
                "    font-size: 14px;"
                "    font-weight: 500;"
                "}"
                "QToolButton:hover {"
                "    background: rgba(0, 0, 0, 0.06);"
                "}";
        } else {
            return
                "QToolButton {"
                "    background: transparent;"
                "    color: #1e293b;"
                "    border: none;"
                "    border-radius: 14px;"
                "    padding: 12px 16px;"
                "    text-align: left;"
                "    font-size: 14px;"
                "    font-weight: 500;"
                "}"
                "QToolButton:hover {"
                "    background: rgba(0, 0, 0, 0.03);"
                "}";
        }
    }
}

QString MainWindow::getBottomButtonStyle(bool isSignOut)
{
    if (isSignOut) {
        return
            "QToolButton {"
            "    background: transparent;"
            "    color: #ef4444;"
            "    border: none;"
            "    border-radius: 14px;"
            "    padding: 12px 16px;"
            "    text-align: left;"
            "    font-size: 14px;"
            "    font-weight: 500;"
            "}"
            "QToolButton:hover {"
            "    background: rgba(239, 68, 68, 0.1);"
            "    color: #dc2626;"
            "}";
    } else {
        if (m_darkMode) {
            return
                "QToolButton {"
                "    background: transparent;"
                "    color: #f1f5f9;"
                "    border: none;"
                "    border-radius: 14px;"
                "    padding: 12px 16px;"
                "    text-align: left;"
                "    font-size: 14px;"
                "    font-weight: 500;"
                "}"
                "QToolButton:hover {"
                "    background: rgba(255, 255, 255, 0.07);"
                "}";
        } else {
            return
                "QToolButton {"
                "    background: transparent;"
                "    color: #1e293b;"
                "    border: none;"
                "    border-radius: 14px;"
                "    padding: 12px 16px;"
                "    text-align: left;"
                "    font-size: 14px;"
                "    font-weight: 500;"
                "}"
                "QToolButton:hover {"
                "    background: rgba(0, 0, 0, 0.03);"
                "}";
        }
    }
}

void MainWindow::applyTheme()
{
    if (m_darkMode) {
        // 深色主题
        ui->leftWidget->setStyleSheet(
            "#leftWidget {"
            "    background: rgba(255, 255, 255, 0.04);"
            "    border-top-left-radius: 24px;"
            "    border-bottom-left-radius: 24px;"
            "    border: 1px solid rgba(255, 255, 255, 0.1);"
            "}"
        );

        ui->stackedWidget->setStyleSheet(
            "QStackedWidget {"
            "    background: rgba(255, 255, 255, 0.04);"
            "    border-top-right-radius: 24px;"
            "    border-bottom-right-radius: 24px;"
            "    border: 1px solid rgba(255, 255, 255, 0.1);"
            "}"
        );

        ui->label_2->setStyleSheet(
            "QLabel {"
            "    color: #f1f5f9;"
            "    font-size: 16px;"
            "    font-weight: 600;"
            "    background: transparent;"
            "}"
        );

        ui->label_3->setStyleSheet(
            "QLabel {"
            "    color: #94a3b8;"
            "    font-size: 11px;"
            "    background: transparent;"
            "}"
        );

        m_minimizeBtn->setStyleSheet(
            "QPushButton {"
            "    background: rgba(255, 255, 255, 0.07);"
            "    color: #94a3b8;"
            "    border: none;"
            "    border-radius: 10px;"
            "    font-size: 14px;"
            "}"
            "QPushButton:hover {"
            "    background: rgba(255, 255, 255, 0.1);"
            "}"
        );

        m_maximizeBtn->setStyleSheet(m_minimizeBtn->styleSheet());
    } else {
        // 浅色主题
        ui->leftWidget->setStyleSheet(
            "#leftWidget {"
            "    background: rgba(255, 255, 255, 0.6);"
            "    border-top-left-radius: 24px;"
            "    border-bottom-left-radius: 24px;"
            "    border: 1px solid rgba(0, 0, 0, 0.05);"
            "}"
        );

        ui->stackedWidget->setStyleSheet(
            "QStackedWidget {"
            "    background: rgba(255, 255, 255, 0.6);"
            "    border-top-right-radius: 24px;"
            "    border-bottom-right-radius: 24px;"
            "    border: 1px solid rgba(0, 0, 0, 0.05);"
            "}"
        );

        ui->label_2->setStyleSheet(
            "QLabel {"
            "    color: #1e293b;"
            "    font-size: 16px;"
            "    font-weight: 600;"
            "    background: transparent;"
            "}"
        );

        ui->label_3->setStyleSheet(
            "QLabel {"
            "    color: #64748b;"
            "    font-size: 11px;"
            "    background: transparent;"
            "}"
        );

        m_minimizeBtn->setStyleSheet(
            "QPushButton {"
            "    background: rgba(0, 0, 0, 0.02);"
            "    color: #64748b;"
            "    border: none;"
            "    border-radius: 10px;"
            "    font-size: 14px;"
            "}"
            "QPushButton:hover {"
            "    background: rgba(0, 0, 0, 0.05);"
            "}"
        );

        m_maximizeBtn->setStyleSheet(m_minimizeBtn->styleSheet());
    }

    // 更新按钮样式
    for (auto btn : {ui->homeBtn, ui->deviceBtn, ui->settingBtn, ui->aboutBtn}) {
        if (btn != m_currentActiveButton) {
            btn->setStyleSheet(getSidebarButtonStyle(false));
        }
    }

    if (m_currentActiveButton) {
        m_currentActiveButton->setStyleSheet(getSidebarButtonStyle(true));
    }

    ui->languageBtn->setStyleSheet(getBottomButtonStyle(false));
    ui->darkModeBtn->setStyleSheet(getBottomButtonStyle(false));
    ui->signOutBtn->setStyleSheet(getBottomButtonStyle(true));

    update();
}

void MainWindow::setButtonActive(QToolButton *button)
{
    if (m_currentActiveButton && m_currentActiveButton != button) {
        setButtonNormal(m_currentActiveButton);
    }

    button->setStyleSheet(getSidebarButtonStyle(true));
    m_currentActiveButton = button;
}

void MainWindow::setButtonNormal(QToolButton *button)
{
    button->setStyleSheet(getSidebarButtonStyle(false));
}

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

void MainWindow::onLanguageButtonClicked()
{
    m_currentLang = (m_currentLang == "zh") ? "en" : "zh";

    // 更新按钮文本
    ui->homeBtn->setText(m_currentLang == "zh" ? "  主页" : "  Home");
    ui->deviceBtn->setText(m_currentLang == "zh" ? "  设备管理" : "  Devices");
    ui->settingBtn->setText(m_currentLang == "zh" ? "  设置" : "  Settings");
    ui->aboutBtn->setText(m_currentLang == "zh" ? "  关于" : "  About");

    ui->languageBtn->setText(m_currentLang == "zh" ? "  语言: 中文" : "  Language: English");
    ui->darkModeBtn->setText(m_darkMode ? (m_currentLang == "zh" ? "  浅色模式" : "  Light Mode")
                                        : (m_currentLang == "zh" ? "  深色模式" : "  Dark Mode"));
    ui->signOutBtn->setText(m_currentLang == "zh" ? "  退出登录" : "  Sign Out");
}

void MainWindow::onDarkModeButtonClicked()
{
    m_darkMode = !m_darkMode;
    ui->darkModeBtn->setText(m_darkMode ? (m_currentLang == "zh" ? "  浅色模式" : "  Light Mode")
                                        : (m_currentLang == "zh" ? "  深色模式" : "  Dark Mode"));
    applyTheme();
}

void MainWindow::onSignOutButtonClicked()
{
    QApplication::quit();
}

void MainWindow::onMinimizeClicked()
{
    showMinimized();
}

void MainWindow::onMaximizeClicked()
{
    if (isMaximized()) {
        showNormal();
    } else {
        showMaximized();
    }
}

void MainWindow::onCloseClicked()
{
    close();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制渐变背景
    QRect rect = this->rect().adjusted(0, 0, 0, 0);

    if (m_darkMode) {
        // 深色模式渐变背景
        QRadialGradient gradient(rect.width() * 0.2, rect.height() * 0.2,
                                 qMax(rect.width(), rect.height()));
        gradient.setColorAt(0, QColor(80, 80, 90, 102));    // rgba(80,80,90,0.4)
        gradient.setColorAt(0.6, QColor(10, 10, 12, 230));  // rgba(10,10,12,0.9)
        painter.fillRect(rect, gradient);

        // 叠加基础颜色
        painter.fillRect(rect, QColor(2, 6, 23, 255));  // bg-slate-950
    } else {
        // 浅色模式渐变背景
        QRadialGradient gradient(rect.width() * 0.2, rect.height() * 0.2,
                                 qMax(rect.width(), rect.height()) * 1.2);
        gradient.setColorAt(0, QColor(255, 255, 255, 230));    // rgba(255,255,255,0.9)
        gradient.setColorAt(0.4, QColor(226, 232, 240, 153));  // rgba(226,232,240,0.6)
        gradient.setColorAt(0.7, QColor(226, 232, 240, 77));   // rgba(226,232,240,0.3)
        painter.fillRect(rect, gradient);

        // 叠加基础颜色
        painter.fillRect(rect, QColor(241, 245, 249, 255));  // bg-slate-100
    }

    QMainWindow::paintEvent(event);
}

QString MainWindow::getLightThemeStyles()
{
    return "";
}

QString MainWindow::getDarkThemeStyles()
{
    return "";
}

void MainWindow::setupButtonWithIcon(QToolButton *button, const QString &text, const QString &iconPath)
{
    // 这个函数保留但不再使用
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    // 动态调整窗口控制按钮位置
    if (m_controlsWidget && ui->stackedWidget) {
        m_controlsWidget->move(ui->stackedWidget->width() - 140, 20);
    }
}
