#include "about.h"
#include "ui_about.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QSysInfo>

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    buildLayout();
}

About::~About()
{
    delete ui;
}

void About::buildLayout()
{
    // 清除现有布局
    if (ui->widget->layout()) {
        QLayout *oldLayout = ui->widget->layout();
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }

    // React: 添加Cupertino风格滚动条
    ui->widget->setStyleSheet(
        "QScrollArea {"
        "    border: none;"
        "    background: transparent;"
        "}"
        "QScrollBar:vertical {"
        "    background: transparent;"
        "    width: 4px;"
        "    margin: 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: rgba(60, 60, 67, 0.18);"
        "    border-radius: 999px;"
        "    min-height: 20px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "    background: rgba(60, 60, 67, 0.36);"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    border: none;"
        "    background: none;"
        "    height: 0px;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: transparent;"
        "}"
        "QScrollBar:horizontal {"
        "    background: transparent;"
        "    height: 4px;"
        "    margin: 0px;"
        "}"
        "QScrollBar::handle:horizontal {"
        "    background: rgba(60, 60, 67, 0.18);"
        "    border-radius: 999px;"
        "    min-width: 20px;"
        "}"
        "QScrollBar::handle:horizontal:hover {"
        "    background: rgba(60, 60, 67, 0.36);"
        "}"
        "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {"
        "    border: none;"
        "    background: none;"
        "    width: 0px;"
        "}"
        "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {"
        "    background: transparent;"
        "}"
    );

    // React: max-w-4xl mx-auto p-8 mt-5 - 实现 max-w-4xl (896px) 限制
    QHBoxLayout *outerLayout = new QHBoxLayout(ui->widget);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->setSpacing(0);

    // 左侧弹性空间
    outerLayout->addStretch(1);

    // 中间内容区域 (max-width: 896px)
    QWidget *innerContent = new QWidget();
    innerContent->setStyleSheet("background: transparent;");
    innerContent->setMaximumWidth(896);  // max-w-4xl = 896px

    QVBoxLayout *mainLayout = new QVBoxLayout(innerContent);
    mainLayout->setContentsMargins(32, 52, 32, 32);  // p-8 + mt-5
    mainLayout->setSpacing(0);

    // 1. Logo + 应用名 + 版本号 + 按钮（居中）
    mainLayout->addWidget(createHeader());
    mainLayout->addSpacing(32);  // mb-8

    // 2. 更新日志卡片
    mainLayout->addWidget(createAppInfoCard());
    mainLayout->addSpacing(24);  // mb-6

    // 3. 系统信息卡片
    mainLayout->addWidget(createSystemInfoCard());

    // 添加弹性空间
    mainLayout->addStretch(1);

    // 添加内容区域到外层布局
    outerLayout->addWidget(innerContent);

    // 右侧弹性空间
    outerLayout->addStretch(1);
}

QWidget* About::createHeader()
{
    // React: text-center mb-8
    QWidget *header = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(header);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignCenter);

    // Logo容器 - React: w-24 h-24 mx-auto mb-6
    QWidget *logoContainer = new QWidget();
    logoContainer->setFixedSize(96, 96);  // w-24 h-24 = 96x96px
    logoContainer->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
        "stop:0 #0A84FF, stop:1 #0051C7);"
        "border-radius: 20px;");

    QGraphicsDropShadowEffect *logoShadow = new QGraphicsDropShadowEffect();
    logoShadow->setBlurRadius(40);
    logoShadow->setColor(QColor(10, 132, 255, 38));  // 0.15 * 255
    logoShadow->setOffset(0, 20);
    logoContainer->setGraphicsEffect(logoShadow);

    // Logo图标 (使用文本 "RD" 占位)
    QLabel *logoIcon = new QLabel("RD", logoContainer);
    logoIcon->setAlignment(Qt::AlignCenter);
    logoIcon->setGeometry(0, 0, 96, 96);
    logoIcon->setStyleSheet(
        "QLabel {"
        "    color: #ffffff;"
        "    font-size: 48px;"           // size-48
        "    font-weight: 700;"
        "    background: transparent;"
        "}");

    layout->addWidget(logoContainer, 0, Qt::AlignCenter);
    layout->addSpacing(24);  // mb-6

    // 应用名 - React: text-4xl font-semibold mb-2
    QLabel *appName = new QLabel("RemoteDesktop");
    appName->setAlignment(Qt::AlignCenter);
    appName->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 36px;"            // text-4xl
        "    font-weight: 600;"           // font-semibold
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "}");
    layout->addWidget(appName);
    layout->addSpacing(8);  // mb-2

    // 版本号 - React: text-xl mb-4
    QLabel *version = new QLabel("版本 2.0.1");
    version->setAlignment(Qt::AlignCenter);
    version->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"             // text-slate-500
        "    font-size: 20px;"            // text-xl
        "    font-weight: 400;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "}");
    layout->addWidget(version);
    layout->addSpacing(16);  // mb-4

    // 检查更新按钮 - React: accentBg + shadow
    QPushButton *updateBtn = new QPushButton("检查更新");
    updateBtn->setCursor(Qt::PointingHandCursor);
    updateBtn->setStyleSheet(
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
        "        stop:0 #0A84FF, stop:1 #0051C7);"
        "    color: #ffffff;"
        "    border: none;"
        "    border-radius: 14px;"
        "    padding: 8px 24px;"          // py-2 px-6
        "    font-size: 14px;"            // text-[14px]
        "    font-weight: 500;"           // font-medium
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
        "        stop:0 #0A90FF, stop:1 #005DD7);"
        "}"
        "QPushButton:pressed {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
        "        stop:0 #0A84FF, stop:1 #0051C7);"
        "}");

    QGraphicsDropShadowEffect *btnShadow = new QGraphicsDropShadowEffect();
    btnShadow->setBlurRadius(40);
    btnShadow->setColor(QColor(10, 132, 255, 38));
    btnShadow->setOffset(0, 20);
    updateBtn->setGraphicsEffect(btnShadow);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch(1);
    btnLayout->addWidget(updateBtn);
    btnLayout->addStretch(1);
    layout->addLayout(btnLayout);

    return header;
}

QWidget* About::createAppInfoCard()
{
    // React: 更新日志卡片
    QWidget *card = new QWidget();
    card->setStyleSheet(
        "QWidget {"
        "    background: rgba(255, 255, 255, 0.7);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 20px;"
        "}");

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(60);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 30);
    card->setGraphicsEffect(shadow);

    // React: p-6
    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(24, 24, 24, 24);  // p-6
    layout->setSpacing(16);  // space-y-4

    // 标题 - React: text-lg font-semibold mb-4
    QLabel *title = new QLabel("更新日志");
    title->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 18px;"            // text-lg
        "    font-weight: 600;"           // font-semibold
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "}");
    layout->addWidget(title);

    // 版本条目
    QWidget *versionEntry = new QWidget();
    versionEntry->setStyleSheet("background: transparent;");
    QVBoxLayout *entryLayout = new QVBoxLayout(versionEntry);
    entryLayout->setContentsMargins(0, 0, 0, 0);
    entryLayout->setSpacing(8);  // mt-2

    // 版本号行 - React: font-medium
    QLabel *versionLabel = new QLabel("v2.0.1 (2024-10-24)");
    versionLabel->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 14px;"
        "    font-weight: 500;"           // font-medium
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "}");
    entryLayout->addWidget(versionLabel);

    // 更新内容列表 - React: text-sm mt-2 space-y-1 ml-4 list-disc
    QString changelogText =
        "• 优化网络连接稳定性 / Improved connection stability\n"
        "• 修复部分已知问题 / Bug fixes\n"
        "• 提升画质传输效率 / Better streaming quality";

    QLabel *changelog = new QLabel(changelogText);
    changelog->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"             // text-slate-500
        "    font-size: 14px;"            // text-sm
        "    font-weight: 400;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "    padding-left: 16px;"         // ml-4
        "}");
    changelog->setWordWrap(true);
    entryLayout->addWidget(changelog);

    layout->addWidget(versionEntry);

    return card;
}

QWidget* About::createSystemInfoCard()
{
    // React: 系统信息卡片
    QWidget *card = new QWidget();
    card->setStyleSheet(
        "QWidget {"
        "    background: rgba(255, 255, 255, 0.7);"
        "    border: 1px solid rgba(0, 0, 0, 0.05);"
        "    border-radius: 20px;"
        "}");

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(60);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 30);
    card->setGraphicsEffect(shadow);

    // React: p-6
    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(24, 24, 24, 24);  // p-6
    layout->setSpacing(16);  // space-y-4

    // 标题 - React: text-lg font-semibold mb-4
    QLabel *title = new QLabel("系统信息");
    title->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"
        "    font-size: 18px;"            // text-lg
        "    font-weight: 600;"           // font-semibold
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "}");
    layout->addWidget(title);

    // 信息网格 - React: grid grid-cols-2 gap-4 text-sm
    QWidget *infoGrid = new QWidget();
    infoGrid->setStyleSheet("background: transparent;");
    QGridLayout *gridLayout = new QGridLayout(infoGrid);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setHorizontalSpacing(16);  // gap-4
    gridLayout->setVerticalSpacing(16);

    // 操作系统
    gridLayout->addWidget(createInfoRow("操作系统", getOSVersion()), 0, 0);

    // 构建版本
    gridLayout->addWidget(createInfoRow("构建版本", getBuildVersion()), 0, 1);

    layout->addWidget(infoGrid);

    return card;
}

QWidget* About::createInfoRow(const QString &label, const QString &value, bool mono)
{
    Q_UNUSED(mono);

    QWidget *row = new QWidget();
    row->setStyleSheet("background: transparent;");
    QVBoxLayout *layout = new QVBoxLayout(row);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(4);

    // 标签 - React: textSecondary
    QLabel *labelWidget = new QLabel(label);
    labelWidget->setStyleSheet(
        "QLabel {"
        "    color: #64748b;"              // text-slate-500
        "    font-size: 14px;"             // text-sm
        "    font-weight: 400;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "}");

    // 值 - React: theme.text
    QLabel *valueWidget = new QLabel(value);
    valueWidget->setStyleSheet(
        "QLabel {"
        "    color: #1e293b;"              // text-slate-900
        "    font-size: 14px;"             // text-sm
        "    font-weight: 400;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    background: transparent;"
        "}");

    layout->addWidget(labelWidget);
    layout->addWidget(valueWidget);

    return row;
}

// 辅助函数实现
QString About::getAppVersion()
{
    return "2.0.1";
}

QString About::getBuildDate()
{
    return QString(__DATE__) + " " + QString(__TIME__);
}

QString About::getOSVersion()
{
    // React: "Windows 11 Pro"
    return QSysInfo::prettyProductName();
}

QString About::getQtVersion()
{
    return QString(QT_VERSION_STR);
}

QString About::getArchitecture()
{
    return QSysInfo::currentCpuArchitecture();
}

QString About::getBuildVersion()
{
    // React: "22000.1219"
    return "22000.1219";  // 可以替换为实际构建版本
}
