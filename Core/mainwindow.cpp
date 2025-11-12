#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsDropShadowEffect>
#include <QApplication>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initializeFrame();
    setupTopBar();
    setupBranding();
    setupNavigation();
    setupBottomButtons();

    onHomeButtonClicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeFrame()
{
    setAttribute(Qt::WA_TranslucentBackground);
    ui->centralwidget->setAttribute(Qt::WA_StyledBackground, true);
    ui->shellFrame->setAttribute(Qt::WA_StyledBackground, true);
    ui->leftWidget->setAttribute(Qt::WA_StyledBackground, true);

    applyShadow(ui->shellFrame, 60.0, 28.0, QColor(15, 23, 42, 42));
    applyShadow(ui->leftWidget, 48.0, 20.0, QColor(15, 23, 42, 26));
}

void MainWindow::setupTopBar()
{
    auto setCommonIcon = [](QToolButton *button, IconGlyph glyph, const QColor &color) {
        button->setIcon(QIcon(IconHelper::draw(glyph, QSize(18, 18), color)));
        button->setIconSize(QSize(18, 18));
        button->setText(QString());
        button->setCursor(Qt::PointingHandCursor);
    };

    const QString glassStyle = QStringLiteral(
        "QToolButton {"
        "    background: qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "        stop:0 rgba(255,255,255,0.88),"
        "        stop:1 rgba(255,255,255,0.46));"
        "    border-radius: 13px;"
        "    border: 1px solid rgba(255,255,255,0.64);"
        "    border-bottom-color: rgba(15,23,42,0.12);"
        "    border-right-color: rgba(15,23,42,0.1);"
        "    min-width: 36px;"
        "    min-height: 36px;"
        "}"
        "QToolButton:hover {"
        "    background: qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "        stop:0 rgba(255,255,255,0.96),"
        "        stop:1 rgba(255,255,255,0.58));"
        "}"
        "QToolButton:pressed {"
        "    background-color: rgba(10,132,255,0.18);"
        "}");

    const QString closeStyle = QStringLiteral(
        "QToolButton {"
        "    background: qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "        stop:0 rgba(255,255,255,0.92),"
        "        stop:1 rgba(255,245,245,0.58));"
        "    border-radius: 13px;"
        "    border: 1px solid rgba(255,200,200,0.65);"
        "    border-bottom-color: rgba(239,68,68,0.22);"
        "    border-right-color: rgba(239,68,68,0.18);"
        "    min-width: 36px;"
        "    min-height: 36px;"
        "}"
        "QToolButton:hover {"
        "    background: qlineargradient(x1:0,y1:0,x2:0,y2:1,"
        "        stop:0 rgba(255,255,255,0.98),"
        "        stop:1 rgba(255,220,220,0.68));"
        "}"
        "QToolButton:pressed {"
        "    background-color: rgba(239,68,68,0.24);"
        "}");

    ui->minimizeButton->setStyleSheet(glassStyle);
    ui->fullscreenButton->setStyleSheet(glassStyle);
    ui->closeButton->setStyleSheet(closeStyle);

    setCommonIcon(ui->minimizeButton, IconGlyph::Minus, QColor(28, 33, 49, 210));
    setCommonIcon(ui->fullscreenButton, IconGlyph::Maximize, QColor(28, 33, 49, 210));
    setCommonIcon(ui->closeButton, IconGlyph::Close, QColor(239, 68, 68));

    connect(ui->minimizeButton, &QToolButton::clicked, this, &MainWindow::showMinimized);
    connect(ui->fullscreenButton, &QToolButton::clicked, this, &MainWindow::onToggleFullscreen);
    connect(ui->closeButton, &QToolButton::clicked, this, &MainWindow::close);
}

void MainWindow::setupBranding()
{
    ui->label_appName->setStyleSheet("QLabel { color: rgba(15,23,42,0.92); font-size: 18px; font-weight: 600; }");
    ui->label_version->setStyleSheet("QLabel { color: rgba(15,23,42,0.45); font-size: 12px; font-weight: 500; }");

    auto *logoIcon = new QLabel(ui->logoBadge);
    logoIcon->setAlignment(Qt::AlignCenter);
    logoIcon->setPixmap(IconHelper::draw(IconGlyph::Monitor, QSize(26, 26), Qt::white));
    logoIcon->resize(ui->logoBadge->size());
    logoIcon->setAttribute(Qt::WA_TransparentForMouseEvents);

    applyShadow(ui->logoBadge, 36.0, 12.0, QColor(10, 132, 255, 48));
}

void MainWindow::setupNavigation()
{
    setupSidebarButton(ui->homeBtn, tr("主页"), IconGlyph::Home);
    setupSidebarButton(ui->deviceBtn, tr("设备管理"), IconGlyph::Grid);
    setupSidebarButton(ui->settingBtn, tr("设置"), IconGlyph::Settings);
    setupSidebarButton(ui->aboutBtn, tr("关于"), IconGlyph::Info);

    connect(ui->homeBtn, &QToolButton::clicked, this, &MainWindow::onHomeButtonClicked);
    connect(ui->deviceBtn, &QToolButton::clicked, this, &MainWindow::onDeviceButtonClicked);
    connect(ui->settingBtn, &QToolButton::clicked, this, &MainWindow::onSettingButtonClicked);
    connect(ui->aboutBtn, &QToolButton::clicked, this, &MainWindow::onAboutButtonClicked);
}

void MainWindow::setupSidebarButton(QToolButton *button, const QString &text, IconGlyph glyph)
{
    button->setText(text);
    button->setIcon(QIcon(IconHelper::draw(glyph, QSize(22, 22), QColor(15, 23, 42, 220))));
    button->setIconSize(QSize(22, 22));
    button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    button->setCursor(Qt::PointingHandCursor);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    button->setProperty("glyph", static_cast<int>(glyph));

    button->setStyleSheet(
        "QToolButton {"
        "    background: transparent;"
        "    border: 1px solid transparent;"
        "    color: rgba(15,23,42,0.55);"
        "    font-size: 15px;"
        "    font-weight: 600;"
        "    padding: 12px 16px;"
        "    border-radius: 16px;"
        "    text-align: left;"
        "}"
        "QToolButton:hover {"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "        stop:0 rgba(255,255,255,0.62),"
        "        stop:1 rgba(240,244,255,0.42));"
        "    border-color: rgba(255,255,255,0.6);"
        "}");
}

void MainWindow::setButtonActive(QToolButton *button)
{
    if (m_currentActiveButton && m_currentActiveButton != button) {
        setButtonNormal(m_currentActiveButton);
    }

    bool ok = false;
    IconGlyph glyph = static_cast<IconGlyph>(button->property("glyph").toInt(&ok));
    if (ok) {
        button->setIcon(QIcon(IconHelper::draw(glyph, QSize(22, 22), QColor(10, 132, 255))));
    }

    button->setStyleSheet(
        "QToolButton {"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "        stop:0 rgba(10,132,255,0.24),"
        "        stop:1 rgba(10,132,255,0.14));"
        "    border: 1px solid rgba(10,132,255,0.32);"
        "    color: #0A84FF;"
        "    font-size: 15px;"
        "    font-weight: 700;"
        "    padding: 12px 16px;"
        "    border-radius: 16px;"
        "    text-align: left;"
        "}"
        "QToolButton:hover {"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "        stop:0 rgba(10,132,255,0.3),"
        "        stop:1 rgba(10,132,255,0.18));"
        "}");

    m_currentActiveButton = button;
}

void MainWindow::setButtonNormal(QToolButton *button)
{
    if (!button) {
        return;
    }

    bool ok = false;
    IconGlyph glyph = static_cast<IconGlyph>(button->property("glyph").toInt(&ok));
    if (ok) {
        button->setIcon(QIcon(IconHelper::draw(glyph, QSize(22, 22), QColor(15, 23, 42, 220))));
    }

    button->setStyleSheet(
        "QToolButton {"
        "    background: transparent;"
        "    border: 1px solid transparent;"
        "    color: rgba(15,23,42,0.55);"
        "    font-size: 15px;"
        "    font-weight: 600;"
        "    padding: 12px 16px;"
        "    border-radius: 16px;"
        "    text-align: left;"
        "}"
        "QToolButton:hover {"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "        stop:0 rgba(255,255,255,0.62),"
        "        stop:1 rgba(240,244,255,0.42));"
        "    border-color: rgba(255,255,255,0.6);"
        "}");
}

void MainWindow::setupBottomButtons()
{
    connect(ui->languageBtn, &QToolButton::clicked, this, &MainWindow::onLanguageButtonClicked);
    connect(ui->darkModeBtn, &QToolButton::clicked, this, &MainWindow::onDarkModeButtonClicked);
    connect(ui->signOutBtn, &QToolButton::clicked, this, &MainWindow::onSignOutButtonClicked);

    auto controlStyle = QStringLiteral(
        "QToolButton {"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "        stop:0 rgba(255,255,255,0.86),"
        "        stop:1 rgba(240,244,255,0.52));"
        "    border: 1px solid rgba(255,255,255,0.7);"
        "    border-bottom-color: rgba(15,23,42,0.12);"
        "    border-right-color: rgba(15,23,42,0.1);"
        "    border-radius: 16px;"
        "    color: rgba(15,23,42,0.75);"
        "    font-size: 14px;"
        "    font-weight: 600;"
        "    padding: 12px 16px;"
        "    text-align: left;"
        "}"
        "QToolButton:hover {"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "        stop:0 rgba(255,255,255,0.94),"
        "        stop:1 rgba(236,242,255,0.66));"
        "}");

    ui->languageBtn->setStyleSheet(controlStyle);
    ui->languageBtn->setCursor(Qt::PointingHandCursor);
    ui->languageBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->languageBtn->setIconSize(QSize(20, 20));

    ui->darkModeBtn->setStyleSheet(controlStyle);
    ui->darkModeBtn->setCursor(Qt::PointingHandCursor);
    ui->darkModeBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->darkModeBtn->setIconSize(QSize(20, 20));

    ui->signOutBtn->setStyleSheet(
        "QToolButton {"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "        stop:0 rgba(255,235,235,0.88),"
        "        stop:1 rgba(239,68,68,0.18));"
        "    border: 1px solid rgba(239,68,68,0.32);"
        "    border-radius: 16px;"
        "    color: rgba(239,68,68,0.92);"
        "    font-size: 14px;"
        "    font-weight: 600;"
        "    padding: 12px 16px;"
        "    text-align: left;"
        "}"
        "QToolButton:hover {"
        "    background: qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "        stop:0 rgba(255,240,240,0.94),"
        "        stop:1 rgba(239,68,68,0.24));"
        "}");
    ui->signOutBtn->setCursor(Qt::PointingHandCursor);
    ui->signOutBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->signOutBtn->setIcon(QIcon(IconHelper::draw(IconGlyph::Logout, QSize(20, 20), QColor(239, 68, 68))));
    ui->signOutBtn->setIconSize(QSize(20, 20));

    updateLanguageButton();
    updateDarkModeButton();
}

void MainWindow::updateLanguageButton()
{
    ui->languageBtn->setIcon(QIcon(IconHelper::draw(IconGlyph::Globe, QSize(20, 20), QColor(10, 132, 255))));
    ui->languageBtn->setText(m_useEnglish ? tr("语言: English") : tr("语言: 中文"));
}

void MainWindow::updateDarkModeButton()
{
    if (m_isDarkMode) {
        ui->darkModeBtn->setIcon(QIcon(IconHelper::draw(IconGlyph::Sun, QSize(20, 20), QColor(252, 211, 77))));
        ui->darkModeBtn->setText(tr("浅色模式"));
    } else {
        ui->darkModeBtn->setIcon(QIcon(IconHelper::draw(IconGlyph::Moon, QSize(20, 20), QColor(15, 23, 42))));
        ui->darkModeBtn->setText(tr("深色模式"));
    }
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
    m_useEnglish = !m_useEnglish;
    updateLanguageButton();
}

void MainWindow::onDarkModeButtonClicked()
{
    m_isDarkMode = !m_isDarkMode;
    updateDarkModeButton();
}

void MainWindow::onSignOutButtonClicked()
{
    QApplication::quit();
}

void MainWindow::onToggleFullscreen()
{
    m_isFullscreen = !m_isFullscreen;
    if (m_isFullscreen) {
        showFullScreen();
    } else {
        showNormal();
    }
}

void MainWindow::applyShadow(QWidget *target, qreal blurRadius, qreal yOffset, const QColor &color)
{
    auto *effect = new QGraphicsDropShadowEffect(target);
    effect->setBlurRadius(blurRadius);
    effect->setOffset(0, yOffset);
    effect->setColor(color);
    target->setGraphicsEffect(effect);
}
